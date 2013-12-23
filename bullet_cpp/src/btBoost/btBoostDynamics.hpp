// File: btBoostDynamics.hpp
#ifndef _btBoostDynamics_hpp
#define _btBoostDynamics_hpp

#include "btBoostDynamicsDbvtBroadphase.hpp"
#include "btBoostDynamicsDefaultCollisionConfiguration.hpp"
#include "btBoostDynamicsCollisionDispatcher.hpp"

void defineDynamics()
{
    defineDbvtBroadphase();
    defineDefaultCollisionConfiguration();
    defineCollisionDispatcher();
}

#endif // _btBoostDynamics_hpp
