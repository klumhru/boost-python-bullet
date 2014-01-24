#include "ContactSolverInfo.hpp"

#include <boost/python.hpp>
#include <btBulletDynamicsCommon.h>

using namespace boost::python;

void defineContactSolverInfo()
{
    enum_<btSolverMode>("btSolverMode")
        .value("SOLVER_RANDMIZE_ORDER", SOLVER_RANDMIZE_ORDER)
        .value("SOLVER_FRICTION_SEPARATE", SOLVER_FRICTION_SEPARATE)
        .value("SOLVER_USE_WARMSTARTING", SOLVER_USE_WARMSTARTING)
        .value("SOLVER_USE_2_FRICTION_DIRECTIONS", SOLVER_USE_2_FRICTION_DIRECTIONS)
        .value("SOLVER_ENABLE_FRICTION_DIRECTION_CACHING", SOLVER_ENABLE_FRICTION_DIRECTION_CACHING)
        .value("SOLVER_DISABLE_VELOCITY_DEPENDENT_FRICTION_DIRECTION", SOLVER_DISABLE_VELOCITY_DEPENDENT_FRICTION_DIRECTION)
        .value("SOLVER_CACHE_FRIENDLY", SOLVER_CACHE_FRIENDLY)
        .value("SOLVER_SIMD", SOLVER_SIMD)
        .value("SOLVER_INTERLEAVE_CONTACT_AND_FRICTION_CONSTRAINTS", SOLVER_INTERLEAVE_CONTACT_AND_FRICTION_CONSTRAINTS)
        .value("SOLVER_ALLOW_ZERO_LENGTH_FRICTION_DIRECTIONS", SOLVER_ALLOW_ZERO_LENGTH_FRICTION_DIRECTIONS)
    ;

    class_<btContactSolverInfoData>("btContactSolverInfoData")
        .def_readwrite("tau", &btContactSolverInfoData::m_tau)
        .def_readwrite("damping", &btContactSolverInfoData::m_damping)
        .def_readwrite("friction", &btContactSolverInfoData::m_friction)
        .def_readwrite("time_step", &btContactSolverInfoData::m_timeStep)
        .def_readwrite("restitution", &btContactSolverInfoData::m_restitution)
        .def_readwrite("num_iterations", &btContactSolverInfoData::m_numIterations)
        .def_readwrite("max_error_reduction", &btContactSolverInfoData::m_maxErrorReduction)
        .def_readwrite("erp", &btContactSolverInfoData::m_erp)
        .def_readwrite("erp2", &btContactSolverInfoData::m_erp2)
        .def_readwrite("global_cfm", &btContactSolverInfoData::m_globalCfm)
        .def_readwrite("split_impulse", &btContactSolverInfoData::m_splitImpulse)
        .def_readwrite("split_impulse_penetration_threshold",
                       &btContactSolverInfoData::m_splitImpulsePenetrationThreshold)
        .def_readwrite("split_impulse_turn_erp",
                       &btContactSolverInfoData::m_splitImpulseTurnErp)
        .def_readwrite("linear_slop", &btContactSolverInfoData::m_linearSlop)
        .def_readwrite("warm_starting_factor",
                       &btContactSolverInfoData::m_warmstartingFactor)
        .def_readwrite("solver_mode", &btContactSolverInfoData::m_solverMode)
        .def_readwrite("resting_contact_restitution_threshold",
                       &btContactSolverInfoData::m_restingContactRestitutionThreshold)
        .def_readwrite("minimum_solver_batch_size",
                       &btContactSolverInfoData::m_minimumSolverBatchSize)
        .def_readwrite("max_gyroscopic_force",
                       &btContactSolverInfoData::m_maxGyroscopicForce)
        .def_readwrite("single_axis_rolling_friction_threshold",
                       &btContactSolverInfoData::m_singleAxisRollingFrictionThreshold)
    ;

    class_<btContactSolverInfo, bases<btContactSolverInfoData> >
        ("btContactSolverInfo")
    ;
}
