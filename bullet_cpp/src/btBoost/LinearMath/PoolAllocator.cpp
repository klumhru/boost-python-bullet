#include "PoolAllocator.hpp"

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
