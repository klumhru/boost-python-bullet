// File: btBoostDynamics.hpp
#ifndef _btBoostDynamics_hpp
#define _btBoostDynamics_hpp

#include <boost/python.hpp>
#include "btBoostLinearMathScalar.hpp"
#include "btBoostLinearMathVector3.hpp"
#include "btBoostLinearMathQuadWord.hpp"
#include "btBoostLinearMathQuaternion.hpp"

void defineLinearMath()
{
    defineScalar();
    defineVector3();
    defineQuadWord();
    defineQuaternion();
}

#endif // _btBoostDynamics_hpp
