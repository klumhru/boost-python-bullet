// File: DbvtBroadphase.hpp
#ifndef _DbvtBroadphase_hpp
#define _DbvtBroadphase_hpp

#include <boost/python.hpp>
#include <btBulletCollisionCommon.h>

using namespace boost::python;

void btDbvtBroadphase_collide(btDbvtBroadphase& self, btDispatcher& dispatcher);

void defineDbvtBroadphase();

#endif // _DbvtBroadphase_hpp
