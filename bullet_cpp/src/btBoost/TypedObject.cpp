#include "TypedObject.hpp"

#include <boost/python.hpp>
#include <LinearMath/btScalar.h>

using namespace boost::python;

void defineTypedObject()
{
    // TODO: Implement tests
    class_<btTypedObject>("btTypedObject",
                          init<int>())
        .def_readwrite("object_type",
                       &btTypedObject::m_objectType)
    ;
}
