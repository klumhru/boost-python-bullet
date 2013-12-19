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
    class_<btQuaternion, bases<btQuadWord> >("btQuaternion")
        // Constructors
        .def(init<btQuaternion>())
        .def(init<const btScalar&, const btScalar&, const btScalar&, const btScalar&>())
        .def(init<const btVector3&, const btScalar&>())
        .def(init<const btScalar&, const btScalar&, const btScalar&>())
        // String ops
        .def(self_ns::repr(self_ns::self))
        .def(self_ns::str(self_ns::self))
        // Operators
        // TODO: Add indexing operators
        .def(self == other<btQuaternion>())
        .def(self != other<btQuaternion>())
        .def(self += other<btQuaternion>())
        .def(self -= other<btQuaternion>())
        .def(self *= other<btScalar>())
        .def(self *= other<btQuaternion>())
        .def(self * other<btScalar>())
        .def(self / other<btScalar>())
        .def(self /= other<btScalar>())
        .def(self + other<btQuaternion>())
        .def(self - other<btQuaternion>())
        .def(-self)
        // Member functions
        .def("set_rotation", &btQuaternion::setRotation)
        .def("set_euler", &btQuaternion::setEuler)
        // TODO: Add set_euler taking 3 scalar params
        .def("set_euler_zyx", &btQuaternion::setEulerZYX)
        .def("dot", &btQuaternion::dot)
        .def_readonly("length", &btQuaternion::length)
        .def_readonly("length2", &btQuaternion::length2)
        .def("normalize", &btQuaternion::normalize,
             return_value_policy<copy_non_const_reference>())
        .def("normalized", &btQuaternion::normalized)
        .def("angle", &btQuaternion::angle)
        .def("angle_shortest_path", &btQuaternion::angleShortestPath)
        .def("get_angle", &btQuaternion::getAngle)
        .def("get_angle_shortest_path", &btQuaternion::getAngleShortestPath)
        .def("get_axis", &btQuaternion::getAxis)
        .def("inverse", &btQuaternion::inverse)
        .def("farthest", &btQuaternion::farthest)
        .def("nearest", &btQuaternion::nearest)
        .def("slerp", &btQuaternion::slerp)
        .def("get_identity", &btQuaternion::getIdentity,
             return_value_policy<copy_const_reference>())
        .staticmethod("get_identity")
        .add_static_property("identity", make_function(&btQuaternion::getIdentity,
                             return_value_policy<copy_const_reference>()))
        ;
}

#endif // _btBoostLinearMathQuaternion_hpp
