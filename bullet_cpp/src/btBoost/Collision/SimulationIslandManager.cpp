#include "SimulationIslandManager.hpp"

#include <boost/python.hpp>
#include <BulletCollision/CollisionDispatch/btSimulationIslandManager.h>
#include <btBoost/Collision/SimulationIslandManagerWrap.hpp>

using namespace boost::python;

btElement&
(btUnionFind::*btUnionFind_getElement_ref)(int) = &btUnionFind::getElement;

int
(btUnionFind::*btUnionFind_find1)(int) = &btUnionFind::find;
int
(btUnionFind::*btUnionFind_find2)(int, int) = &btUnionFind::find;


void defineSimulationIslandManager()
{
    class_<btElement>("btElement")
        .def_readwrite("id", &btElement::m_id)
        .def_readwrite("sz", &btElement::m_sz)
    ;

    class_<btUnionFind>("btUnionFind")
        .def("sort_islands", &btUnionFind::sortIslands)
        .def("reset", &btUnionFind::reset)
        .add_property("num_elements",
                      &btUnionFind::getNumElements)
        .add_property("is_root",
                      &btUnionFind::isRoot)
        .def("get_element", btUnionFind_getElement_ref,
             return_internal_reference<>())
        .def("allocate", &btUnionFind::allocate)
        .def("free", &btUnionFind::Free)
        .def("find", btUnionFind_find1)
        .def("find", btUnionFind_find2)
        .def("unite", &btUnionFind::unite)
    ;

    class_<btSimulationIslandManager>
        ("btSimulationIslandManager")
        .def("init_union_find", &btSimulationIslandManager::initUnionFind)
        .def("get_union_find", &btSimulationIslandManager::getUnionFind,
             return_internal_reference<>())
        // TODO: Implement IslandCallback if needed
        .add_property("split_islands",
                      &btSimulationIslandManager::getSplitIslands,
                      &btSimulationIslandManager::setSplitIslands)
    ;
}
