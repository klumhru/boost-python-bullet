// File: btBoostDynamicsRigidBody.hpp
#ifndef _btBoostDynamicsRigidBody_hpp
#define _btBoostDynamicsRigidBody_hpp

#include <boost/python.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include "btBoostLinearMathAlignedObjectArray.hpp"

using namespace boost::python;

bool
(btCollisionObject::*btCollisionObject_hasAnisotropicFriction)(int) const
    = &btCollisionObject::hasAnisotropicFriction;

void defineRigidBody()
{
    enum_<btRigidBodyFlags>("btRigidBodyFlags")
        .value("BT_DISABLE_WORLD_GRAVITY", BT_DISABLE_WORLD_GRAVITY)
        .value("BT_ENABLE_GYROPSCOPIC_FORCE", BT_ENABLE_GYROPSCOPIC_FORCE)
    ;

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
        .add_property("anisotropic_friction",
             make_function(&btCollisionObject::getAnisotropicFriction,
             return_value_policy<copy_const_reference>()),
             &btCollisionObject::setAnisotropicFriction)
        .def("has_anisotropic_friction",
             btCollisionObject_hasAnisotropicFriction)
    ;
}

#endif // _btBoostDynamicsRigidBody_hpp
