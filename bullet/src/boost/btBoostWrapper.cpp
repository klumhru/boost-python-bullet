#ifndef BT_BOOST_WRAPPER_HW
#define BT_BOOST_WRAPPER_HW

#include <boost/python.hpp>
#include "btBoostDynamics.hpp"


const char* hello_world()
{
    return "Hello world";
}


BOOST_PYTHON_MODULE(bullet)
{
    using namespace boost::python;

    def("hello_world", &hello_world);

    defineDynamics();
}

#endif // BT_BOOST_WRAPPER_HW
