// File: btBoostDynamics.hpp
#ifndef _btBoostDynamics_hpp
#define _btBoostDynamics_hpp

#include "btBoostDynamicsDbvtBroadphase.hpp"
#include "btBoostDynamicsDefaultCollisionConfiguration.hpp"
#include "btBoostDynamicsCollisionDispatcher.hpp"
#include "btBoostDynamicsSequentialImpulseConstraintSolver.hpp"
#include "btBoostDynamicsShapes.hpp"
#include "btBoostDynamicsRigidBody.hpp"

void defineDynamics()
{
    defineDbvtBroadphase();
    defineDefaultCollisionConfiguration();
    defineCollisionDispatcher();
    defineSequentialImpulseConstraintSolver();
    defineShapes();
    defineRigidBody();
}

#endif // _btBoostDynamics_hpp
