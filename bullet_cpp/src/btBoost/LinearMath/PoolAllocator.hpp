// File: btBoostLinearMathPoolAllocator.hpp
#ifndef _btBoostLinearMathPoolAllocator_hpp
#define _btBoostLinearMathPoolAllocator_hpp

#include <boost/python.hpp>
#include <LinearMath/btPoolAllocator.h>

using namespace boost::python;

void definePoolAllocator()
{
	class_<btPoolAllocator>("btPoolAllocator", init<int, int>())
		.def_readonly("free_count", &btPoolAllocator::getFreeCount)
		.def_readonly("used_count" ,&btPoolAllocator::getUsedCount)
		.def_readonly("max_count", &btPoolAllocator::getMaxCount)
		.def_readonly("element_size", &btPoolAllocator::getElementSize)
	;
}

#endif // _btBoostLinearMathPoolAllocator_hpp
