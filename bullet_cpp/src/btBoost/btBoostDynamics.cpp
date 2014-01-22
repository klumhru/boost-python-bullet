#include "btBoostDynamics.hpp"

#include <btBoost/Dynamics/DbvtBroadphase.hpp>
#include <btBoost/Dynamics/DefaultCollisionConfiguration.hpp>
#include <btBoost/Dynamics/CollisionDispatcher.hpp>
#include <btBoost/Dynamics/SequentialImpulseConstraintSolver.hpp>
#include <btBoost/Dynamics/Shapes.hpp>
#include <btBoost/Dynamics/RigidBody.hpp>

void defineDynamics()
{
    defineDbvtBroadphase();
    defineDefaultCollisionConfiguration();
    defineCollisionDispatcher();
    defineSequentialImpulseConstraintSolver();
    defineShapes();
    defineRigidBody();
}

