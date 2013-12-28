// File: btBoostDynamics.hpp
#ifndef _btBoostDynamics_hpp
#define _btBoostDynamics_hpp

#include "btBoostDynamicsDbvtBroadphase.hpp"
#include "btBoostDynamicsDefaultCollisionConfiguration.hpp"
#include "btBoostDynamicsCollisionDispatcher.hpp"
#include "btBoostDynamicsSequentialImpulseConstraintSolver.hpp"
#include "btBoostDynamicsDiscreteDynamicsWorld.hpp"

void defineDynamics()
{
    defineDbvtBroadphase();
    defineDefaultCollisionConfiguration();
    defineCollisionDispatcher();
    defineSequentialImpulseConstraintSolver();
    defineDiscreteDynamicsWorld();
}

#endif // _btBoostDynamics_hpp
