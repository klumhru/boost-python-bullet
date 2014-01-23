// File: btBoostWrapper.cpp
#ifndef _btBoostWrapper_cpp
#define _btBoostWrapper_cpp

#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wreorder"

#include <boost/python.hpp>
#include <btBoost/btBoostLinearMath.hpp>
#include <btBoost/btBoostDynamics.hpp>
#include <btBoost/btBoostCollision.hpp>
#include <btBoost/btBoostHello.hpp>
#include <btBoost/TypedObject.hpp>

using namespace boost::python;

BOOST_PYTHON_MODULE(bullet)
{
    defineHello();
    defineTypedObject();
    defineLinearMath();
    defineCollision();
    defineDynamics();
}

#endif // _btBoostWrapper_cpp
