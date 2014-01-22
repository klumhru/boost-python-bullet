// File: CollisionDispatcher.hpp
#ifndef _CollisionDispatcher_hpp
#define _CollisionDispatcher_hpp

#include <btBulletDynamicsCommon.h>

btCollisionDispatcher*
make_CollisionDispatcher(btCollisionConfiguration& config);

void defineCollisionDispatcher();

#endif // _CollisionDispatcher_hpp
