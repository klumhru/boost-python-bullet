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

btVector3 abs(const btVector3& v)
{
    return v.absolute();
}

// TODO: Define static methods for the 6 directional axes

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
        .add_property("w", make_function(&btVector3::w, return_value_policy<copy_const_reference>()),
                      &btVector3::setW)
        // Convenience stream operator for str() representation
        // self_ns is explicit to resolve
        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))
        // Operators
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
        .def(self_ns::abs(self_ns::self))
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
             return_value_policy<copy_non_const_reference>())
        .def_readonly("normalized", &btVector3::normalized)
        .def("rotate", &btVector3::rotate)
        .def("angle", &btVector3::angle)
        .def("absolute", &btVector3::absolute)
        .def("set_max", &btVector3::setMax)
        .def("set_min", &btVector3::setMin)
        .def_readonly("min_axis", &btVector3::minAxis)
        .def_readonly("max_axis", &btVector3::maxAxis)
        .def_readonly("closest_axis", &btVector3::closestAxis)
        .def_readonly("furthest_axis", &btVector3::furthestAxis)
        .def("set_value", &btVector3::setValue)
        .def("getSkewSymmetricMatrix", &btVector3::getSkewSymmetricMatrix)
        .def("set_zero", &btVector3::setZero)
        .def_readonly("is_zero", &btVector3::isZero)
        .def_readonly("fuzzy_zero", &btVector3::fuzzyZero)
        .def("cross", &btVector3::cross)
        .def("set_interpolate_3", &btVector3::setInterpolate3)
        .def("lerp", &btVector3::lerp)
        .def("dot3", &btVector3::dot3);
}

#endif // _btBoostDynamicsVector3_hpp
