// File: btBoostSequentialImpulseConstraintSolver.hpp
#ifndef _btBoostSequentialImpulseConstraintSolver_hpp
#define _btBoostSequentialImpulseConstraintSolver_hpp

#include <boost/python.hpp>
#include <btBulletDynamicsCommon.h>

using namespace boost::python;

void defineSequentialImpulseConstraintSolver()
{
    class_<btSequentialImpulseConstraintSolver,
           bases<btConstraintSolver> >(
        "btSequentialImpulseConstraintSolver")
    ;
}

#endif // _btBoostSequentialImpulseConstraintSolver_hpp
