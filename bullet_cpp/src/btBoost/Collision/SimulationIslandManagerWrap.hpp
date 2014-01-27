// File: SimulationIslandManagerWrap.hpp
#ifndef _SimulationIslandManagerWrap_hpp
#define _SimulationIslandManagerWrap_hpp

#include <boost/python.hpp>
#include <BulletCollision/CollisionDispatch/btSimulationIslandManager.h>

using namespace boost::python;

class IslandCallbackWrap
: btSimulationIslandManager::IslandCallback,
  wrapper<btSimulationIslandManager::IslandCallback>
{
    // TOOD: Deferring implementation of virtual calls
};

class SimulationIslandManagerWrap
{

};

#endif // _SimulationIslandManagerWrap_hpp
