// File: btBoostDynamicsDbvtBroadphase.hpp
#ifndef _btBoostDynamicsDbvtBroadphase_hpp
#define _btBoostDynamicsDbvtBroadphase_hpp

#include <boost/python.hpp>
#include <btBulletCollisionCommon.h>

using namespace boost::python;

void btDbvtBroadphase_collide(btDbvtBroadphase& self, btDispatcher& dispatcher)
{
    self.collide(&dispatcher);
}

void defineDbvtBroadphase()
{
    class_<btDbvt, boost::noncopyable>("btDbvt");

    class_<btDbvtNode, boost::noncopyable>("btDbvtNode");

    class_<btCollisionDispatcher, boost::noncopyable>("btCollisionDispatcher",
        init<btCollisionConfiguration*>());

    class_<btDbvtProxy>("btDbvtProxy",
        init<const btVector3&, const btVector3&,
             void*, short int, short int>());

    enum_<btDbvtBroadphase::Config>("btDbvtBroadphase_Config")
        .value("DYNAMIC_SET", btDbvtBroadphase::DYNAMIC_SET)
        .value("FIXED_SET", btDbvtBroadphase::FIXED_SET)
        .value("STAGECOUNT", btDbvtBroadphase::STAGECOUNT)
        .export_values()
    ;

    class_<btBroadphaseInterface, boost::noncopyable>
        ("btBroadphaseInterface", no_init)
    ;

    class_<btDbvtBroadphase, bases<btBroadphaseInterface>, boost::noncopyable>
        ("btDbvtBroadphase")
        // Tons of properties
        .add_property("prediction", &btDbvtBroadphase::m_prediction)
        .add_property("stage_current", &btDbvtBroadphase::m_stageCurrent)
        .add_property("fupdates", &btDbvtBroadphase::m_fupdates)
        .add_property("dupdates", &btDbvtBroadphase::m_dupdates)
        .add_property("cupdates", &btDbvtBroadphase::m_cupdates)
        .add_property("newpairs", &btDbvtBroadphase::m_newpairs)
        .add_property("fixedleft", &btDbvtBroadphase::m_fixedleft)
        .add_property("updates_call", &btDbvtBroadphase::m_updates_call)
        .add_property("updates_done", &btDbvtBroadphase::m_updates_done)
        .add_property("updates_ratio", &btDbvtBroadphase::m_updates_ratio)
        .add_property("pid", &btDbvtBroadphase::m_pid)
        .add_property("cid", &btDbvtBroadphase::m_cid)
        .add_property("gid", &btDbvtBroadphase::m_gid)
        .add_property("releasepaircache", &btDbvtBroadphase::m_releasepaircache)
        .add_property("deferedcollide", &btDbvtBroadphase::m_deferedcollide)
        .add_property("needcleanup", &btDbvtBroadphase::m_needcleanup)
    ;
}

#endif // _btBoostDynamicsDbvtBroadphase_hpp
