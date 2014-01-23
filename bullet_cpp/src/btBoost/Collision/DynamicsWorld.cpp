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

    class_<btDynamicsWorld, bases<btCollisionWorld>,
           boost::noncopyable>
        ("btDynamicsWorld", no_init)
        .def("step_simulation",
             &btDynamicsWorld::stepSimulation,
             stepSimulation_overloads())
    ;
}
