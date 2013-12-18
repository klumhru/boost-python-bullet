// File: btBoostLinearMathTransformUtil.hpp
#ifndef _btBoostLinearMathTransformUtil_hpp
#define _btBoostLinearMathTransformUtil_hpp

#include <boost/python.hpp>
#include <LinearMath/btTransformUtil.h>

void defineTransformUtil()
{
    class_<btTransformUtil>("btTransformUtil")
        .def("integrate_transform", btTransformUtil::integrateTransform)
        .staticmethod("integrate_transform");
}

#endif // _btBoostLinearMathTransformUtil_hpp
