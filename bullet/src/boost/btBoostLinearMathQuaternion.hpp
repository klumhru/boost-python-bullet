// File: btBoostLinearMathQuaternion.hpp
#ifndef _btBoostLinearMathQuaternion_hpp
#define _btBoostLinearMathQuaternion_hpp

#include <iostream>
#include <boost/python.hpp>
#include <LinearMath/btQuaternion.h>

using namespace boost::python;
using namespace std;

ostream& operator<<(ostream& os, const btQuaternion q)
{
    os << "(" << q.x() << ", " << q.y() << ", " << q.z() << ", " << q.w() << ")";
    return os;
}

void defineQuaternion()
{
    class_<btQuaternion>("btQuaternion")
        // Constructors
        .def(init<btQuaternion>())
        .def(init<const btScalar&, const btScalar&, const btScalar&, const btScalar&>())
        .def(init<const btVector3&, const btScalar&>())
        .def(init<const btScalar&, const btScalar&, const btScalar&>())
        // Operators
        .def(self == other<btQuaternion>())
        .def(self != other<btQuaternion>())
        .def(self_ns::repr(self_ns::self))
        .def(self_ns::str(self_ns::self))
        // Member functions
        .def("set_rotation", &btQuaternion::setRotation)
        .def("set_euler", &btQuaternion::setEuler)
        .def("set_euler_zyx", &btQuaternion::setEulerZYX)
        ;
}

#endif // _btBoostLinearMathQuaternion_hpp
