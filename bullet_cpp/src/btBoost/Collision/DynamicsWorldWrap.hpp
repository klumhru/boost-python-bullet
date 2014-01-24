// File: DynamicsWorldWrap.hpp
#ifndef _DynamicsWorldWrap_hpp
#define _DynamicsWorldWrap_hpp

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <btBulletDynamicsCommon.h>

using namespace boost::python;

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(stepSimulation_overloads,
                                       stepSimulation,
                                       1, 3);



typedef boost::shared_ptr<btDynamicsWorld> btDynamicsWorldPtr;

struct DynamicsWorldWrap
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

    static void
    addAction(btDynamicsWorld& world,
              btActionInterface& action)
    {
      world.addAction(&action);
    }

    static void
    removeAction(btDynamicsWorld& world,
                 btActionInterface& action)
    {
      world.removeAction(&action);
    }

    static void
    addRigidBody(btDynamicsWorld& world,
                 btRigidBody& body)
    {
        world.addRigidBody(&body);
    }

    static void
    addRigidBody_mask_group(btDynamicsWorld& world,
                            btRigidBody& body,
                            short group,
                            short mask)
    {
        world.addRigidBody(&body, group, mask);
    }

    static void
    removeRigidBody(btDynamicsWorld& world,
                    btRigidBody& body)
    {
        world.removeRigidBody(&body);
    }

    static void
    setConstraintSolver(btDynamicsWorld& world,
                        btConstraintSolver& solver)
    {
        world.setConstraintSolver(&solver);
    }

    static btConstraintSolver&
    getConstraintSolver(btDynamicsWorld& world)
    {
        return *world.getConstraintSolver();
    }

    static btTypedConstraint&
    getConstraint(btDynamicsWorld& world,
                  int index)
    {
        return *world.getConstraint(index);
    }
};

#endif // _DynamicsWorldWrap_hpp
