#include "DiscreteDynamicsWorld.hpp"

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBoost/Collision/CollisionWorldWrappers.hpp>

using namespace boost::python;

const btBroadphaseInterface*
    (btCollisionWorld::*btCollisionWorld_getBroadphase_const)() const
    = &btCollisionWorld::getBroadphase;
btBroadphaseInterface*
    (btCollisionWorld::*btCollisionWorld_getBroadphase)()
    = &btCollisionWorld::getBroadphase;

const btDispatcher*
    (btCollisionWorld::*btCollisionWorld_getDispatcher_const)() const
    = &btCollisionWorld::getDispatcher;
btDispatcher*
    (btCollisionWorld::*btCollisionWorld_getDispatcher)()
    = &btCollisionWorld::getDispatcher;

const btDispatcherInfo&
    (btCollisionWorld::*btCollisionWorld_getDispatchInfo_const)() const
    = &btCollisionWorld::getDispatchInfo;
btDispatcherInfo&
    (btCollisionWorld::*btCollisionWorld_getDispatchInfo)()
    = &btCollisionWorld::getDispatchInfo;

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(ddw_step_overloads,
                                       stepSimulation,
                                       1, 3);

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(ddw_addCollisionObject_overloads,
                                       addCollisionObject,
                                       1, 3);

void defineDiscreteDynamicsWorld()
{
    class_<btCollisionWorld::LocalShapeInfo>("LocalShapeInfo")
        .def_readwrite("shape_part",
                       &btCollisionWorld::LocalShapeInfo::m_shapePart)
        .def_readwrite("triangle_index",
                       &btCollisionWorld::LocalShapeInfo::m_triangleIndex)
    ;

    class_<btCollisionWorld::LocalRayResult, boost::noncopyable>
        ("LocalRayResult", no_init)
        .def("__init__", make_constructor(&LocalRayResultWrap::init))
        .add_property("collision_object",
                      make_function(&LocalRayResultWrap::getCollisionObject,
                                    return_internal_reference<>()))
        .def_readwrite("local_shape_info",
                       &btCollisionWorld::LocalRayResult::m_localShapeInfo)
        .def_readwrite("hit_normal_local",
                       &btCollisionWorld::LocalRayResult::m_hitNormalLocal)
        .def_readwrite("hit_fraction",
                       &btCollisionWorld::LocalRayResult::m_hitFraction)
    ;

    class_<RayResultCallbackWrap, boost::noncopyable>
        ("RayResultCallback")
        .def_readwrite("closest_hit_fraction",
                       &RayResultCallbackWrap::m_closestHitFraction)
        .add_property("collision_object",
                      make_function(RayResultCallbackWrap::getCollisionObject,
                                    return_internal_reference<>()),
                      make_function(RayResultCallbackWrap::setCollisionObject,
                                    with_custodian_and_ward<1, 2>()))
        .def_readwrite("collision_filter_group",
                       &RayResultCallbackWrap::m_collisionFilterGroup)
        .def_readwrite("collision_filter_mask",
                       &RayResultCallbackWrap::m_collisionFilterMask)
        .def_readwrite("flags", &RayResultCallbackWrap::m_flags)
        .add_property("has_hit", &RayResultCallbackWrap::hasHit)
        .def("needs_collision", RayResultCallbackWrap::needsCollision)
        .def("add_single_result", &RayResultCallbackWrap::addSingleResult)
    ;

    class_<btCollisionWorld::ClosestRayResultCallback,
           bases<btCollisionWorld::RayResultCallback>, boost::noncopyable>
        ("ClosestRayResultCallback",
         init<const btVector3&, const btVector3&>())
        .def_readwrite("ray_from_world",
                       &btCollisionWorld::ClosestRayResultCallback::m_rayFromWorld)
        .def_readwrite("ray_to_world",
                       &btCollisionWorld::ClosestRayResultCallback::m_rayToWorld)
        .def_readwrite("hit_normal_world",
                       &btCollisionWorld::ClosestRayResultCallback::m_hitNormalWorld)
        .def_readwrite("hit_point_world",
                       &btCollisionWorld::ClosestRayResultCallback::m_hitPointWorld)
    ;

    class_<btCollisionWorld::AllHitsRayResultCallback,
           bases<btCollisionWorld::RayResultCallback>, boost::noncopyable>
        ("AllHitsRayResultCallback",
         init<const btVector3&, const btVector3&>())
        // TODO: Wrap m_collisionObjects
        .def_readwrite("ray_from_world",
                       &btCollisionWorld::AllHitsRayResultCallback::m_rayFromWorld)
        .def_readwrite("ray_to_world",
                       &btCollisionWorld::AllHitsRayResultCallback::m_rayToWorld)
        .def_readwrite("hit_normal_world",
                       &btCollisionWorld::AllHitsRayResultCallback::m_hitNormalWorld)
        .def_readwrite("hit_point_world",
                       &btCollisionWorld::AllHitsRayResultCallback::m_hitPointWorld)
        .def_readwrite("hit_fractions",
                       &btCollisionWorld::AllHitsRayResultCallback::m_hitFractions)
    ;

    class_<btCollisionWorld::LocalConvexResult,
           boost::noncopyable>
        ("LocalConvexResult", no_init)
        .def("__init__", make_constructor(&LocalConvexResultWrap::init))
        .add_property("hit_collision_object",
                      make_function(LocalConvexResultWrap::getHitCollisionObject,
                                    return_internal_reference<>()),
                      make_function(LocalConvexResultWrap::setHitCollisionObject,
                                    with_custodian_and_ward<1, 2>()))
        .add_property("local_shape_info",
                      make_function(LocalConvexResultWrap::getLocalShapeInfo,
                                    return_internal_reference<>()),
                      make_function(LocalConvexResultWrap::setLocalShapeInfo,
                                    with_custodian_and_ward<1, 2>()))
        .def_readwrite("hit_normal_local",
                       &btCollisionWorld::LocalConvexResult::m_hitNormalLocal)
        .def_readwrite("hit_point_local",
                       &btCollisionWorld::LocalConvexResult::m_hitPointLocal)
        .def_readwrite("hit_fraction",
                       &btCollisionWorld::LocalConvexResult::m_hitFraction)
    ;

    class_<btCollisionWorld::ConvexResultCallback,
           boost::noncopyable>
        ("ConvexResultCallback", no_init)
        .def_readwrite("closest_hit_fraction",
                       &btCollisionWorld::ConvexResultCallback::m_closestHitFraction)
        .def_readwrite("collision_filter_group",
                       &btCollisionWorld::ConvexResultCallback::m_collisionFilterGroup)
        .def_readwrite("collision_filter_mask",
                       &btCollisionWorld::ConvexResultCallback::m_collisionFilterMask)
        .add_property("has_hit",
                      &btCollisionWorld::ConvexResultCallback::hasHit)
        // TODO: Wrap needsCollision and addSingleResult
    ;

    class_<btCollisionWorld::ClosestConvexResultCallback,
           bases<btCollisionWorld::ConvexResultCallback>,
           boost::noncopyable>
        ("ClosestConvexResultCallback", init<const btVector3&, const btVector3&>())
        .def_readwrite("convex_from_world",
                       &btCollisionWorld::ClosestConvexResultCallback::m_convexFromWorld)
        .def_readwrite("convex_to_world",
                       &btCollisionWorld::ClosestConvexResultCallback::m_convexToWorld)
        .def_readwrite("hit_normal_world",
                       &btCollisionWorld::ClosestConvexResultCallback::m_hitNormalWorld)
        .def_readwrite("hit_point_world",
                       &btCollisionWorld::ClosestConvexResultCallback::m_hitPointWorld)
        .add_property("hit_collision_object",
                      make_function(ClosestConvexResultCallbackWrap::getHitCollisionObject,
                                    return_internal_reference<>()),
                      make_function(ClosestConvexResultCallbackWrap::setHitCollisionObject,
                                    with_custodian_and_ward<1, 2>()))
    ;

    class_<btCollisionWorld::ContactResultCallback,
           boost::noncopyable>
        ("ContactResultCallback", no_init)
        .def_readwrite("collision_filter_group",
                       &btCollisionWorld::ContactResultCallback::m_collisionFilterGroup)
        .def_readwrite("collision_filter_mask",
                       &btCollisionWorld::ContactResultCallback::m_collisionFilterMask)
        // TODO: Wrap needsCollision and addSingleResult
    ;

    class_<btCollisionWorld, boost::noncopyable>
        ("btCollisionWorld", no_init)
        .def("__init__", make_constructor(&btCollisionWorldWrap::init))
        .def("step_simulation", &btDiscreteDynamicsWorld::stepSimulation,
             ddw_step_overloads())
        .add_property("broadphase",
                      make_function(btCollisionWorld_getBroadphase,
                                    return_internal_reference<>()),
                      make_function(btCollisionWorldWrap::setBroadphase,
                                    with_custodian_and_ward<1, 2>()))
        .add_property("dispatcher",
                      make_function(btCollisionWorld_getDispatcher_const,
                                    return_internal_reference<>()))
        .add_property("pair_cache",
                      make_function(&btCollisionWorld::getPairCache,
                                    return_internal_reference<>()))
        .def("update_single_aabb", btCollisionWorldWrap::updateSingleAabb)
        .def("update_aabbs", &btCollisionWorld::updateAabbs)
        .def("compute_overlapping_pairs",
             &btCollisionWorld::computeOverlappingPairs)
        .add_property("num_collision_objects",
                      &btCollisionWorld::getNumCollisionObjects)
        .def("ray_test",
             &btCollisionWorld::rayTest)
        .def("convex_sweep_test",
             &btCollisionWorld::convexSweepTest)
        .def("contact_test",
             &btCollisionWorld::contactTest)
        .def("contact_pair_test",
             &btCollisionWorld::contactPairTest)
        // Internal functions are not wrapped for ray and object tests
        .def("ray_test_single",
             &btCollisionWorldWrap::rayTestSingle)
        .staticmethod("ray_test_single")
        .def("object_query_single",
             &btCollisionWorldWrap::objectQuerySingle)
        .staticmethod("object_query_single")
        .def("add_collision_object",
             btCollisionWorldWrap::addCollisionObject,
             with_custodian_and_ward<1, 2>())
        // TODO: implement overloads for addCollisionObject
        // TODO: implement getCollisionObjectArray
        .def("remove_collision_object",
             btCollisionWorldWrap::removeCollisionObject)
        .def("perform_discrete_collision_detection",
             &btCollisionWorld::performDiscreteCollisionDetection)
        .add_property("dispatch_info",
                      make_function(btCollisionWorld_getDispatchInfo,
                                    return_internal_reference<>()))
        .add_property("force_update_all_aabbs",
                      &btCollisionWorld::getForceUpdateAllAabbs,
                      &btCollisionWorld::setForceUpdateAllAabbs)
    ;

    class_<btDynamicsWorld, bases<btCollisionWorld>, boost::noncopyable>
        ("btDynamicsWorld", no_init);

    class_<btDiscreteDynamicsWorld, bases<btDynamicsWorld>, boost::noncopyable>
        ("btDiscreteDynamicsWorld", no_init)
        .def("__init__", make_constructor(&btDiscreteDynamicsWorldWrap::init))
        .def("synchronize_motion_states",
             &btDiscreteDynamicsWorld::synchronizeMotionStates)
        .def("set_gravity",
             &btDiscreteDynamicsWorld::setGravity)
        .def("get_gravity",
             &btDiscreteDynamicsWorld::getGravity)
        .add_property("gravity",
                      make_function(&btDiscreteDynamicsWorld::getGravity,
                                    return_value_policy<return_by_value>()),
                      &btDiscreteDynamicsWorld::setGravity)
        .def("add_collision_object",
             btDiscreteDynamicsWorldWrap::addCollisionObject,
             with_custodian_and_ward<1, 2>())
        .def("remove_collision_object",
             btDiscreteDynamicsWorldWrap::removeCollisionObject)
    ;
}
