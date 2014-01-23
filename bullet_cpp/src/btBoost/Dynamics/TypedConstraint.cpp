#include "TypedConstraint.hpp"

#include <boost/python.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBoost/Dynamics/TypedConstraintWrap.hpp>

using namespace boost::python;

void defineTypedConstraint()
{
    enum_<btTypedConstraintType>("btTypedConstraintType")
        .value("POINT2POINT_CONSTRAINT_TYPE", POINT2POINT_CONSTRAINT_TYPE)
        .value("HINGE_CONSTRAINT_TYPE", HINGE_CONSTRAINT_TYPE)
        .value("CONETWIST_CONSTRAINT_TYPE", CONETWIST_CONSTRAINT_TYPE)
        .value("D6_CONSTRAINT_TYPE", D6_CONSTRAINT_TYPE)
        .value("SLIDER_CONSTRAINT_TYPE", SLIDER_CONSTRAINT_TYPE)
        .value("CONTACT_CONSTRAINT_TYPE", CONTACT_CONSTRAINT_TYPE)
        .value("D6_SPRING_CONSTRAINT_TYPE", D6_SPRING_CONSTRAINT_TYPE)
        .value("GEAR_CONSTRAINT_TYPE", GEAR_CONSTRAINT_TYPE)
        .value("FIXED_CONSTRAINT_TYPE", FIXED_CONSTRAINT_TYPE)
        .value("MAX_CONSTRAINT_TYPE", MAX_CONSTRAINT_TYPE)
    ;

    enum_<btConstraintParams>("btConstraintParams")
        .value("BT_CONSTRAINT_ERP", BT_CONSTRAINT_ERP)
        .value("BT_CONSTRAINT_STOP_ERP", BT_CONSTRAINT_STOP_ERP)
        .value("BT_CONSTRAINT_CFM", BT_CONSTRAINT_CFM)
        .value("BT_CONSTRAINT_STOP_CFM", BT_CONSTRAINT_STOP_CFM)
    ;

    class_<btJointFeedback>("btJointFeedback")
        .def_readwrite("applied_force_body_a",
                       &btJointFeedback::m_appliedForceBodyA)
        .def_readwrite("applied_torque_body_a",
                       &btJointFeedback::m_appliedTorqueBodyA)
        .def_readwrite("applied_force_body_b",
                       &btJointFeedback::m_appliedForceBodyB)
        .def_readwrite("applied_torque_body_b",
                       &btJointFeedback::m_appliedTorqueBodyB)
    ;

    class_<btTypedConstraint::btConstraintInfo1>
        ("btConstraintInfo1")
        .def_readwrite("num_constraint_rows",
                       &btTypedConstraint::btConstraintInfo1::m_numConstraintRows)
        .def_readwrite("nub",
                       &btTypedConstraint::btConstraintInfo1::nub)
    ;

    // TODO: Implement tests
    class_<ConstraintInfo2>("ConstraintInfo2")
        .def_readwrite("fps", &ConstraintInfo2::fps)
        .def_readwrite("erp", &ConstraintInfo2::erp)
        .add_property("j1_linear_axis",
                      make_function(Constraint2Wrap::getJ1linearAxis,
                                    return_value_policy<return_by_value>()),
                      Constraint2Wrap::setJ1linearAxis)
        .add_property("j1_angular_axis",
                      make_function(Constraint2Wrap::getJ1angularAxis,
                                    return_value_policy<return_by_value>()),
                      Constraint2Wrap::setJ1angularAxis)
        .add_property("j2_linear_axis",
                      make_function(Constraint2Wrap::getJ2linearAxis,
                                    return_value_policy<return_by_value>()),
                      Constraint2Wrap::setJ2linearAxis)
        .add_property("j2_angular_axis",
                      make_function(Constraint2Wrap::getJ2angularAxis,
                                    return_value_policy<return_by_value>()),
                      Constraint2Wrap::setJ2angularAxis)
        .def_readwrite("rowskip",
                       &ConstraintInfo2::rowskip)
        .add_property("constraint_error",
                      make_function(Constraint2Wrap::getConstraintError,
                                    return_value_policy<return_by_value>()),
                      Constraint2Wrap::setConstraintError)
        .add_property("cfm",
                      make_function(Constraint2Wrap::getCfm,
                                    return_value_policy<return_by_value>()),
                      Constraint2Wrap::setCfm)
        .add_property("cfm",
                      make_function(Constraint2Wrap::getCfm,
                                    return_value_policy<return_by_value>()),
                      Constraint2Wrap::setCfm)
        .add_property("lower_limit",
                      make_function(Constraint2Wrap::getLowerLimit,
                                    return_value_policy<return_by_value>()),
                      Constraint2Wrap::setLowerLimit)
        .add_property("upper_limit",
                      make_function(Constraint2Wrap::getUpperLimit,
                                    return_value_policy<return_by_value>()),
                      Constraint2Wrap::setUpperLimit)
        .add_property("findex",
                      make_function(Constraint2Wrap::getFIndex,
                                    return_value_policy<return_by_value>()),
                      Constraint2Wrap::setFIndex)
        .def_readwrite("num_iterations",
                       &ConstraintInfo2::m_numIterations)
        .def_readwrite("damping",
                       &ConstraintInfo2::m_damping)
    ;

    // TODO: Tests, bitches though they will be...
    class_<btTypedConstraint, bases<btTypedObject>, boost::noncopyable>
        ("btTypedConstraint", no_init)
        // TODO: investigate base constructor implementations
        .add_property("override_num_solver_iterations",
                      &btTypedConstraint::getOverrideNumSolverIterations,
                      &btTypedConstraint::setOverrideNumSolverIterations)
        // Skipping internal functions:
        // buildJacobian, setupSolverConstraint, getInfo1, getInfo2,
        // internalSetAppliedImpulse, internalGetAppliedImpulse
        .add_property("breaking_impulse_threshold",
                      &btTypedConstraint::getBreakingImpulseThreshold,
                      &btTypedConstraint::setBreakingImpulseThreshold)
        .add_property("enabled",
                      &btTypedConstraint::isEnabled,
                      &btTypedConstraint::setEnabled)
        // Skipping internal function:
        // solveConstraintObsolete
        .add_property("rigidbody_a",
                      make_function(btTypedConstraint_getRigidBodyA_ref,
                                    return_internal_reference<>()))
        .add_property("rigidbody_b",
                      make_function(btTypedConstraint_getRigidBodyB_ref,
                                    return_internal_reference<>()))
        .add_property("user_constraint_type",
                      &btTypedConstraint::getUserConstraintType,
                      &btTypedConstraint::setUserConstraintType)
        .add_property("user_constraint_id",
                      &btTypedConstraint::getUserConstraintId,
                      &btTypedConstraint::setUserConstraintId)
        // Skipping void* getUserConstraintPtr
        .add_property("joint_feedback",
                      make_function(TypedConstraintWrap::getJointFeedback,
                                    return_internal_reference<>()),
                      make_function(TypedConstraintWrap::setJointFeedback,
                                    with_custodian_and_ward<1, 2>()))
        .add_property("uid",
                      &btTypedConstraint::getUid)
        .add_property("feedback",
                      &btTypedConstraint::needsFeedback,
                      &btTypedConstraint::enableFeedback)
        .add_property("applied_impulse",
                      &btTypedConstraint::getAppliedImpulse)
        .add_property("typed_constraint_type",
                      &btTypedConstraint::getConstraintType)
        .add_property("dbg_draw_size",
                      &btTypedConstraint::getDbgDrawSize,
                      &btTypedConstraint::setDbgDrawSize)
        .def("set_param", &btTypedConstraint::setParam,
             btTypedConstraint_setParam_overloads())
        .def("get_param", &btTypedConstraint::getParam,
             btTypedConstraint_getParam_overloads())
    ;

    def("adjust_angle_to_limits", &btAdjustAngleToLimits);

    class_<btAngularLimit>("btAngularLimit")
        .def("set", &btAngularLimit::set,
             btAngularLimit_set_overloads())
        .def("test", &btAngularLimit::test)
        .add_property("softness", &btAngularLimit::getSoftness)
        .add_property("bias_factor", &btAngularLimit::getBiasFactor)
        .add_property("relaxation_factor", &btAngularLimit::getRelaxationFactor)
        .add_property("correction", &btAngularLimit::getCorrection)
        .add_property("sign", &btAngularLimit::getSign)
        .add_property("half_range", &btAngularLimit::getHalfRange)
        .add_property("is_limit", &btAngularLimit::isLimit)
        .def("fit", make_function(AngularLimitWrap::fit,
                                  return_value_policy<return_by_value>()))
        .add_property("error", &btAngularLimit::getError)
        .add_property("low", &btAngularLimit::getLow)
        .add_property("high", &btAngularLimit::getHigh)
    ;
}
