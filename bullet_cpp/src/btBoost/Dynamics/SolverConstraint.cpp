#include "SolverConstraint.hpp"

#include <btBulletDynamicsCommon.h>
#include <boost/python.hpp>
#include <btBoost/LinearMath/AlignedObjectArray.hpp>
#include <btBoost/array_helpers.hpp>

using namespace boost::python;

void defineSolverConstraint()
{
    enum_<btSolverConstraint::btSolverConstraintType>
        ("btSolverConstraintType")
        .value("BT_SOLVER_CONTACT_1D",
               btSolverConstraint::BT_SOLVER_CONTACT_1D)
        .value("BT_SOLVER_FRICTION_1D",
               btSolverConstraint::BT_SOLVER_FRICTION_1D)
    ;

    class_<btConstraintArray>("btConstraintArray")
        // TODO: fix indexing suite so it works with these types of arrays
    ;

    // TODO: Tests
    class_<btSolverConstraint>("btSolverConstraint")
        .def_readwrite("relpos1_cross_normal",
                       &btSolverConstraint::m_relpos1CrossNormal)
        .def_readwrite("contact_normal1",
                       &btSolverConstraint::m_contactNormal1)
        .def_readwrite("relpos2_cross_normal",
                       &btSolverConstraint::m_relpos2CrossNormal)
        .def_readwrite("contact_normal2",
                       &btSolverConstraint::m_contactNormal2)
        .def_readwrite("angular_component_a",
                       &btSolverConstraint::m_angularComponentA)
        .def_readwrite("angular_component_b",
                       &btSolverConstraint::m_angularComponentB)
        .def_readwrite("applied_push_impulse",
                       &btSolverConstraint::m_appliedPushImpulse)
        .def_readwrite("applied_impulse",
                       &btSolverConstraint::m_appliedImpulse)
        .def_readwrite("friction",
                       &btSolverConstraint::m_friction)
        .def_readwrite("jac_diag_ab_inv",
                       &btSolverConstraint::m_jacDiagABInv)
        .def_readwrite("rhs",
                       &btSolverConstraint::m_rhs)
        .def_readwrite("cfm",
                       &btSolverConstraint::m_cfm)
        .def_readwrite("lower_limit",
                       &btSolverConstraint::m_lowerLimit)
        .def_readwrite("upper_limit",
                       &btSolverConstraint::m_upperLimit)
        .def_readwrite("rhs_penetration",
                       &btSolverConstraint::m_rhsPenetration)
        .def_readwrite("override_num_solver_iterations",
                       &btSolverConstraint::m_overrideNumSolverIterations)
        .def_readwrite("friction_index",
                       &btSolverConstraint::m_frictionIndex)
        .def_readwrite("solver_body_id_a",
                       &btSolverConstraint::m_solverBodyIdA)
        .def_readwrite("friction_index",
                       &btSolverConstraint::m_frictionIndex)
        .def_readwrite("solver_body_id_b",
                       &btSolverConstraint::m_solverBodyIdB)

    ;
}
