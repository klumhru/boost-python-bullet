#include "btBoostCollision.hpp"

#include <btBoost/Collision/CollisionWorld.hpp>
#include <btBoost/Collision/DynamicsWorld.hpp>
#include <btBoost/Collision/DiscreteDynamicsWorld.hpp>
#include <btBoost/Collision/OverlappingPairCache.hpp>

void defineCollision()
{
    defineCollisionWorld();
    defineDynamicsWorld();
    defineDiscreteDynamicsWorld();
    defineOverlappingPairCaches();
}
