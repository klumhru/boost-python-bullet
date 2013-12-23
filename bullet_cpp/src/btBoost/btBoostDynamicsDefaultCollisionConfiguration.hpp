// File: btBoostDynamicsDefaultCollisionConfiguration.hpp
#ifndef _btBoostDynamicsDefaultCollisionConfiguration_hpp
#define _btBoostDynamicsDefaultCollisionConfiguration_hpp

#include <boost/python.hpp>
#include <btBulletDynamicsCommon.h>
#include "btBoostLinearMathPoolAllocator.hpp"

using namespace boost::python;

void defineDefaultCollisionConfiguration()
{
	class_<btDefaultCollisionConstructionInfo>("btDefaultCollisionConstructionInfo")
		.add_property("persistentManifoldPool",
			&btDefaultCollisionConstructionInfo::m_persistentManifoldPool)
		.add_property("collisionAlgorithmPool",
			&btDefaultCollisionConstructionInfo::m_collisionAlgorithmPool)
		.add_property("defaultMaxPersistentManifoldPoolSize",
			&btDefaultCollisionConstructionInfo::m_defaultMaxPersistentManifoldPoolSize)
		.add_property("defaultMaxCollisionAlgorithmPoolSize",
			&btDefaultCollisionConstructionInfo::m_defaultMaxCollisionAlgorithmPoolSize)
		.add_property("customCollisionAlgorithmMaxElementSize",
			&btDefaultCollisionConstructionInfo::m_customCollisionAlgorithmMaxElementSize)
		.add_property("useEpaPenetrationAlgorithm",
			&btDefaultCollisionConstructionInfo::m_useEpaPenetrationAlgorithm)
	;

    class_<btCollisionConfiguration,
           boost::noncopyable>("btCollisionConfiguration", no_init)
    ;

    class_<btDefaultCollisionConfiguration,
           bases<btCollisionConfiguration> >("btDefaultCollisionConfiguration",
                                     init<const btDefaultCollisionConstructionInfo&>())
    ;
}

#endif // _btBoostDynamicsDefaultCollisionConfiguration_hpp
