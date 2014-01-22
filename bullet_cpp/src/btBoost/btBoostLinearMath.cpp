#include "btBoostLinearMath.hpp"


#include <btBoost/LinearMath/Scalar.hpp>
#include <btBoost/LinearMath/Vector3.hpp>
#include <btBoost/LinearMath/QuadWord.hpp>
#include <btBoost/LinearMath/Quaternion.hpp>
#include <btBoost/LinearMath/Matrix3x3.hpp>
#include <btBoost/LinearMath/Transform.hpp>
#include <btBoost/LinearMath/TransformUtil.hpp>
#include <btBoost/LinearMath/MotionState.hpp>
#include <btBoost/LinearMath/AlignedObjectArray.hpp>

void defineLinearMath()
{
    defineScalar();
    defineVector3();
    defineQuadWord();
    defineQuaternion();
    defineMatrix3x3();
    defineTransform();
    defineMotionState();
    defineTransformUtil();
    definePrimitiveArrays();
}
