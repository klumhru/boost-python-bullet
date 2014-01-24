#include "btBoostCollision.hpp"

#include <btBoost/Collision/ContactSolverInfo.hpp>
#include <btBoost/Collision/CollisionWorld.hpp>
#include <btBoost/Collision/DynamicsWorld.hpp>
#include <btBoost/Collision/DiscreteDynamicsWorld.hpp>
#include <btBoost/Collision/OverlappingPairCache.hpp>

void defineCollision()
{
    defineContactSolverInfo();
    defineCollisionWorld();
    defineDynamicsWorld();
    defineDiscreteDynamicsWorld();
    defineOverlappingPairCaches();
}
