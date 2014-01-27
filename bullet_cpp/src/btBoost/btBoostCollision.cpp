#include "btBoostCollision.hpp"

#include <btBoost/Collision/ContactSolverInfo.hpp>
#include <btBoost/Collision/SimulationIslandManager.hpp>
#include <btBoost/Collision/CollisionWorld.hpp>
#include <btBoost/Collision/DynamicsWorld.hpp>
#include <btBoost/Collision/DiscreteDynamicsWorld.hpp>
#include <btBoost/Collision/OverlappingPairCache.hpp>

void defineCollision()
{
    defineContactSolverInfo();
    defineSimulationIslandManager();
    defineCollisionWorld();
    defineDynamicsWorld();
    defineDiscreteDynamicsWorld();
    defineOverlappingPairCaches();
}
