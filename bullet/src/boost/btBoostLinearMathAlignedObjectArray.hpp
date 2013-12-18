// File: btBoostLinearMathAlignedObjectArray.hpp
#ifndef _btBoostLinearMathAlignedObjectArray_hpp
#define _btBoostLinearMathAlignedObjectArray_hpp

#include <boost/python/suite/indexing/indexing_suite.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python.hpp>
#include <boost/ref.hpp>
#include <LinearMath/btAlignedObjectArray.h>

using namespace boost::python;

// We need a DerivedPolicy object so we can use indexing_suite
// Ref: 1: http://stackoverflow.com/questions/18882089/wrapping-arrays-in-boost-python
//      2: http://www.boost.org/doc/libs/1_53_0/libs/python/doc/v2/indexing.html

/// Following section taken from Ref: 1 with some minor changes
///
/// @brief Policy type for referenced indexing, meeting the DerivedPolicies
///        requirement of boost::python::index_suite.
///
/// @note Requires Container to support:
///          - value_type and size_type types,
///          - value_type is default constructable and copyable,
///          - element access via operator[],
///          - Default constructable, iterator constructable,
///          - begin(), end(), and size() member functions
template <typename Container>
class ref_index_suite
  : public boost::python::indexing_suite<Container,
      ref_index_suite<Container>, true, true>
{
public:

    typedef typename Container::value_type data_type;
    typedef typename Container::size_type  index_type;
    typedef typename Container::size_type  size_type;

    // Element access and manipulation.

    /// @brief Get element from container.
    static data_type&
    get_item(Container& container, index_type index)
    {
        return container.at(index);
    }

    /// @brief Set element from container.
    static void
    set_item(Container& container, index_type index, const data_type& value)
    {
        container[index] = value;
    }

    /// @brief Reset index to default value.
    static void
    delete_item(Container& container, index_type index)
    {
        container.remove(container.at(index));
    };

    // Slice support.

    /// @brief Get slice from container.
    ///
    /// @return Python object containing
    static boost::python::object
    get_slice(Container& container, index_type from, index_type to)
    {
        using boost::python::list;
        if (from > to) return list();

        // Return copy, as container only references its elements.
        list list;
        while (from != to) list.append(container[from++]);
        return list;
    };

    /// @brief Set a slice in container with a given value.
    static void
    set_slice(Container& container, index_type from,
              index_type to, const data_type& value)
    {
        // If range is invalid, return early.
        if (from > to) return;

        // Populate range with value.
        while (from < to) container[from++] = value;
    }

    /// @brief Set a slice in container with another range.
    template <class Iterator>
    static void
    set_slice(Container& container, index_type from,
              index_type to, Iterator first, Iterator last)
    {
        // If range is invalid, return early.
        if (from > to) return;

        // Populate range with other range.
        while (from < to) container[from++] = *first++;
    }

    /// @brief Reset slice to default values.
    static void
    delete_slice(Container& container, index_type from, index_type to)
    {
        if(from > to) return;

        while(from < to) container.remove(container.at(from++));
    }

    // Capacity.

    /// @brief Get size of container.
    static std::size_t
    size(Container& container) { return container.size(); }

    /// @brief Check if a value is within the container.
    template <class T>
    static bool
    contains(Container& container, const T& value)
    {
        return container.findLinearSearch(value) < container.size();
    }

    /// @brief Minimum index supported for container.
    static index_type
    get_min_index(Container& /*container*/)
    {
        return 0;
    }

    /// @brief Maximum index supported for container.
    static index_type
    get_max_index(Container& container)
    {
        return container.size()-1;
    }

    // Misc.

    /// @brief Convert python index (could be negative) to a valid container
    ///        index with proper boundary checks.
    static index_type
    convert_index(Container& container, PyObject* object)
    {
        namespace python = boost::python;
        python::extract<long> py_index(object);

        // If py_index cannot extract a long, then type the type is wrong so
        // set error and return early.
        if (!py_index.check())
        {
            PyErr_SetString(PyExc_TypeError, "Invalid index type");
            python::throw_error_already_set();
            return index_type();
        }

        // Extract index.
        long index = py_index();

        // Adjust negative index.
        if (index < 0)
            index += container.size();

        // Boundary check.
        if (index >= long(container.size()) || index < 0)
        {
            PyErr_SetString(PyExc_IndexError, "Index out of range");
            python::throw_error_already_set();
        }

        return index;
    }

    static bool
    compare_index(Container& container, index_type a, index_type b)
    {
          return container[a] < container[b];
    }
};

typedef btAlignedObjectArray<btVector3> btVector3Array;

void defineAlignedObjectArray()
{
    class_<btVector3Array>("btVector3Array")
        .def(init<btVector3Array>())
        .def(ref_index_suite<btVector3Array>())
        .def("append", &btVector3Array::push_back)
    ;
}

#endif // _btBoostLinearMathAlignedObjectArray_hpp
