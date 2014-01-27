// File: DiscreteDynamicsWorldWrap.hpp
#ifndef _DiscreteDynamicsWorldWrap_hpp
#define _DiscreteDynamicsWorldWrap_hpp

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

typedef boost::shared_ptr<btDiscreteDynamicsWorld> DiscreteDynamicsWorldPtr;

class DiscreteDynamicsWorldWrap
{
public:
    static DiscreteDynamicsWorldPtr
    init(btDispatcher& dispatcher,
         btBroadphaseInterface& pairCache,
         btConstraintSolver& solver,
         btCollisionConfiguration& config)
    {
        return DiscreteDynamicsWorldPtr(
            new btDiscreteDynamicsWorld(&dispatcher,
                                        &pairCache,
                                        &solver,
                                        &config)
        );
    }

    static void
    addCollisionObject(btDiscreteDynamicsWorld& world,
                       btCollisionObject& object)
    {
        world.addCollisionObject(&object);
    }

    static void
    removeCollisionObject(btDiscreteDynamicsWorld& world,
                          btCollisionObject& object)
    {
        world.removeCollisionObject(&object);
    }

    static void
    addRigidBody(btDiscreteDynamicsWorld& world,
                 btRigidBody& body)
    {
        world.addRigidBody(&body);
    }

    static void
    removeRigidBody(btDiscreteDynamicsWorld& world,
                    btRigidBody& body)
    {
        world.removeRigidBody(&body);
    }

    static void
    setConstraintSolver(btDiscreteDynamicsWorld& world,
                        btConstraintSolver& solver)
    {
        world.setConstraintSolver(&solver);
    }

    static void
    synchronizeSingleMotionState(btDiscreteDynamicsWorld& world,
                                 btRigidBody& body)
    {
        world.synchronizeSingleMotionState(&body);
    }

    static btSimulationIslandManager&
    getSimulationIslandManager(btDiscreteDynamicsWorld& world)
    {
        return *world.getSimulationIslandManager();
    }

    static btCollisionWorld&
    getCollisionWorld(btDiscreteDynamicsWorld& world)
    {
        return *world.getCollisionWorld();
    }
};


#endif // _DiscreteDynamicsWorldWrap_hpp
