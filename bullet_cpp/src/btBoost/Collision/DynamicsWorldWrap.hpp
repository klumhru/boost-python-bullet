// File: DynamicsWorldWrap.hpp
#ifndef _DynamicsWorldWrap_hpp
#define _DynamicsWorldWrap_hpp

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <btBulletDynamicsCommon.h>

using namespace boost::python;

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(stepSimulation_overloads,
                                       stepSimulation,
                                       1, 3)

typedef boost::shared_ptr<btDynamicsWorld> btDynamicsWorldPtr;

class btDynamicsWorldWrap
{
    static void
    addConstraint(btDynamicsWorld& world,
                  btTypedConstraint& constraint)
    {
        world.addConstraint(&constraint);
    }

    static void
    removeConstraint(btDynamicsWorld& world,
                     btTypedConstraint& constraint)
    {
        world.removeConstraint(&constraint);
    }
};

#endif // _DynamicsWorldWrap_hpp
