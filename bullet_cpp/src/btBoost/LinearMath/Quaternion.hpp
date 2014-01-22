// File: Quaternion.hpp
#ifndef _Quaternion_hpp
#define _Quaternion_hpp

#include <iostream>
#include <LinearMath/btQuaternion.h>

using namespace std;

ostream& operator<<(ostream& os, const btQuaternion q);

void defineQuaternion();

#endif // _Quaternion_hpp
