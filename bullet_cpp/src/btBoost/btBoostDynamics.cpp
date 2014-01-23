#include "btBoostDynamics.hpp"

#include <btBoost/Dynamics/DbvtBroadphase.hpp>
#include <btBoost/Dynamics/ActionInterface.hpp>
#include <btBoost/Dynamics/TypedConstraint.hpp>
#include <btBoost/Dynamics/DefaultCollisionConfiguration.hpp>
#include <btBoost/Dynamics/CollisionDispatcher.hpp>
#include <btBoost/Dynamics/SequentialImpulseConstraintSolver.hpp>
#include <btBoost/Dynamics/Shapes.hpp>
#include <btBoost/Dynamics/RigidBody.hpp>
#include <btBoost/Dynamics/SolverConstraint.hpp>

void defineDynamics()
{
    defineSolverConstraint();
    defineDbvtBroadphase();
    defineDefaultCollisionConfiguration();
    defineCollisionDispatcher();
    defineSequentialImpulseConstraintSolver();
    defineShapes();
    defineRigidBody();
    defineActionInterface();
    defineTypedConstraint();
}

