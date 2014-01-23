// File: CollisionWorldWrappers.hpp
#ifndef _CollisionWorldWrappers_hpp
#define _CollisionWorldWrappers_hpp

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <btBulletDynamicsCommon.h>

using namespace boost::python;

typedef boost::shared_ptr<btCollisionWorld> btCollisionWorldPtr;
typedef boost::shared_ptr<btCollisionWorld::LocalRayResult> LocalRayResultPtr;

class btCollisionWorldWrap
{
public:
    static btCollisionWorldPtr
    init(btDispatcher& dispatcher,
         btBroadphaseInterface& pairCache,
         btCollisionConfiguration& config)
    {
        return btCollisionWorldPtr(new btCollisionWorld(&dispatcher,
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

    static void
    rayTestSingle(const btTransform& rayFromTrans,
                  const btTransform& rayToTrans,
                  btCollisionObject& collisionObject,
                  const btCollisionShape& collisionShape,
                  const btTransform& colObjWorldTransform,
                  btCollisionWorld::RayResultCallback& resultCallback)
    {
        btCollisionWorld::rayTestSingle(rayFromTrans,
                                        rayToTrans,
                                        &collisionObject,
                                        &collisionShape,
                                        colObjWorldTransform,
                                        resultCallback);
    }

    static void
    objectQuerySingle(const btConvexShape& castShape,
                      const btTransform& rayFromTrans,
                      const btTransform& rayToTrans,
                      btCollisionObject& collisionObject,
                      const btCollisionShape& collisionShape,
                      const btTransform& colObjWorldTransform,
                      btCollisionWorld::ConvexResultCallback& resultCallback,
                      btScalar allowedPenetration)
    {
        btCollisionWorld::objectQuerySingle(&castShape,
                                            rayFromTrans,
                                            rayToTrans,
                                            &collisionObject,
                                            &collisionShape,
                                            colObjWorldTransform,
                                            resultCallback,
                                            allowedPenetration);
    }

    static void
    addCollisionObject(btCollisionWorld& world,
                       btCollisionObject& obj,
                       short int collisionFilterGroup,
                       short int collisionFilterMask)
    {
        world.addCollisionObject(&obj,
                                 collisionFilterGroup,
                                 collisionFilterMask);
    }

    static void
    removeCollisionObject(btCollisionWorld& world,
                          btCollisionObject& obj)
    {
        world.removeCollisionObject(&obj);
    }
};

class LocalRayResultWrap
{
public:
    static LocalRayResultPtr
    init(const btCollisionObject& collisionObject,
         btCollisionWorld::LocalShapeInfo& localShapeInfo,
         const btVector3& hitNormalLocal,
         btScalar hitFraction)
    {
        return LocalRayResultPtr(new btCollisionWorld::LocalRayResult(
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

typedef boost::shared_ptr<btCollisionWorld::LocalConvexResult> LCRPtr;

struct LocalConvexResultWrap
{
    static LCRPtr
    init(const btCollisionObject&  hitCollisionObject,
         btCollisionWorld::LocalShapeInfo& localShapeInfo,
         const btVector3& hitNormalLocal,
         const btVector3& hitPointLocal,
         btScalar hitFraction)
    {
        return LCRPtr(
            new btCollisionWorld::LocalConvexResult(
                &hitCollisionObject,
                &localShapeInfo,
                hitNormalLocal,
                hitPointLocal,
                hitFraction
            )
        );
    }

    static const btCollisionObject&
    getHitCollisionObject(btCollisionWorld::LocalConvexResult& result)
    {
        return *result.m_hitCollisionObject;
    }

    static void
    setHitCollisionObject(btCollisionWorld::LocalConvexResult& result,
                          btCollisionObject& obj)
    {
        result.m_hitCollisionObject = &obj;
    }

    static btCollisionWorld::LocalShapeInfo&
    getLocalShapeInfo(btCollisionWorld::LocalConvexResult& result)
    {
        return *result.m_localShapeInfo;
    }

    static void
    setLocalShapeInfo(btCollisionWorld::LocalConvexResult& result,
                      btCollisionWorld::LocalShapeInfo& info)
    {
        result.m_localShapeInfo = &info;
    }
};

struct ClosestConvexResultCallbackWrap
{
    static const btCollisionObject&
    getHitCollisionObject(btCollisionWorld::ClosestConvexResultCallback& result)
    {
        return *result.m_hitCollisionObject;
    }

    static void
    setHitCollisionObject(btCollisionWorld::ClosestConvexResultCallback& result,
                          btCollisionObject& obj)
    {
        result.m_hitCollisionObject = &obj;
    }
};

#endif // _CollisionWorldWrappers_hpp
