#include "SequentialImpulseConstraintSolver.hpp"

#include <boost/python.hpp>
#include <btBulletDynamicsCommon.h>

using namespace boost::python;

void defineSequentialImpulseConstraintSolver()
{
    class_<btConstraintSolver, boost::noncopyable>
        ("btConstraintSolver", no_init)
    ;
    class_<btSequentialImpulseConstraintSolver,
           bases<btConstraintSolver>, boost::noncopyable>
        ("btSequentialImpulseConstraintSolver")
    ;
}
