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

void defineDiscreteDynamicsWorld()
{
    class_<btDiscreteDynamicsWorld>("btDiscreteDynamicsWorld", no_init)
        .def("__init__", make_constructor(&init_btDiscreteDynamicsWorld))

    ;
}

#endif // _btBoostDynamicsDiscreteDynamicsWorld_hpp
