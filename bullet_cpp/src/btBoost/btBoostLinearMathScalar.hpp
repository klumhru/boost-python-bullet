// File: btScalar.hpp
#ifndef _btScalar_hpp
#define _btScalar_hpp

#include <LinearMath/btScalar.h>
#include <boost/python.hpp>

using namespace boost::python;

void defineScalar()
{
    def("btRadians", &btRadians);
    def("btDegrees", &btDegrees);
}

#endif // _btScalar_hpp
