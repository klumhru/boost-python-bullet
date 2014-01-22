#include "AlignedObjectArray.hpp"

void definePrimitiveArrays()
{
    // TODO: Needs tests
    class_<btIntArray>("btIntArray")
        .def(init<btIntArray>())
        .def(bt_ref_index_suite<btIntArray>())
        .def("append", &btIntArray::push_back)
    ;

    // TODO: Needs tests
    class_<btUIntArray>("btUIntArray")
        .def(init<btUIntArray>())
        .def(bt_ref_index_suite<btUIntArray>())
        .def("append", &btUIntArray::push_back)
    ;

    // TODO: Needs tests
    class_<btScalarArray>("btScalarArray")
        .def(init<btScalarArray>())
        .def(bt_ref_index_suite<btScalarArray>())
        .def("append", &btScalarArray::push_back)
    ;
}

