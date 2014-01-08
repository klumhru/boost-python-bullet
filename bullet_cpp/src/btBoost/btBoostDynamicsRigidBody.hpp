// File: btBoostDynamicsRigidBody.hpp
#ifndef _btBoostDynamicsRigidBody_hpp
#define _btBoostDynamicsRigidBody_hpp

#include <boost/python.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include "btBoostLinearMathAlignedObjectArray.hpp"

using namespace boost::python;

void defineRigidBody()
{
    enum_<btRigidBodyFlags>("btRigidBodyFlags")
        .value("BT_DISABLE_WORLD_GRAVITY", BT_DISABLE_WORLD_GRAVITY)
        .value("BT_ENABLE_GYROPSCOPIC_FORCE", BT_ENABLE_GYROPSCOPIC_FORCE)
    ;


    class_<btCollisionObjectArray>("btCollisionObjectArray")
        .def(init<btCollisionObjectArray>())
        .def(bt_ref_index_suite<btCollisionObjectArray>())
        .def("append", &btCollisionObjectArray::push_back)
    ;
}

#endif // _btBoostDynamicsRigidBody_hpp
