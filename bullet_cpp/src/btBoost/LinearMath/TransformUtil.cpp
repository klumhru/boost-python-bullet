#include "TransformUtil.hpp"

#include <boost/python.hpp>

using namespace boost::python;

btScalar
calculate_diff_axis_angle_quaternion(const btQuaternion& orn0,const btQuaternion& orn1,btVector3& axis)
{
    btScalar angle;
    btTransformUtil::calculateDiffAxisAngleQuaternion(
        orn0, orn1, axis, angle
    );
    return angle;
}

btScalar
calculate_diff_axis_angle(const btTransform& t1,
                          const btTransform& t2,
                          btVector3& axis)
{
    btScalar angle;
    btTransformUtil::calculateDiffAxisAngle(t1, t2, axis, angle);
    return angle;
}

void defineTransformUtil()
{
    class_<btTransformUtil>("btTransformUtil")
        .def("integrate_transform", btTransformUtil::integrateTransform)
        .staticmethod("integrate_transform")
        .def("calculate_velocity_quaternion",
             btTransformUtil::calculateVelocityQuaternion)
        .staticmethod("calculate_velocity_quaternion")
        .def("calculate_diff_axis_angle_quaternion",
             calculate_diff_axis_angle_quaternion)
        .staticmethod("calculate_diff_axis_angle_quaternion")
        .def("calculate_velocity", btTransformUtil::calculateVelocity)
        .staticmethod("calculate_velocity")
        .def("calculate_diff_axis_angle",
             calculate_diff_axis_angle)
        .staticmethod("calculate_diff_axis_angle")
    ;
}

