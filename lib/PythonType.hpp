//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Python plugin for Zen Scripting
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef INDIEZEN_ZPYTHON_PYTHON_TYPE_HPP_INCLUDED
#define INDIEZEN_ZPYTHON_PYTHON_TYPE_HPP_INCLUDED

#include <Python.h>

#include <Zen/Core/Scripting/I_ScriptType.hpp>

#include <string>
#include <list>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace ZPython {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class PythonModule;
class PythonMethod;

class PythonType
:   public Scripting::I_ScriptType
{
    /// @name Types
    /// @{
public:
    typedef std::list<PythonMethod*>    methods_type;
    /// @}

    /// @name I_ScriptType implementation
    /// @{
public:
    virtual void addMethod(const std::string& _name, const std::string& _docString, void_function_no_args_type _function);
    virtual void addMethod(const std::string& _name, const std::string& _docString, void_function_args_type _function);
    virtual void addMethod(const std::string& _name, const std::string& _docString, object_function_args_type _function);
    virtual void addMethod(const std::string& _name, const std::string& _docString, object_function_no_args_type _function);
    virtual void addMethod(const std::string& _name, const std::string& _docString, string_function_no_args_type _function);
    virtual void addMethod(const std::string& _name, const std::string& _docString, string_function_args_type _function);
    virtual void addMethod(const std::string& _name, const std::string& _docString, bool_function_no_args_type _function);
    virtual void addMethod(const std::string& _name, const std::string& _docString, bool_function_args_type _function);
    virtual void addMethod(const std::string& _name, const std::string& _docString, int_function_no_args_type _function);
    virtual void addMethod(const std::string& _name, const std::string& _docString, int_function_args_type _function);
    virtual void addMethod(const std::string& _name, const std::string& _docString, Scripting::I_ScriptMethod* _function);
    virtual void activate();
    /// @}

    /// @name Additional Implementation
    /// @{
public:
    PyTypeObject*   getRawType();
    //PyObject*       getRawClass();
    const std::string& getName() const;
    PythonModule&   getModule();
    /// @}

    /// @name 'Structors
    /// @{
public:
             PythonType(PythonModule* _pModule, const std::string& _name, const std::string& _docString, unsigned long _rawSize);
    virtual ~PythonType();
    /// @}

    /// @name Member Variables
    /// @{
private:
    PythonModule*           m_pModule;      ///< Module
    std::string             m_name;         ///< Class Name
    std::string             m_docString;    ///< Document String
    std::string             m_fullName;     ///< Full Class Name including module

    PyTypeObject            m_type;
    PyObject*               m_pClass;
    PyObject*               m_pClassDict;

    methods_type            m_methods;
    /// @}

};  // class PythonModule

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
inline
PyTypeObject*
PythonType::getRawType()
{ 
    return &m_type; 
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#if 0
inline
PyObject*
PythonType::getRawClass()
{ 
    return m_pClass; 
}
#endif

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
inline
const std::string&
PythonType::getName() const
{
    return m_name;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
inline
PythonModule&
PythonType::getModule()
{
    return *m_pModule;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace ZPython
}   // namespace IndieZen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // INDIEZEN_ZPYTHON_PYTHON_TYPE_HPP_INCLUDED
