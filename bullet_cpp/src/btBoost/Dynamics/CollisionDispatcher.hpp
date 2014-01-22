// File: CollisionDispatcher.hpp
#ifndef _CollisionDispatcher_hpp
#define _CollisionDispatcher_hpp

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <btBulletDynamicsCommon.h>

using namespace boost::python;

btCollisionDispatcher*
make_CollisionDispatcher(btCollisionConfiguration& config);

void defineCollisionDispatcher();

#endif // _CollisionDispatcher_hpp
