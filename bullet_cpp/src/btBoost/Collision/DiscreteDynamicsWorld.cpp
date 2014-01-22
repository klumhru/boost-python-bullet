#include "DiscreteDynamicsWorld.hpp"

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
