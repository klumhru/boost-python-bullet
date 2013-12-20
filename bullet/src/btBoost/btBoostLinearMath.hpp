// File: btBoostLinearMath.hpp
#ifndef _btBoostLinearMath_hpp
#define _btBoostLinearMath_hpp

#include "btBoostLinearMathScalar.hpp"
#include "btBoostLinearMathVector3.hpp"
#include "btBoostLinearMathQuadWord.hpp"
#include "btBoostLinearMathQuaternion.hpp"
#include "btBoostLinearMathMatrix3x3.hpp"
#include "btBoostLinearMathTransform.hpp"
#include "btBoostLinearMathTransformUtil.hpp"
#include "btBoostLinearMathMotionState.hpp"
#include "btBoostLinearMathAlignedObjectArray.hpp"

void defineLinearMath()
{
    defineScalar();
    defineVector3();
    defineQuadWord();
    defineQuaternion();
    defineMatrix3x3();
    defineTransform();
    defineMotionState();
    defineAlignedObjectArray();
    defineTransformUtil();
}

#endif // _btBoostLinearMath_hpp
