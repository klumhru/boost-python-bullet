// File: btBoostLinearMathTransform.hpp
#ifndef _btBoostLinearMathTransform_hpp
#define _btBoostLinearMathTransform_hpp

#include <boost/python.hpp>
#include <LinearMath/btTransform.h>
#include <iostream>
#include "btBoostLinearMathVector3.hpp"
#include "btBoostLinearMathQuaternion.hpp"

using namespace boost::python;
using namespace std;

ostream& operator<<(ostream& os, const btTransform& t)
{
    os << "((" << t.getBasis() << "), (" << t.getOrigin() << "))";
    return os;
}

void defineTransform()
{
    class_<btTransform>("btTransform")
        // Constructors
        .def(init<const btQuaternion&>())
        .def(init<const btQuaternion&, const btVector3&>())
        .def(init<const btMatrix3x3&>())
        .def(init<const btMatrix3x3&, const btVector3&>())
        // String ops
        // Operators
        .def(self == other<btTransform>())
        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        ;
}

#endif // _btBoostLinearMathTransform_hpp
