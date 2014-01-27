#include "DiscreteDynamicsWorld.hpp"

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btSimulationIslandManager.h>
#include <btBoost/Collision/DiscreteDynamicsWorldWrap.hpp>

using namespace boost::python;

void defineDiscreteDynamicsWorld()
{
    class_<btDiscreteDynamicsWorld, bases<btDynamicsWorld>,
           boost::noncopyable>
        ("btDiscreteDynamicsWorld", no_init)
        .def("__init__", make_constructor(&DiscreteDynamicsWorldWrap::init))
        .def("synchronize_single_motion_state",
             DiscreteDynamicsWorldWrap::synchronizeSingleMotionState)
        .add_property("simulation_island_manager",
                      make_function(DiscreteDynamicsWorldWrap::getSimulationIslandManager,
                                    return_internal_reference<>()))
        .add_property("collision_world",
                      make_function(DiscreteDynamicsWorldWrap::getCollisionWorld,
                                    return_internal_reference<>()))
        .add_property("synchronize_all_motion_states",
                      &btDiscreteDynamicsWorld::getSynchronizeAllMotionStates,
                      &btDiscreteDynamicsWorld::setSynchronizeAllMotionStates)
        .add_property("apply_speculative_contact_restitution",
                      &btDiscreteDynamicsWorld::getApplySpeculativeContactRestitution,
                      &btDiscreteDynamicsWorld::setApplySpeculativeContactRestitution)
        .add_property("latency_motion_state_interpolation",
                      &btDiscreteDynamicsWorld::getLatencyMotionStateInterpolation,
                      &btDiscreteDynamicsWorld::setLatencyMotionStateInterpolation)
    ;
}
