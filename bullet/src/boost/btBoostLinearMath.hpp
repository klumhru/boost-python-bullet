// File: btBoostDynamics.hpp
#ifndef _btBoostDynamics_hpp
#define _btBoostDynamics_hpp

#include <boost/python.hpp>
#include "btBoostLinearMathScalar.hpp"
#include "btBoostLinearMathVector3.hpp"
#include "btBoostLinearMathQuadWord.hpp"
#include "btBoostLinearMathQuaternion.hpp"
#include "btBoostLinearMathMatrix3x3.hpp"
#include "btBoostLinearMathTransform.hpp"
#include "btBoostLinearMathMotionState.hpp"
#include "btBoostLinearMathAlignedObjectArray.hpp"

// TODO: implement btAlignedObjectArray somewhere, it's needed to pass arrays
//       back and forth

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
}

#endif // _btBoostDynamics_hpp
