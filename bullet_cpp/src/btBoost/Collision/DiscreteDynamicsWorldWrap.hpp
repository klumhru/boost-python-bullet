// File: DiscreteDynamicsWorldWrap.hpp
#ifndef _DiscreteDynamicsWorldWrap_hpp
#define _DiscreteDynamicsWorldWrap_hpp

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <btBulletDynamicsCommon.h>

typedef boost::shared_ptr<btDiscreteDynamicsWorld> btDdwPtr;

class btDiscreteDynamicsWorldWrap
{
public:
    static btDdwPtr
    init(btDispatcher& dispatcher,
         btBroadphaseInterface& pairCache,
         btConstraintSolver& solver,
         btCollisionConfiguration& config)
    {
        return btDdwPtr(new btDiscreteDynamicsWorld(&dispatcher,
                                                    &pairCache,
                                                    &solver,
                                                    &config));
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
};


#endif // _DiscreteDynamicsWorldWrap_hpp
