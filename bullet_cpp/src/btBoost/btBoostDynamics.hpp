// File: btBoostDynamics.hpp
#ifndef _btBoostDynamics_hpp
#define _btBoostDynamics_hpp

#include "btBoostDynamicsDbvtBroadphase.hpp"
#include "btBoostDynamicsDefaultCollisionConfiguration.hpp"
#include "btBoostDynamicsCollisionDispatcher.hpp"
#include "btBoostDynamicsSequentialImpulseConstraintSolver.hpp"
#include "btBoostDynamicsDiscreteDynamicsWorld.hpp"
#include "btBoostDynamicsShapes.hpp"
#include "btBoostDynamicsRigidBody.hpp"
#include "btBoostCollisionOverLappingPairCache.hpp"

void defineDynamics()
{
    defineDbvtBroadphase();
    defineDefaultCollisionConfiguration();
    defineCollisionDispatcher();
    defineSequentialImpulseConstraintSolver();
    defineDiscreteDynamicsWorld();
    defineShapes();
    defineRigidBody();
    defineOverlappingPairCaches();
}

#endif // _btBoostDynamics_hpp
