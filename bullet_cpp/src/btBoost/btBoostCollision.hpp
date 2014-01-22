// File: btBoostCollision.hpp
#ifndef _btBoostCollision_hpp
#define _btBoostCollision_hpp

#include <btBoost/Collision/DiscreteDynamicsWorld.hpp>
#include <btBoost/Collision/OverlappingPairCache.hpp>

void defineCollision()
{
    defineDiscreteDynamicsWorld();
    defineOverlappingPairCaches();
}

#endif // _btBoostCollision_hpp
