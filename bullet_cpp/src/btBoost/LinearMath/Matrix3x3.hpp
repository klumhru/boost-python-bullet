// File: Matrix3x3.hpp
#ifndef _Matrix3x3_hpp
#define _Matrix3x3_hpp

#include <iostream>
#include <boost/python.hpp>
#include <LinearMath/btMatrix3x3.h>

using namespace boost::python;
using namespace std;

ostream& operator<<(ostream& os, const btMatrix3x3& m);

void defineMatrix3x3();

#endif // _Matrix3x3_hpp
