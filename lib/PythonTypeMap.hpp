//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Python plugin for Zen Scripting
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef INDIEZEN_ZPYTHON_PYTHON_TYPE_MAP_HPP_INCLUDED
#define INDIEZEN_ZPYTHON_PYTHON_TYPE_MAP_HPP_INCLUDED

#include <Python.h>

#include <vector>
#include <map>

#include <boost/any.hpp>
#include <boost/function.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace ZPython {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

/// Map from any type to boost::any with support for creating parameter lists
class PythonTypeMap
{
    /// @name Types
    /// @{
public:
    typedef boost::function<void (std::vector<boost::any>&, PyObject*)> function_type;
    typedef std::map<_typeobject *, function_type>                      map_type;
    /// @}

    /// @name PythonTypeMap implementation
    /// @{
public:
    /// Convert and push_back a PyObject onto a parameter list.
    bool push_back(std::vector<boost::any>& _parms, PyObject* _pObject);
    /// @}

    /// @name 'Structors
    /// @{
public:
             PythonTypeMap();
    virtual ~PythonTypeMap();
    /// @}

    /// @name Member Variables
    /// @{
private:
    map_type    m_map;
    /// @}

};  // class PythonTypeMap
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace ZPython
}   // namespace IndieZen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // INDIEZEN_ZPYTHON_PYTHON_TYPE_MAP_HPP_INCLUDED

