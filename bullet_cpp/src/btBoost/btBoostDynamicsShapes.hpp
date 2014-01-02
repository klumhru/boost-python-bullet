// File: btBoostDynamicsShapes.hpp
#ifndef _btBoostDynamicsShapes_hpp
#define _btBoostDynamicsShapes_hpp

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btBox2dShape.h>
#include <BulletCollision/CollisionShapes/btConvex2dShape.h>
#include <boost/python.hpp>
#include "array_helpers.hpp"
#include "btBoostLinearMathAlignedObjectArray.hpp"

using namespace boost::python;

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(chullshape_addPoint_overloads,
                                       btConvexHullShape::addPoint,
                                       1, 2)

btTransform&    (btCompoundShape::*cs_getChildTransformRef)(int)        = &btCompoundShape::getChildTransform;
btTransform&    (btCompoundShape::*cs_getChildTransformConstRef)(int)   = &btCompoundShape::getChildTransform;
btCollisionShape*       (btCompoundShape::*cs_getChildShapeRef)(int)            = &btCompoundShape::getChildShape;
const btCollisionShape* (btCompoundShape::*cs_getChildShapeConstRef)(int) const = &btCompoundShape::getChildShape;
btDbvt*     (btCompoundShape::*cs_getDynamicAabbTree)()     = &btCompoundShape::getDynamicAabbTree;
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(compoundshape_updateChildTransform_overloads,
                                       btCompoundShape::updateChildTransform,
                                       2, 3)

void cs_removeChildShape(btCompoundShape& cs, btCollisionShape& shape)
{
    return cs.removeChildShape(&shape);
}

btConvex2dShape*
make_btConvex2dShape(btConvexShape& childShape)
{
    return new btConvex2dShape(&childShape);
}
btConvexShape*  (btConvex2dShape::*c2ds_getChildShapeRef)()     = &btConvex2dShape::getChildShape;

typedef btAlignedObjectArray<btCompoundShapeChild> btCompoundShapeChildArray;

void defineShapes()
{
    // Base classes, not for developer use

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

    class_<btPolyhedralConvexShape, bases<btConvexInternalShape>,
           boost::noncopyable>
        ("btPolyhedralConvexShape", no_init)
        .def_readonly("num_vertices", &btPolyhedralConvexShape::getNumVertices)
        .def_readonly("num_edges", &btPolyhedralConvexShape::getNumEdges)
        .def("get_edge", &btPolyhedralConvexShape::getEdge)
        .def("get_vertex", &btPolyhedralConvexShape::getVertex)
        .def_readonly("num_planes", &btPolyhedralConvexShape::getNumPlanes)
        .def("get_plane", &btPolyhedralConvexShape::getPlane)
        .def_readonly("is_inside", &btPolyhedralConvexShape::isInside)
    ;

    class_<btPolyhedralConvexAabbCachingShape, bases<btPolyhedralConvexShape>,
           boost::noncopyable>
        ("btPolyhedralConvexAabbCachingShape", no_init)
        .def("get_nonvirtual_aabb",
             &btPolyhedralConvexAabbCachingShape::getNonvirtualAabb)
        .def("recalc_local_aabb",
             &btPolyhedralConvexAabbCachingShape::getAabb)
    ;

    class_<btConcaveShape, bases<btCollisionShape>, boost::noncopyable>
        ("btConcaveShape", no_init)
    ;

    class_<btTriangleMeshShape, bases<btConcaveShape>, boost::noncopyable>
        ("btTriangleMeshShape", no_init)
    ;

    // End base classes

    // Some internal data passing classes

    class_<btCompoundShapeChild>("btCompoundShapeChild")
        .def(self == other<btCompoundShapeChild>())
        .def_readwrite("transform", &btCompoundShapeChild::m_transform)
        .add_property("child_shape",
             make_getter(&btCompoundShapeChild::m_childShape, return_value_policy<reference_existing_object>()),
             make_setter(&btCompoundShapeChild::m_childShape, return_value_policy<reference_existing_object>()))
        .def_readwrite("child_shape_type", &btCompoundShapeChild::m_childShapeType)
        .def_readwrite("child_margin", &btCompoundShapeChild::m_childMargin)
        .add_property("node",
             make_getter(&btCompoundShapeChild::m_node, return_value_policy<reference_existing_object>()),
             make_setter(&btCompoundShapeChild::m_node, return_value_policy<reference_existing_object>()))
    ;

    class_<btCompoundShapeChildArray>("btCompoundShapeChildArray")
        .def(init<btCompoundShapeChildArray>())
        .def(bt_ref_index_suite<btCompoundShapeChildArray>())
        .def("append", &btCompoundShapeChildArray::push_back)
    ;

    // End internal data passing

    // TODO: Add tests
    class_<btConvexHullShape, bases<btPolyhedralConvexAabbCachingShape> >
        ("btConvexHullShape")
        .def("add_point", &btConvexHullShape::addPoint,
             chullshape_addPoint_overloads())
        .def("get_unscaled_points",
             &btConvexHullShape::getUnscaledPoints_wrap,
             return_internal_reference<>())
        .def("get_scaled_point", &btConvexHullShape::getScaledPoint)
        .def("get_num_points", &btConvexHullShape::getNumPoints)
    ;

    // TODO: Add tests
    class_<btBox2dShape, bases<btPolyhedralConvexShape> >
        ("btBox2dShape", init<const btVector3&>())
        .def_readonly("half_extents_with_margin",
                      make_function(&btBox2dShape::getHalfExtentsWithMargin,
                                    return_value_policy<return_by_value>()))
        .def_readonly("half_extents_without_margin",
                      make_function(&btBox2dShape::getHalfExtentsWithoutMargin,
                                    return_internal_reference<>()))
    ;

    // TODO: Add tests
    class_<btBoxShape, bases<btPolyhedralConvexShape> >
        ("btBoxShape", init<const btVector3&>())
        .def_readonly("half_extents_with_margin",
                      make_function(&btBoxShape::getHalfExtentsWithMargin,
                                    return_value_policy<return_by_value>()))
        .def_readonly("half_extents_without_margin",
                      make_function(&btBoxShape::getHalfExtentsWithoutMargin,
                                    return_internal_reference<>()))
    ;

    class_<btBvhTriangleMeshShape, bases<btTriangleMeshShape>, boost::noncopyable>
        ("btBvhTriangleMeshShape", no_init)
    ; // TODO: Implement - left empty while deciding whether to define and wrap btStridingMeshInterface

    // TODO: Implement tests
    class_<btCapsuleShape, bases<btConvexInternalShape> >
        ("btCapsuleShape", init<btScalar, btScalar>())
        .def_readonly("up_axis", &btCapsuleShape::getUpAxis)
        .def_readonly("radius", &btCapsuleShape::getRadius)
        .def_readonly("half_height", &btCapsuleShape::getHalfHeight)
    ;

    // TODO: Implement tests
    class_<btCapsuleShapeX, bases<btCapsuleShape> >
        ("btCapsuleShapeX", init<btScalar, btScalar>())
    ;

    // TODO: Implement tests
    class_<btCapsuleShapeZ, bases<btCapsuleShape> >
        ("btCapsuleShapeZ", init<btScalar, btScalar>())
    ;

    // TODO: Implement tests
    class_<btCompoundShape, bases<btCollisionShape> >
        ("btCompoundShape")
        .def(init<bool>())
        .def("add_child_shape", &btCompoundShape::addChildShape)
        .def("remove_child_shape_by_index",
             &btCompoundShape::removeChildShapeByIndex)
        .def("remove_child_shape",
             cs_removeChildShape)
        .def_readonly("num_child_shapes", &btCompoundShape::getNumChildShapes)
        // TODO: Check implementation of
        //       const btCollisionShape* getChildShape(int) const
        .def("get_child_shape",
             make_function(cs_getChildShapeRef,
                           return_value_policy<reference_existing_object>()))
        // TODO: Same goes for this one, but we can't prevent python callers from
        //       modifying internal references, we'd just get a stack dump...
        .def("get_child_transform",
             make_function(cs_getChildTransformRef,
                           return_internal_reference<>()))
        .def("update_child_transform", &btCompoundShape::updateChildTransform,
             compoundshape_updateChildTransform_overloads())
        .def("get_child_list", &btCompoundShape::getChildListRef,
             return_internal_reference<>())
        .def_readonly("children", make_function(&btCompoundShape::getChildListRef,
                      return_internal_reference<>()))
        .def_readonly("dynamic_aabb_tree", make_function(cs_getDynamicAabbTree,
                      return_value_policy<reference_existing_object>()))
        .def("create_aabb_from_children", &btCompoundShape::createAabbTreeFromChildren)
        // TODO: Investigate implementation of calculatePrincipalAxisTransform
        .def_readonly("update_revision", &btCompoundShape::getUpdateRevision)
    ;

    // TODO: Implement tests
    class_<btConeShape, bases<btConvexInternalShape> >
        ("btConeShape", init<btScalar, btScalar>())
        .def_readonly("radius", &btConeShape::getRadius)
        .def_readonly("height", &btConeShape::getHeight)
        .def_readonly("cone_up_index", &btConeShape::getConeUpIndex)
    ;
    class_<btConeShapeX, bases<btConeShape> >
        ("btConeShapeX", init<btScalar, btScalar>())
    ;
    class_<btConeShapeZ, bases<btConeShape> >
        ("btConeShapeZ", init<btScalar, btScalar>())
    ;

    // TODO: Implement tests
    class_<btConvex2dShape, bases<btConvexShape> >
        ("btConvex2dShape", no_init)
        .def("__init__", make_constructor(&make_btConvex2dShape))
        .def_readonly("child_shape", make_function(c2ds_getChildShapeRef,
                      return_value_policy<reference_existing_object>()))
    ;


}

#endif // _btBoostDynamicsShapes_hpp
