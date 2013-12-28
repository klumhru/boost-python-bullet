// File: btBoostDynamicsShapes.hpp
#ifndef _btBoostDynamicsShapes_hpp
#define _btBoostDynamicsShapes_hpp

#include <btBulletDynamicsCommon.h>
#include <boost/python.hpp>

using namespace boost::python;

void defineShapes()
{
    class_<btCollisionShape, boost::noncopyable>
        ("btCollisionShape", no_init)
        .def_readonly("polyhedral", &btCollisionShape::isPolyhedral)
        .def_readonly("convex2d", &btCollisionShape::isConvex2d)
        .def_readonly("convex", &btCollisionShape::isConvex)
        .def_readonly("non_moving", &btCollisionShape::isNonMoving)
        .def_readonly("concave", &btCollisionShape::isConcave)
        .def_readonly("compound", &btCollisionShape::isCompound)
        .def_readonly("soft_body", &btCollisionShape::isSoftBody)
        .def_readonly("infinite", &btCollisionShape::isInfinite)
        .def_readonly("shape_type", &btCollisionShape::getShapeType)
        .add_property("margin", &btCollisionShape::getMargin,
                      &btCollisionShape::setMargin)
        .def("get_aabb", &btCollisionShape::getAabb)
        .def_readonly("aabb", &btCollisionShape::getAabb)
        .def("get_bounding_sphere", &btCollisionShape::getBoundingSphere)
        .def_readonly("angular_motion_disc",
                      &btCollisionShape::getAngularMotionDisc)
        .def("get_contact_breaking_threshold",
             &btCollisionShape::getContactBreakingThreshold)
        .def("calculate_temporal_aabb",
             &btCollisionShape::calculateTemporalAabb)
        .add_property("local_scaling",
                      make_function(&btCollisionShape::getLocalScaling,
                                    return_value_policy<copy_const_reference>()),
                      &btCollisionShape::setLocalScaling)
        .def("calculate_local_inertia", &btCollisionShape::calculateLocalInertia)
        .def("anisotropic_rolling_friction_direction",
             &btCollisionShape::getAnisotropicRollingFrictionDirection)
    ;

    class_<btConvexShape, bases<btCollisionShape>, boost::noncopyable>
        ("btConvexShape", no_init)
        .def("local_get_supporting_vertex",
             &btConvexShape::localGetSupportingVertexWithoutMargin)
        .def("local_get_supporting_vertex_without_margin_non_virtual",
             &btConvexShape::localGetSupportVertexWithoutMarginNonVirtual)
        .def("local_get_support_vertex_non_virtual",
             &btConvexShape::localGetSupportVertexNonVirtual)
        .def("get_margin_non_virtual",
             &btConvexShape::getMarginNonVirtual)
        .def("get_aabb_non_virtual",
             &btConvexShape::getAabbNonVirtual)
        .def("project", &btConvexShape::project)
        .def("batched_unit_vector_get_supporting_vertex_without_margin",
             &btConvexShape::batchedUnitVectorGetSupportingVertexWithoutMargin)
        .def("get_aabb_slow",
             &btConvexShape::getAabbSlow)
    ;

    class_<btConvexInternalShape, bases<btConvexShape>, boost::noncopyable>
        ("btConvexInternalShape", no_init)
        .add_property("implicit_shape_dimensions",
                      make_function(&btConvexInternalShape::getImplicitShapeDimensions,
                                    return_value_policy<copy_const_reference>()),
                      &btConvexInternalShape::setImplicitShapeDimensions)
        // TODO: wrap setSafeMargin overloads
        .def_readonly("local_scaling_non_virtual",
                      make_function(&btConvexInternalShape::getLocalScalingNV,
                                    return_value_policy<copy_const_reference>()))
        .def_readonly("margin_non_virtual",
                      make_function(&btConvexInternalShape::getMarginNV,
                                    return_value_policy<return_by_value>()))
        .def_readonly("num_preferred_penetration_directions",
                      &btConvexInternalShape::getNumPreferredPenetrationDirections)
        .def("get_preferred_penetration_direction",
             &btConvexInternalShape::getPreferredPenetrationDirection)
    ;
}

#endif // _btBoostDynamicsShapes_hpp
