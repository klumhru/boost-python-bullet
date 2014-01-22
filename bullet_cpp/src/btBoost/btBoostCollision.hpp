// File: btBoostCollision.hpp
#ifndef _btBoostCollision_hpp
#define _btBoostCollision_hpp

#include "Collision/DiscreteDynamicsWorld.hpp"
#include "Collision/OverlappingPairCache.hpp"

void defineCollision()
{
    defineDiscreteDynamicsWorld();
    defineOverlappingPairCaches();
}

#endif // _btBoostCollision_hpp
