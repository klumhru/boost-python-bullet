// File: QuadWord.hpp
#ifndef _QuadWord_hpp
#define _QuadWord_hpp

#include <iostream>
#include <LinearMath/btQuadWord.h>

using namespace std;

ostream& operator<<(ostream& os, const btQuadWord& w);

void defineQuadWord();

#endif // _QuadWord_hpp
