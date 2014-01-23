#include "OverlappingPairCache.hpp"

#include <boost/python.hpp>
#include <btBulletDynamicsCommon.h>

using namespace boost::python;


void defineOverlappingPairCaches()
{
    class_<btOverlapCallback, boost::noncopyable>
        ("btOverlapCallback", no_init)
    ;

    class_<btOverlapFilterCallback, boost::noncopyable>
        ("btOverlapFilterCallback", no_init)
    ;

    class_<btOverlappingPairCallback, boost::noncopyable>
        ("btOverlappingPairCallback", no_init)
    ;

    class_<btOverlappingPairCache, bases<btOverlappingPairCallback>,
           boost::noncopyable>
        ("btOverlappingPairCache", no_init)
    ;

    class_<btHashedOverlappingPairCache, bases<btOverlappingPairCache> >
        ("btHashedOverlappingPairCache")
    ;

    class_<btSortedOverlappingPairCache, bases<btOverlappingPairCache> >
        ("btSortedOverlappingPairCache")
    ;

    class_<btNullPairCache, bases<btOverlappingPairCache> >
        ("btNullPairCache")
    ;
}
