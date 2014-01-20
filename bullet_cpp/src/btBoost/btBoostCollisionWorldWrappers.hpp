// File: btBoostCollisionWorldWrappers.hpp
#ifndef _btBoostCollisionWorldWrappers_hpp
#define _btBoostCollisionWorldWrappers_hpp

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <btBulletDynamicsCommon.h>

using namespace boost::python;

typedef boost::shared_ptr<btCollisionWorld> btColWorldPtr;
typedef boost::shared_ptr<btDiscreteDynamicsWorld> btDdwPtr;
typedef boost::shared_ptr<btCollisionWorld::LocalRayResult> btLocalRayResPtr;

class btCollisionWorldWrap
{
public:
    static btColWorldPtr
    init(btDispatcher& dispatcher,
         btBroadphaseInterface& pairCache,
         btCollisionConfiguration& config)
    {
        return btColWorldPtr(new btCollisionWorld(&dispatcher,
                                                  &pairCache,
                                                  &config));
    }

    static void
    setBroadphase(btCollisionWorld& world,
                  btBroadphaseInterface& interface)
    {
        world.setBroadphase(&interface);
    }

    static void
    updateSingleAabb(btCollisionWorld& world,
                     btCollisionObject& obj)
    {
        world.updateSingleAabb(&obj);
    }
};

class LocalRayResultWrap
{
public:
    static btLocalRayResPtr
    init(const btCollisionObject& collisionObject,
         btCollisionWorld::LocalShapeInfo& localShapeInfo,
         const btVector3& hitNormalLocal,
         btScalar hitFraction)
    {
        return btLocalRayResPtr(new btCollisionWorld::LocalRayResult(
                                &collisionObject,
                                &localShapeInfo,
                                hitNormalLocal,
                                hitFraction));
    }

    static const btCollisionObject&
    getCollisionObject(btCollisionWorld::LocalRayResult& result)
    {
        return *result.m_collisionObject;
    }
};

struct RayResultCallbackWrap
: btCollisionWorld::RayResultCallback,
  boost::python::wrapper<btCollisionWorld::RayResultCallback>
{
    btScalar
    addSingleResult(btCollisionWorld::LocalRayResult& rayResult,
                    bool normalInWorldSpace)
    {
        return this->get_override("addSingleResult")(rayResult, normalInWorldSpace);
    }

    static bool
    needsCollision(btCollisionWorld::RayResultCallback& callback,
                   btBroadphaseProxy& proxy)
    {
        return callback.needsCollision(&proxy);
    }

    static const btCollisionObject*
    getCollisionObject(btCollisionWorld::RayResultCallback& cb)
    {
        return cb.m_collisionObject;
    }

    static void
    setCollisionObject(btCollisionWorld::RayResultCallback& cb,
                       btCollisionObject& obj)
    {
        cb.m_collisionObject = &obj;
    }
};

class btDiscreteDynamicsWorldWrap
{
public:
    static btColWorldPtr
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


#endif // _btBoostCollisionWorldWrappers_hpp
