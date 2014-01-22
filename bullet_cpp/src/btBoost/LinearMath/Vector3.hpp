// File: Vector3.hpp
#ifndef _Vector3_hpp
#define _Vector3_hpp

#include <iostream>
#include <boost/python.hpp>
#include <LinearMath/btVector3.h>
#include <btBoost/LinearMath/AlignedObjectArray.hpp>

using namespace boost::python;
using namespace std;

// TODO: Define static methods for the 6 directional axes

typedef btAlignedObjectArray<btVector3> btVector3Array;

void defineVector3();

#endif // _Vector3_hpp
