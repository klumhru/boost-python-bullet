#include "QuadWord.hpp"

#include <boost/python.hpp>

using namespace boost::python;

ostream& operator<<(ostream& os, const btQuadWord& w)
{
    os << "(" << w.x() << ", " << w.y() << ", "
        << w.z() << ", " << w.w() << ")";
    return os;
}

void (btQuadWord::*setValue3)(const btScalar&,
                              const btScalar&,
                              const btScalar&) = &btQuadWord::setValue;
void (btQuadWord::*setValue4)(const btScalar&,
                              const btScalar&,
                              const btScalar&,
                              const btScalar&) = &btQuadWord::setValue;

void defineQuadWord()
{
    class_<btQuadWord>("btQuadWord")
        // Constructors
        .def(init<btQuadWord>())
        .def(init<btScalar, btScalar, btScalar>())
        .def(init<btScalar, btScalar, btScalar, btScalar>())
        // Properties
        .add_property("x", make_function(&btQuadWord::x,
                      return_value_policy<copy_const_reference>()),
                      &btQuadWord::setX)
        .add_property("y", make_function(&btQuadWord::y,
                      return_value_policy<copy_const_reference>()),
                      &btQuadWord::setY)
        .add_property("z", make_function(&btQuadWord::z,
                      return_value_policy<copy_const_reference>()),
                      &btQuadWord::setZ)
        .add_property("w", make_function(&btQuadWord::w,
                      return_value_policy<copy_const_reference>()),
                      &btQuadWord::setW)
        // Operators
        .def(self == other<btQuadWord>())
        .def(self != other<btQuadWord>())
        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))
        // Member functions
        .def("set_value", setValue3)
        .def("set_value", setValue4)
        .def("set_max", &btQuadWord::setMax)
        .def("set_min", &btQuadWord::setMin)
        ;
}

