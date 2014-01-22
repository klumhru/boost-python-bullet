#include "Scalar.hpp"

#include <LinearMath/btScalar.h>
#include <boost/python.hpp>

using namespace boost::python;

void defineScalar()
{
    def("btRadians", &btRadians);
    def("btDegrees", &btDegrees);
}
