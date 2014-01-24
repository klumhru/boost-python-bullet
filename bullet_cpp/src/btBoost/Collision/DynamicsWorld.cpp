#include "DynamicsWorld.hpp"

#include <boost/python.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBoost/Collision/DynamicsWorldWrap.hpp>

using namespace boost::python;

void defineDynamicsWorld()
{
    enum_<btDynamicsWorldType>
        ("btDynamicsWorldType")
        .value("BT_SIMPLE_DYNAMICS_WORLD", BT_SIMPLE_DYNAMICS_WORLD)
        .value("BT_DISCRETE_DYNAMICS_WORLD", BT_DISCRETE_DYNAMICS_WORLD)
        .value("BT_CONTINUOUS_DYNAMICS_WORLD", BT_CONTINUOUS_DYNAMICS_WORLD)
        .value("BT_SOFT_RIGID_DYNAMICS_WORLD", BT_SOFT_RIGID_DYNAMICS_WORLD)
        .value("BT_GPU_DYNAMICS_WORLD", BT_GPU_DYNAMICS_WORLD)
    ;

    // TODO: Add tests implicitly through implementing classes
    // TODO: Make this class dynamic abstract
    class_<btDynamicsWorld, bases<btCollisionWorld>,
           boost::noncopyable>
        ("btDynamicsWorld", no_init)
        .def("step_simulation",
             &btDynamicsWorld::stepSimulation,
             stepSimulation_overloads())
        .def("add_constraint",
             DynamicsWorldWrap::addConstraint,
             with_custodian_and_ward<1, 2>())
        .def("remove_constraint",
             DynamicsWorldWrap::removeConstraint)
        .def("add_action",
             DynamicsWorldWrap::addAction,
             with_custodian_and_ward<1, 2>())
        .add_property("gravity",
                      make_function(&btDynamicsWorld::getGravity,
                                    return_value_policy<return_by_value>()),
                      &btDynamicsWorld::setGravity)
        .def("add_rigidbody",
             DynamicsWorldWrap::addRigidBody,
             with_custodian_and_ward<1, 2>())
        .def("add_rigidbody",
             DynamicsWorldWrap::addRigidBody_mask_group,
             with_custodian_and_ward<1, 2>())
        .def("remove_rigidbody",
             DynamicsWorldWrap::removeRigidBody)
        .add_property("constraint_solver",
                      make_function(DynamicsWorldWrap::getConstraintSolver,
                                    return_internal_reference<>()),
                      make_function(DynamicsWorldWrap::setConstraintSolver,
                                    with_custodian_and_ward<1, 2>()))
        .def("num_constraints",
             &btDynamicsWorld::getNumConstraints)
        .def("get_constraint",
             DynamicsWorldWrap::getConstraint,
             return_internal_reference<>())
        .add_property("world_type",
                      &btDynamicsWorld::getWorldType)
        .def("clear_forces",
             &btDynamicsWorld::clearForces)
        // TODO: Fix segfault caused by the following property
        /*.add_property("solver_info",
                      make_function(&btDynamicsWorld::getSolverInfo,
                                    return_internal_reference<>()))*/
    ;
}
