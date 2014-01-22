#include "btBoostCollision.hpp"

#include <btBoost/Collision/DiscreteDynamicsWorld.hpp>
#include <btBoost/Collision/OverlappingPairCache.hpp>

void defineCollision()
{
    defineDiscreteDynamicsWorld();
    defineOverlappingPairCaches();
}
