// File: btBoostLinearMathTransform.hpp
#ifndef _btBoostLinearMathTransform_hpp
#define _btBoostLinearMathTransform_hpp

#include <LinearMath/btTransform.h>
#include <iostream>

using namespace std;

ostream& operator<<(ostream& os, const btTransform& t);

void defineTransform();

#endif // _btBoostLinearMathTransform_hpp
