#include "RigidBody.hpp"

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <btBoost/LinearMath/AlignedObjectArray.hpp>

using namespace boost::python;


BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(btCollisionObject_hasAnisotropicFriction_overloads,
                                       btCollisionObject::hasAnisotropicFriction,
                                       0, 1)

btCollisionShape*
(btCollisionObject::*btCollisionObject_getCollisionShape)()
    = &btCollisionObject::getCollisionShape;

void btCollisionObject_setCollisionShape(btCollisionObject& obj,
                                         btCollisionShape& shape)
{
    return obj.setCollisionShape(&shape);
}

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(btCollisionObject_activate_overloads,
                                       btCollisionObject::activate,
                                       0, 1)

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(btCollisionObject_setAnisotropicFriction_overloads,
                                       btCollisionObject::setAnisotropicFriction,
                                       1, 2)

btTransform&
(btCollisionObject::*btCollisionObject_getWorldTransform)()
    = &btCollisionObject::getWorldTransform;
const btTransform&
(btCollisionObject::*btCollisionObject_getWorldTransform_const)() const
    = &btCollisionObject::getWorldTransform;

btBroadphaseProxy*
(btCollisionObject::*btCollisionShape_getBroadphaseHandle)()
    = &btCollisionObject::getBroadphaseHandle;

btTransform&
(btCollisionObject::*btCollisionObject_getInterpolationWorldTransform)()
    = &btCollisionObject::getInterpolationWorldTransform;
const btTransform&
(btCollisionObject::*btCollisionObject_getInterpolationWorldTransform_const)() const
    = &btCollisionObject::getInterpolationWorldTransform;

void
btCollisionObject_setBroadphaseHandle(btCollisionObject& obj,
                                      btBroadphaseProxy& handle)
{
    return obj.setBroadphaseHandle(&handle);
}

bool btCollisionObject_checkCollideWith(btCollisionObject& lv,
                                        btCollisionObject& rv)
{
    return lv.checkCollideWith(&rv);
}

class btRigidBodyConstruciontInfoWrap
{
public:
    static btCollisionShape*
    getCollisionShape(btRigidBody::btRigidBodyConstructionInfo& info)
    {
        return info.m_collisionShape;
    }
    static void
    setCollisionShape(btRigidBody::btRigidBodyConstructionInfo& info,
                      btCollisionShape& shape)
    {
        info.m_collisionShape = &shape;
    }

    static btMotionState*
    getMotionState(btRigidBody::btRigidBodyConstructionInfo& info)
    {
        return info.m_motionState;
    }
    static void
    setMotionState(btRigidBody::btRigidBodyConstructionInfo& info,
                   btMotionState& state)
    {
        info.m_motionState = &state;
    }

    static boost::shared_ptr<btRigidBody::btRigidBodyConstructionInfo>
    create(btScalar mass,
           btMotionState& state,
           btCollisionShape& shape,
           const btVector3& inertia)
    {
        return boost::shared_ptr<btRigidBody::btRigidBodyConstructionInfo>(
            new btRigidBody::btRigidBodyConstructionInfo(
                mass, &state, &shape, inertia
            )
        );
    }
};

class btRigidBodyWrap
{
public:
    static boost::shared_ptr<btRigidBody>
    create(btScalar mass,
           btMotionState& motionState,
           btCollisionShape& collisionShape,
           const btVector3& inertia)
    {
        return boost::shared_ptr<btRigidBody>(
            new btRigidBody(mass,
                            &motionState,
                            &collisionShape,
                            inertia)
        );
    }

    static btRigidBody*
    upcast(btCollisionObject& obj)
    {
        return btRigidBody::upcast(&obj);
    }

    static const btTransform&
    getCenterOfMassTransform(btRigidBody& body)
    {
        return body.getCenterOfMassTransform();
    }

    static const btVector3&
    getCenterOfMassPosition(btRigidBody& body)
    {
        return body.getCenterOfMassPosition();
    }

    static const btVector3&
    getLinearVelocity(btRigidBody& body)
    {
        return body.getLinearVelocity();
    }

    static const btVector3&
    getAngularVelocity(btRigidBody& body)
    {
        return body.getAngularVelocity();
    }

    static void
    setBroadPhaseProxy(btRigidBody& body, btBroadphaseProxy& proxy)
    {
        body.setNewBroadphaseProxy(&proxy);
    }
    static void
    setMotionState(btRigidBody& body, btMotionState& motionState)
    {
        body.setMotionState(&motionState);
    }

    static void
    setAngularFactorFloat(btRigidBody& body, btScalar val)
    {
        body.setAngularFactor(val);
    }
    static void
    setAngularFactorVec(btRigidBody& body, const btVector3& vec)
    {
        body.setAngularFactor(vec);
    }
};

btBroadphaseProxy*
(btRigidBody::*_rb_get_bp_pointer)() = &btRigidBody::getBroadphaseProxy;
btMotionState*
(btRigidBody::*_rb_get_ms_pointer)() = &btRigidBody::getMotionState;

void defineRigidBody()
{
    class_<btCollisionObjectArray>("btCollisionObjectArray")
        .def(init<btCollisionObjectArray>())
        .def(bt_ref_index_suite<btCollisionObjectArray>())
        .def("append", &btCollisionObjectArray::push_back)
    ;

    enum_<btCollisionObject::CollisionFlags>("CollisionFlags")
        .value("CF_STATIC_OBJECT", btCollisionObject::CF_STATIC_OBJECT)
        .value("CF_KINEMATIC_OBJECT", btCollisionObject::CF_KINEMATIC_OBJECT)
        .value("CF_NO_CONTACT_RESPONSE", btCollisionObject::CF_NO_CONTACT_RESPONSE)
        .value("CF_CUSTOM_MATERIAL_CALLBACK", btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK)
        .value("CF_CHARACTER_OBJECT", btCollisionObject::CF_CHARACTER_OBJECT)
        .value("CF_DISABLE_VISUALIZE_OBJECT", btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT)
        .value("CF_DISABLE_SPU_COLLISION_PROCESSING", btCollisionObject::CF_DISABLE_SPU_COLLISION_PROCESSING)
    ;

    enum_<btCollisionObject::CollisionObjectTypes>
        ("CollisionObjectTypes")
        .value("CO_COLLISION_OBJECT", btCollisionObject::CO_COLLISION_OBJECT)
        .value("CO_RIGID_BODY", btCollisionObject::CO_RIGID_BODY)
        .value("CO_GHOST_OBJECT", btCollisionObject::CO_GHOST_OBJECT)
        .value("CO_SOFT_BODY", btCollisionObject::CO_SOFT_BODY)
        .value("CO_HF_FLUID", btCollisionObject::CO_HF_FLUID)
        .value("CO_USER_TYPE", btCollisionObject::CO_USER_TYPE)
        .value("CO_FEATHERSTONE_LINK", btCollisionObject::CO_FEATHERSTONE_LINK)
    ;

    enum_<btCollisionObject::AnisotropicFrictionFlags>
        ("AnisotropicFrictionFlags")
        .value("CF_ANISOTROPIC_FRICTION_DISABLED", btCollisionObject::CF_ANISOTROPIC_FRICTION_DISABLED)
        .value("CF_ANISOTROPIC_FRICTION", btCollisionObject::CF_ANISOTROPIC_FRICTION)
        .value("CF_ANISOTROPIC_ROLLING_FRICTION", btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION)
    ;

    class_<btCollisionObject>
        ("btCollisionObject")
        .def_readonly("merges_simulation_islands",
             &btCollisionObject::mergesSimulationIslands)
        .def("get_anisotropic_friction",
             &btCollisionObject::getAnisotropicFriction,
             return_value_policy<copy_const_reference>())
        .def("set_anisotropic_friction",
             &btCollisionObject::setAnisotropicFriction,
             btCollisionObject_setAnisotropicFriction_overloads())
        .def("has_anisotropic_friction",
             &btCollisionObject::hasAnisotropicFriction,
             btCollisionObject_hasAnisotropicFriction_overloads())
        .add_property("contact_processing_threshold",
                      make_function(&btCollisionObject::getContactProcessingThreshold,
                                    return_value_policy<return_by_value>()),
                      &btCollisionObject::setContactProcessingThreshold)
        .def_readonly("static_object",
                      &btCollisionObject::isStaticObject)
        .def_readonly("kinematic_object",
                      &btCollisionObject::isKinematicObject)
        .def_readonly("static_or_kinematic_object",
                      &btCollisionObject::isStaticOrKinematicObject)
        .def_readonly("has_contact_response",
                      &btCollisionObject::hasContactResponse)
        .add_property("collision_shape",
                      make_function(btCollisionObject_getCollisionShape,
                                    return_internal_reference<>()),
                      make_function(btCollisionObject_setCollisionShape,
                                    with_custodian_and_ward<1, 2>()))
        // Internal API calls not implemented:
        // * internalGetExtensionPointer
        // * internalSetExtensionPointer
        .add_property("activation_state",
                      &btCollisionObject::getActivationState,
                      &btCollisionObject::setActivationState)
        .add_property("deactivation_time",
                      &btCollisionObject::getDeactivationTime,
                      &btCollisionObject::setDeactivationTime)
        .def("force_activation_state",
             &btCollisionObject::forceActivationState)
        .def("activate",
             &btCollisionObject::activate,
             btCollisionObject_activate_overloads())
        .def_readonly("active",
                      &btCollisionObject::isActive)
        .add_property("restitution",
                      &btCollisionObject::getRestitution,
                      &btCollisionObject::setRestitution)
        .add_property("friction",
                      &btCollisionObject::getFriction,
                      &btCollisionObject::setFriction)
        .add_property("rolling_friction",
                      &btCollisionObject::getRollingFriction,
                      &btCollisionObject::setRollingFriction)
        .def_readonly("internal_type",
                      &btCollisionObject::getInternalType)
        .add_property("world_transform",
                      make_function(btCollisionObject_getWorldTransform,
                                    return_internal_reference<>()),
                      &btCollisionObject::setWorldTransform)
        .def("get_world_transform",
             btCollisionObject_getWorldTransform_const,
             return_value_policy<copy_const_reference>())
        .add_property("broadphase_handle",
                      make_function(btCollisionShape_getBroadphaseHandle,
                                    return_internal_reference<>()),
                      make_function(btCollisionObject_setBroadphaseHandle,
                                    with_custodian_and_ward<1, 2>()))
        .add_property("interpolation_world_transform",
                      make_function(btCollisionObject_getInterpolationWorldTransform,
                                    return_internal_reference<>()),
                      &btCollisionObject::setInterpolationWorldTransform)
        .def("get_interpolation_world_transform",
             btCollisionObject_getInterpolationWorldTransform_const,
             return_value_policy<copy_const_reference>())
        .add_property("interpolation_linear_velocity",
                      make_function(&btCollisionObject::getInterpolationLinearVelocity,
                                    return_value_policy<copy_const_reference>()),
                      &btCollisionObject::setInterpolationLinearVelocity)
        .add_property("interpolation_angular_velocity",
                      make_function(&btCollisionObject::getInterpolationAngularVelocity,
                                    return_value_policy<copy_const_reference>()),
                      &btCollisionObject::setInterpolationAngularVelocity)
        .add_property("island_tag",
                      &btCollisionObject::getIslandTag,
                      &btCollisionObject::setIslandTag)
        .add_property("companion_id",
                      &btCollisionObject::getCompanionId,
                      &btCollisionObject::setCompanionId)
        .add_property("hit_fraction",
                      &btCollisionObject::getHitFraction,
                      &btCollisionObject::setHitFraction)
        .add_property("collision_flags",
                      &btCollisionObject::getCollisionFlags,
                      &btCollisionObject::setCollisionFlags)
        .add_property("ccd_swept_sphere_radius",
                      &btCollisionObject::getCcdSweptSphereRadius,
                      &btCollisionObject::setCcdSweptSphereRadius)
        .add_property("ccd_motion_threshold",
                      &btCollisionObject::getCcdMotionThreshold,
                      &btCollisionObject::setCcdMotionThreshold)
        .def_readonly("ccd_square_motion_threshold",
                      &btCollisionObject::getCcdSquareMotionThreshold)
        .add_property("user_index",
                      &btCollisionObject::getUserIndex,
                      &btCollisionObject::setUserIndex)
        .def_readonly("update_revision_interval",
                      &btCollisionObject::getUpdateRevisionInternal)
        .def("check_collide_with",
             &btCollisionObject_checkCollideWith)
    ;

    enum_<btRigidBodyFlags>("btRigidBodyFlags")
        .value("BT_DISABLE_WORLD_GRAVITY", BT_DISABLE_WORLD_GRAVITY)
        .value("BT_ENABLE_GYROPSCOPIC_FORCE", BT_ENABLE_GYROPSCOPIC_FORCE)
    ;

    class_<btRigidBody::btRigidBodyConstructionInfo>
        ("btRigidBodyConstructionInfo", no_init)
        .def("__init__", make_constructor(btRigidBodyConstruciontInfoWrap::create))
        .add_property("motion_state",
                      make_function(btRigidBodyConstruciontInfoWrap::getMotionState,
                                    return_internal_reference<>()),
                      make_function(btRigidBodyConstruciontInfoWrap::setMotionState,
                                    with_custodian_and_ward<1, 2>()))
        .add_property("collision_shape",
                      make_function(btRigidBodyConstruciontInfoWrap::getCollisionShape,
                                    return_internal_reference<>()),
                      make_function(btRigidBodyConstruciontInfoWrap::setCollisionShape,
                                    with_custodian_and_ward<1, 2>()))
        .def_readwrite("mass", &btRigidBody::btRigidBodyConstructionInfo::m_mass)
        .def_readwrite("start_world_transform", &btRigidBody::btRigidBodyConstructionInfo::m_startWorldTransform)
        .def_readwrite("local_inertia", &btRigidBody::btRigidBodyConstructionInfo::m_localInertia)
        .def_readwrite("linear_damping", &btRigidBody::btRigidBodyConstructionInfo::m_linearDamping)
        .def_readwrite("angular_damping", &btRigidBody::btRigidBodyConstructionInfo::m_angularDamping)
        .def_readwrite("friction", &btRigidBody::btRigidBodyConstructionInfo::m_friction)
        .def_readwrite("rolling_friction", &btRigidBody::btRigidBodyConstructionInfo::m_rollingFriction)
        .def_readwrite("linear_sleeping_threshold", &btRigidBody::btRigidBodyConstructionInfo::m_linearSleepingThreshold)
        .def_readwrite("angular_sleeping_threshold", &btRigidBody::btRigidBodyConstructionInfo::m_angularSleepingThreshold)
        .def_readwrite("additional_damping", &btRigidBody::btRigidBodyConstructionInfo::m_additionalDamping)
        .def_readwrite("additional_damping_factor", &btRigidBody::btRigidBodyConstructionInfo::m_additionalDampingFactor)
        .def_readwrite("additional_linear_damping_threshold_sqr", &btRigidBody::btRigidBodyConstructionInfo::m_additionalLinearDampingThresholdSqr)
        .def_readwrite("additional_angular_damping_threshold_sqr", &btRigidBody::btRigidBodyConstructionInfo::m_additionalAngularDampingThresholdSqr)
        .def_readwrite("additional_angular_damping_factor", &btRigidBody::btRigidBodyConstructionInfo::m_additionalAngularDampingFactor)
    ;

    class_<btRigidBody, bases<btCollisionObject> >
        ("btRigidBody", init<const btRigidBody::btRigidBodyConstructionInfo&>())
        .def("__init__", make_constructor(btRigidBodyWrap::create))
        .def("upcast", btRigidBodyWrap::upcast,
             return_internal_reference<>())
        .staticmethod("upcast")
        .def("predict_integrated_transform",
             &btRigidBody::predictIntegratedTransform)
        .def("save_kinematic_state", &btRigidBody::saveKinematicState)
        .def("apply_gravity", &btRigidBody::applyGravity)
        .add_property("gravity", make_function(&btRigidBody::getGravity,
                      return_value_policy<copy_const_reference>()),
                      &btRigidBody::setGravity)
        .def("set_damping", &btRigidBody::setDamping)
        .def_readonly("angular_damping", &btRigidBody::getAngularDamping)
        .def_readonly("linear_damping", &btRigidBody::getLinearDamping)
        .def_readonly("linear_sleeping_threshold", &btRigidBody::getLinearSleepingThreshold)
        .def_readonly("angular_sleeping_threshold", &btRigidBody::getAngularSleepingThreshold)
        .add_property("linear_factor", make_function(&btRigidBody::getLinearFactor,
                      return_value_policy<copy_const_reference>()),
                      &btRigidBody::setLinearFactor)
        .def("set_mass_props", &btRigidBody::setMassProps)
        .def_readonly("inv_mass", &btRigidBody::getInvMass)
        // TODO: Add test for inv_inertia_tensor_world
        .def_readonly("inv_inertia_tensor_world",
                      make_function(&btRigidBody::getInvInertiaTensorWorld,
                                    return_value_policy<copy_const_reference>()))
        .def("get_inv_inertia_tensor_world",
             &btRigidBody::getInvInertiaTensorWorld,
             return_value_policy<copy_const_reference>())
        .def("integrate_velocities", &btRigidBody::integrateVelocities)
        .def("apply_central_force", &btRigidBody::applyCentralForce)
        .def("get_total_force", &btRigidBody::getTotalForce,
             return_value_policy<copy_const_reference>())
        .def("get_total_torque", &btRigidBody::getTotalTorque,
             return_value_policy<copy_const_reference>())
        .def("get_inv_inertia_diag_local", &btRigidBody::getInvInertiaDiagLocal,
             return_value_policy<copy_const_reference>())
        .add_property("inv_inertia_diag_local", make_function(&btRigidBody::getInvInertiaDiagLocal,
                      return_value_policy<copy_const_reference>()),
                      &btRigidBody::setInvInertiaDiagLocal)
        .def("set_sleeping_thresholds", &btRigidBody::setSleepingThresholds)
        .def("apply_torque", &btRigidBody::applyTorque)
        .def("apply_force", &btRigidBody::applyForce)
        .def("apply_central_impulse", &btRigidBody::applyCentralImpulse)
        .def("apply_torque_impulse", &btRigidBody::applyTorqueImpulse)
        .def("apply_impulse", &btRigidBody::applyImpulse)
        .def("clear_forces", &btRigidBody::clearForces)
        .def("update_inertia_tensor", &btRigidBody::updateInertiaTensor)
        .add_property("center_of_mass_transform",
                      make_function(&btRigidBody::getCenterOfMassTransform,
                      return_internal_reference<>()),
                      &btRigidBody::setCenterOfMassTransform)
        .def("set_center_of_mass_transform",
             &btRigidBody::setCenterOfMassTransform)
        .def("get_center_of_mass_transform",
             &btRigidBody::getCenterOfMassTransform,
             return_internal_reference<>())
        .add_property("center_of_mass_position",
                      make_function(&btRigidBody::getCenterOfMassPosition,
                      return_internal_reference<>()))
        .def("get_center_of_mass_position",
             &btRigidBody::getCenterOfMassPosition,
             return_internal_reference<>())
        .add_property("angular_velocity", make_function(&btRigidBody::getAngularVelocity,
                      return_internal_reference<>()),
                      &btRigidBody::setAngularVelocity)
        .add_property("linear_velocity", make_function(&btRigidBody::getLinearVelocity,
                      return_internal_reference<>()),
                      &btRigidBody::setLinearVelocity)
        .def("get_linear_velocity_in_local_point",
             &btRigidBody::getVelocityInLocalPoint,
             return_value_policy<return_by_value>())
        .def("translate", &btRigidBody::translate)
        .def("get_aabb", &btRigidBody::getAabb)
        // TODO: test broadphase proxy in integration tests
        .add_property("broadphase_proxy",
                      make_function(_rb_get_bp_pointer,
                                    return_internal_reference<>()),
                      make_function(btRigidBodyWrap::setBroadPhaseProxy,
                                    with_custodian_and_ward<1, 2>()))
        .add_property("motion_state",
                      make_function(_rb_get_ms_pointer,
                                    return_internal_reference<>()),
                      make_function(btRigidBodyWrap::setMotionState,
                                    with_custodian_and_ward<1, 2>()))
        .def("set_angular_factor",
             btRigidBodyWrap::setAngularFactorFloat)
        .add_property("angular_factor", make_function(&btRigidBody::getAngularFactor,
                      return_value_policy<copy_const_reference>()),
                      btRigidBodyWrap::setAngularFactorVec)
        .def_readonly("in_world", &btRigidBody::isInWorld)
        // TODO: Add constraint support when btTypedConstraint is ready
        .add_property("flags", &btRigidBody::getFlags, &btRigidBody::setFlags)
        .def("compute_gyroscopic_force",
             &btRigidBody::computeGyroscopicForce,
             return_value_policy<return_by_value>())
    ;
}
