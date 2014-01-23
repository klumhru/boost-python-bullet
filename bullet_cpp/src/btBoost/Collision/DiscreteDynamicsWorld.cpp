#include "DiscreteDynamicsWorld.hpp"

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBoost/Collision/DiscreteDynamicsWorldWrap.hpp>

using namespace boost::python;

void defineDiscreteDynamicsWorld()
{
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
