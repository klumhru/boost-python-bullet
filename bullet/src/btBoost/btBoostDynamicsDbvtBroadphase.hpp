// File: btBoostDynamicsDbvtBroadphase.hpp
#ifndef _btBoostDynamicsDbvtBroadphase_hpp
#define _btBoostDynamicsDbvtBroadphase_hpp

#include <boost/python.hpp>
#include <btBulletCollisionCommon.h>

using namespace boost::python;

void defineDbvtBroadphase()
{
    class_<btDbvt, boost::noncopyable>("btDbvt");
    class_<btDbvtBroadphase>("btDbvtBroadphase");
}

#endif // _btBoostDynamicsDbvtBroadphase_hpp
