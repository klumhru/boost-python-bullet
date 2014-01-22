// File: TransformUtil.hpp
#ifndef _TransformUtil_hpp
#define _TransformUtil_hpp

#include <LinearMath/btTransformUtil.h>

btScalar
calculate_diff_axis_angle_quaternion(const btQuaternion& orn0,
                                     const btQuaternion& orn1,
                                     btVector3& axis);

btScalar
calculate_diff_axis_angle(const btTransform& t1,
                          const btTransform& t2,
                          btVector3& axis);

void defineTransformUtil();

#endif // _TransformUtil_hpp
