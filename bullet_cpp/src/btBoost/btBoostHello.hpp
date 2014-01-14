// File: btBoostHello.hpp
#ifndef _btBoostHello_hpp
#define _btBoostHello_hpp

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include <boost/python.hpp>

using namespace boost::python;

struct Data
{
    Data(): a(0), b(0) {}
    virtual ~Data() {}
    int a;
    float b;
};

inline bool operator==(const Data& lv, const Data& rv)
{
    return lv.a == rv.a && rv.b == rv.b;
}

class Hello
{
    Data m_data;

public:
    void setData(const Data& v)
    {
        m_data = v;
    }

    const Data& getData() const
    {
        return m_data;
    }

};

inline bool operator==(const Hello& lv, const Hello& rv)
{
    return lv.getData() == rv.getData();
}

using namespace std;

ostream& operator<<(ostream& os, const Data& v)
{
    os << "(a: " << v.a << ", b: " << v.b << ")";
    return os;
}

void defineHello()
{
    class_<Data>("Data")
        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))
        .def(self == other<Data>())
        .def_readwrite("a", &Data::a)
        .def_readwrite("b", &Data::b)
    ;

    class_<Hello>("Hello")
        .def(self == other<Hello>())
        .add_property("data",
                      make_function(&Hello::getData,
                      return_value_policy<copy_const_reference>()),
                      &Hello::setData)
    ;
}

#endif // _btBoostHello_hpp
