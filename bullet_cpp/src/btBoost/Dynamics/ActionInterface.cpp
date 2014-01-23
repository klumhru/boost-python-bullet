#include "ActionInterface.hpp"

#include <boost/python.hpp>
#include <btBulletDynamicsCommon.h>

using namespace boost::python;

struct ActionInterfaceWrap
: btActionInterface,
  wrapper<btActionInterface>
{
    virtual void debugDraw(btIDebugDraw* debugDrawer)
    {}

    virtual void updateAction(btCollisionWorld* world,
                              btScalar deltaTime)
    {
        this->get_override("updateAction")(world, deltaTime);
    }
};

void defineActionInterface()
{
    class_<ActionInterfaceWrap, boost::noncopyable>
        ("btActionInterface")
        .def("update_action",
             &ActionInterfaceWrap::updateAction)
    ;
}
