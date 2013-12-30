// File: btBoostLinearMathMatrix3x3.hpp
#ifndef _btBoostLinearMathMatrix3x3_hpp
#define _btBoostLinearMathMatrix3x3_hpp

#include <iostream>
#include <boost/python.hpp>
#include <LinearMath/btMatrix3x3.h>

using namespace boost::python;
using namespace std;

ostream& operator<<(ostream& os, const btMatrix3x3& m)
{
    btVector3 a = m.getColumn(0),
        b = m.getColumn(1),
        c = m.getColumn(2);
    os << "("
       << "(" << a.x() << ", " << a.y() << ", " << a.z() << "), "
       << "(" << b.x() << ", " << b.y() << ", " << b.z() << "), "
       << "(" << c.x() << ", " << c.y() << ", " << c.z() << "))";
    return os;
}

btVector3& m3x3_get_item_mutable(btMatrix3x3& m, int i)
{
    return m[i];
}

btVector3& m3x3_set_item(btMatrix3x3& m, int i, const btVector3& v)
{
    return m[i] = v;
}

void defineMatrix3x3()
{
    class_<btMatrix3x3>("btMatrix3x3")
        // Constructors
        .def(init<const btQuaternion&>())
        .def(init<const btScalar&, const btScalar&, const btScalar&,
                  const btScalar&, const btScalar&, const btScalar&,
                  const btScalar&, const btScalar&, const btScalar&>())
        .def(init<const btMatrix3x3&>())
        // String operators
        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))
        // Operators
        .def("__getitem__", &m3x3_get_item_mutable,
             return_value_policy<copy_non_const_reference>())
        .def("__setitem__", &m3x3_set_item,
             return_value_policy<copy_non_const_reference>())
        .def(self *= other<btMatrix3x3>())
        .def(self * other<btMatrix3x3>())
        .def(self * other<btScalar>())
        .def(self += other<btMatrix3x3>())
        .def(self + other<btMatrix3x3>())
        .def(self -= other<btMatrix3x3>())
        .def(self - other<btMatrix3x3>())
        .def(self == other<btMatrix3x3>())
        // Member functions
        .def("get_row", &btMatrix3x3::getRow,
             return_value_policy<copy_const_reference>())
        .def("get_column", &btMatrix3x3::getColumn,
             return_value_policy<return_by_value>())
        // TODO: add identity property
        ;
}

#endif // _btBoostLinearMathMatrix3x3_hpp
