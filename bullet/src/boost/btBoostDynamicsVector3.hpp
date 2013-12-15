// File: btBoostDynamicsVector3.hpp
#ifndef _btBoostDynamicsVector3_hpp
#define _btBoostDynamicsVector3_hpp

#include <boost/python.hpp>
#include <LinearMath/btVector3.h>

using namespace boost::python;

void defineVector3()
{
    class_<btVector3>("btVector3");
}

#endif // _btBoostDynamicsVector3_hpp
