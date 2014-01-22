// File: btBoostCollisionOverLappingPairCache.hpp
#ifndef _btBoostCollisionOverLappingPairCache_hpp
#define _btBoostCollisionOverLappingPairCache_hpp

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBoost/Collision/CollisionWorldWrappers.hpp>

// Very thin wrappers for data interchange classes and callbacks
// TODO: Implement the wrappers fully
void defineOverlappingPairCaches();

#endif // _btBoostCollisionOverLappingPairCache_hpp
