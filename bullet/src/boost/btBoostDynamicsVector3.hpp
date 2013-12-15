// File: btBoostDynamicsVector3.hpp
#ifndef _btBoostDynamicsVector3_hpp
#define _btBoostDynamicsVector3_hpp

#include <iostream>
#include <boost/python.hpp>
#include <LinearMath/btVector3.h>

using namespace boost::python;
using namespace std;

ostream& operator<<(ostream& os, const btVector3& v)
{
    os << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")";
    return os;
}

void defineVector3()
{
    class_<btVector3>("btVector3",
                      init<>())
        // Constructors
        .def(init<btScalar, btScalar, btScalar>())
        .def(init<btVector3>())
        // Accessors
        .add_property("x", make_function(&btVector3::getX, return_value_policy<copy_const_reference>()),
                      &btVector3::setX)
        .add_property("y", make_function(&btVector3::getY, return_value_policy<copy_const_reference>()),
                      &btVector3::setY)
        .add_property("z", make_function(&btVector3::getZ, return_value_policy<copy_const_reference>()),
                      &btVector3::setZ)
        // Operators
        .def(self_ns::str(self_ns::self))
        .def(self + other<btVector3>())
        .def(self += other<btVector3>())
        .def(self - other<btVector3>())
        .def(self -= other<btVector3>())
        .def(self / other<btScalar>())
        .def(self /= other<btScalar>())
        .def(self * other<btScalar>())
        .def(self *= other<btVector3>())
        .def(self *= other<btScalar>())
        .def(self == other<btVector3>())
        .def(self != other<btVector3>())
        .def(-self)
        // Member functions
        .def("dot", &btVector3::dot)
        .def_readonly("length2", &btVector3::length2)
        .def_readonly("length_sqr", &btVector3::length2)
        .def_readonly("length", &btVector3::length)
        .def_readonly("norm", &btVector3::norm)
        .def("distance2", &btVector3::distance2)
        .def("distance_sqr", &btVector3::distance2)
        .def("distance", &btVector3::distance)
        .def("safe_normalize", &btVector3::safeNormalize,
             return_value_policy<copy_non_const_reference>())
        .def("normalize", &btVector3::normalize,
             return_value_policy<copy_non_const_reference>());
}

#endif // _btBoostDynamicsVector3_hpp
