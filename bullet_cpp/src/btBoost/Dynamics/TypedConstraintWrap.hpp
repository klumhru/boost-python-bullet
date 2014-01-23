// File: TypedConstraintWrap.hpp
#ifndef _TypedConstraintWrap_hpp
#define _TypedConstraintWrap_hpp

#include <boost/python.hpp>
#include <btBulletDynamicsCommon.h>

typedef btTypedConstraint::btConstraintInfo2 ConstraintInfo2;

btRigidBody&
(btTypedConstraint::*btTypedConstraint_getRigidBodyA_ref)()
= &btTypedConstraint::getRigidBodyA;

btRigidBody&
(btTypedConstraint::*btTypedConstraint_getRigidBodyB_ref)()
= &btTypedConstraint::getRigidBodyB;

class Constraint2Wrap
{
public:
    static btScalar
    getJ1linearAxis(ConstraintInfo2& info)
    {
        return *info.m_J1linearAxis;
    }
    static void
    setJ1linearAxis(ConstraintInfo2& info, const btScalar val)
    {
        btScalar axis(val);
        info.m_J1linearAxis = &axis;
    }

    static btScalar
    getJ1angularAxis(ConstraintInfo2& info)
    {
        return *info.m_J1angularAxis;
    }
    static void
    setJ1angularAxis(ConstraintInfo2& info, const btScalar val)
    {
        btScalar axis(val);
        info.m_J1angularAxis = &axis;
    }

    static btScalar
    getJ2linearAxis(ConstraintInfo2& info)
    {
        return *info.m_J2linearAxis;
    }
    static void
    setJ2linearAxis(ConstraintInfo2& info, const btScalar val)
    {
        btScalar axis(val);
        info.m_J2linearAxis = &axis;
    }

    static btScalar
    getJ2angularAxis(ConstraintInfo2& info)
    {
        return *info.m_J2angularAxis;
    }
    static void
    setJ2angularAxis(ConstraintInfo2& info, const btScalar val)
    {
        btScalar axis(val);
        info.m_J2angularAxis = &axis;
    }

    static btScalar
    getConstraintError(ConstraintInfo2& info)
    {
        return *info.m_constraintError;
    }
    static void
    setConstraintError(ConstraintInfo2& info, const btScalar val)
    {
        btScalar axis(val);
        info.m_constraintError = &axis;
    }

    static btScalar
    getCfm(ConstraintInfo2& info)
    {
        return *info.cfm;
    }
    static void
    setCfm(ConstraintInfo2& info, const btScalar val)
    {
        btScalar axis(val);
        info.cfm = &axis;
    }

    static btScalar
    getLowerLimit(ConstraintInfo2& info)
    {
        return *info.m_lowerLimit;
    }
    static void
    setLowerLimit(ConstraintInfo2& info, const btScalar val)
    {
        btScalar axis(val);
        info.m_lowerLimit = &axis;
    }

    static btScalar
    getUpperLimit(ConstraintInfo2& info)
    {
        return *info.m_upperLimit;
    }
    static void
    setUpperLimit(ConstraintInfo2& info, const btScalar val)
    {
        btScalar axis(val);
        info.m_upperLimit = &axis;
    }

    static int
    getFIndex(ConstraintInfo2& info)
    {
        return *info.findex;
    }
    static void
    setFIndex(ConstraintInfo2& info, const int val)
    {
        int axis(val);
        info.findex = &axis;
    }
};

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(btTypedConstraint_setParam_overloads,
                                       setParam, 2, 3);

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(btTypedConstraint_getParam_overloads,
                                       getParam, 1, 2);

struct TypedConstraintWrap
{
    static btJointFeedback&
    getJointFeedback(btTypedConstraint& constraint)
    {
        return *constraint.getJointFeedback();
    }

    static void
    setJointFeedback(btTypedConstraint& constraint,
                     btJointFeedback& feedback)
    {
        constraint.setJointFeedback(&feedback);
    }
};

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(btAngularLimit_set_overloads,
                                       set, 2, 5);

struct AngularLimitWrap
{
    static btScalar
    fit(btAngularLimit& limit, btScalar& angle)
    {
        limit.fit(angle);
        return angle;
    }
};

#endif // _TypedConstraintWrap_hpp
