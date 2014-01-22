// File: btBoostLinearMathTransform.hpp
#ifndef _btBoostLinearMathTransform_hpp
#define _btBoostLinearMathTransform_hpp

#include <boost/python.hpp>
#include <LinearMath/btTransform.h>
#include <iostream>
#include <btBoost/LinearMath/Vector3.hpp>
#include <btBoost/LinearMath/Quaternion.hpp>

using namespace boost::python;
using namespace std;

ostream& operator<<(ostream& os, const btTransform& t)
{
    os << "basis" << t.getBasis() << ", origin" << t.getOrigin() << "";
    return os;
}

const btMatrix3x3& (btTransform::*get_basis)() const = &btTransform::getBasis;
btMatrix3x3& (btTransform::*get_basis_ref)() = &btTransform::getBasis;
const btVector3& (btTransform::*get_origin)() const = &btTransform::getOrigin;
btVector3& (btTransform::*get_origin_ref)() = &btTransform::getOrigin;

void defineTransform()
{
    class_<btTransform>("btTransform")
        // Constructors
        .def(init<const btTransform&>())
        .def(init<const btQuaternion&>())
        .def(init<const btQuaternion&, const btVector3&>())
        .def(init<const btMatrix3x3&>())
        .def(init<const btMatrix3x3&, const btVector3&>())
        // String ops
        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))
        // Operators
        .def(self == other<btTransform>())
        .def(self * other<btVector3>())
        .def(self * other<btTransform>())
        .def(self *= other<btTransform>())
        // Member functions
        .def("mult", &btTransform::mult)
        .def("get_basis", get_basis,
             return_value_policy<copy_const_reference>())
        .def("set_basis", &btTransform::setBasis)
        .def("get_rotation", &btTransform::getRotation)
        .def("set_rotation", &btTransform::setRotation)
        .def("get_origin", get_origin,
             return_value_policy<copy_const_reference>())
        .def("set_origin", &btTransform::setOrigin)
        // Properties
        .add_property("basis",
                      make_function(get_basis_ref,
                                    return_internal_reference<>()),
                      &btTransform::setBasis)
        .add_property("origin",
                      make_function(get_origin_ref,
                                    return_internal_reference<>()),
                      &btTransform::setOrigin)
        .add_static_property("identity",
            make_function(btTransform::getIdentity,
                          return_value_policy<copy_const_reference>()))
        .def("set_identity", &btTransform::setIdentity)
        .def("inverse", &btTransform::inverse)
        .def("inv_xform", &btTransform::invXform)
        .def("inverse_times", &btTransform::inverseTimes)

        ;
}

#endif // _btBoostLinearMathTransform_hpp
