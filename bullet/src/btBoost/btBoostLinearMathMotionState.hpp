// File: btBoostMotionState.hpp
#ifndef _btBoostMotionState_hpp
#define _btBoostMotionState_hpp

#include <boost/python.hpp>
#include <boost/ref.hpp>
#include <LinearMath/btDefaultMotionState.h>

using namespace boost::python;

ATTRIBUTE_ALIGNED16(struct) btMotionStateWrap
: public btMotionState,
  wrapper<btMotionState>
{
    btMotionStateWrap() : self(0), btMotionState() {}
    btMotionStateWrap(PyObject* p) : self(p), btMotionState() {}

    virtual void getWorldTransform(btTransform& worldTrans ) const
    {
        call_method<void>(self, "getWorldTransform", boost::ref(worldTrans));
    }

    virtual void setWorldTransform(const btTransform& worldTrans)
    {
        this->get_override("setWorldTransform")(worldTrans);
    }

    PyObject* self;
};

void defineMotionState()
{
    class_<btMotionState, btMotionStateWrap, boost::noncopyable>
           ("btMotionState")
        .def("getWorldTransform",
             pure_virtual(&btMotionStateWrap::getWorldTransform))
        .def("setWorldTransform",
             pure_virtual(&btMotionStateWrap::setWorldTransform));

    class_<btDefaultMotionState,
           bases<btMotionState> >("btDefaultMotionState")
        .def(init<const btTransform&>())
        .def(init<const btTransform&, const btTransform&>())
        .def_readwrite("graphics_world_trans",
                       &btDefaultMotionState::m_graphicsWorldTrans)
        .def_readwrite("center_of_mass_offset",
                       &btDefaultMotionState::m_centerOfMassOffset)
        .def_readwrite("start_world_trans",
                       &btDefaultMotionState::m_startWorldTrans)
        .def("get_world_transform", &btDefaultMotionState::getWorldTransform)
        .def("set_world_transform", &btDefaultMotionState::setWorldTransform)
        ;
}

#endif // _btBoostMotionState_hpp
