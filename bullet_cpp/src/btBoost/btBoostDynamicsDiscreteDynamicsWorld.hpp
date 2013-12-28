// File: btBoostDynamicsDiscreteDynamicsWorld.hpp
#ifndef _btBoostDynamicsDiscreteDynamicsWorld_hpp
#define _btBoostDynamicsDiscreteDynamicsWorld_hpp

#include <boost/python.hpp>
#include <btBulletDynamicsCommon.h>

using namespace boost::python;

btDiscreteDynamicsWorld*
init_btDiscreteDynamicsWorld(
    btDispatcher& dispatcher,
    btBroadphaseInterface& pairCache,
    btConstraintSolver& solver,
    btCollisionConfiguration& config
) {
    return new btDiscreteDynamicsWorld(&dispatcher,
                                       &pairCache,
                                       &solver,
                                       &config);
}

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(ddw_step_overloads,
                                       stepSimulation,
                                       1, 3);

void defineDiscreteDynamicsWorld()
{
    class_<btDynamicsWorld, boost::noncopyable>("btDynamicsWorld", no_init);

    class_<btDiscreteDynamicsWorld, bases<btDynamicsWorld>, boost::noncopyable>
        ("btDiscreteDynamicsWorld", no_init)
        .def("__init__", make_constructor(&init_btDiscreteDynamicsWorld))
        .def("step_simulation", &btDiscreteDynamicsWorld::stepSimulation,
             ddw_step_overloads())
        .def("synchronize_motion_states",
             &btDiscreteDynamicsWorld::synchronizeMotionStates)
        .def("set_gravity",
             &btDiscreteDynamicsWorld::setGravity)
        .def("get_gravity",
             &btDiscreteDynamicsWorld::getGravity)
        .add_property("gravity",
                      &btDiscreteDynamicsWorld::getGravity,
                      &btDiscreteDynamicsWorld::setGravity)
    ;
}

#endif // _btBoostDynamicsDiscreteDynamicsWorld_hpp
