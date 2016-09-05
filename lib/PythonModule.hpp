//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Python plugin for Zen Scripting
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
// Copyright (C)        2008 Matthew Alan Gray
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef INDIEZEN_ZPYTHON_PYTHON_MODULE_HPP_INCLUDED
#define INDIEZEN_ZPYTHON_PYTHON_MODULE_HPP_INCLUDED

#include <Python.h>

#include <Zen/Core/Memory/managed_ptr.hpp>
#include <Zen/Core/Memory/managed_weak_ptr.hpp>
#include <Zen/Core/Scripting/I_ScriptEngine.hpp>
#include <Zen/Core/Scripting/I_ScriptModule.hpp>
#include <Zen/Core/Scripting/I_ScriptObject.hpp>

#include <string>
#include <map>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace ZPython {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class PythonEngine;
class PythonType;

class PythonModule
:   public Scripting::I_ScriptModule
{
    /// @name Types
    /// @{
public:
    typedef Zen::Memory::managed_ptr<Scripting::I_ScriptEngine>         pScriptEngine_type;

    typedef Zen::Memory::managed_ptr<Scripting::I_ScriptType>           pScriptType_type;
    typedef Zen::Memory::managed_weak_ptr<Scripting::I_ScriptType>      wpScriptType_type;

    typedef Zen::Memory::managed_ptr<Scripting::I_ScriptObject>         pScriptObject_type;
    typedef Zen::Memory::managed_weak_ptr<Scripting::I_ScriptObject>    wpScriptObject_type;

    typedef Scripting::I_ObjectReference*                               pObjectReference_type;

    typedef std::map<std::string, pScriptType_type>                     type_collection_type;
    /// @}

    /// @name I_ScriptModule implementation
    /// @{
public:
    virtual pScriptType_type createScriptType(const std::string& _typeName, const std::string& _docString, unsigned long _rawSize);
    virtual pScriptType_type getScriptType(const std::string& _typeName);
    virtual void activate();
    virtual void createObject(pScriptType_type _pType, pObjectReference_type _pObject);
    virtual void createGlobalObject(const std::string& _name, pScriptType_type _pType, pObjectReference_type _pObject);
    virtual pScriptEngine_type getScriptEngine();
    /// @}

    /// @name Additional Implementation
    /// @{
public:
    const std::string& getName() const;
    PyObject* newObject(pScriptType_type _pType, pObjectReference_type _pObject);
    PythonEngine& getEngine();
    /// @}

    /// @name Event handlers
    /// @{
public:
    void onDestroyScriptType(wpScriptType_type _pScriptType);
    void onDestroyScriptObject(wpScriptObject_type _pScriptObject);
    /// @}

    /// @name 'Structors
    /// @{
public:
             PythonModule(PythonEngine* _pEngine, const std::string& _name, const std::string& _docString);
    virtual ~PythonModule();
    /// @}

    /// @name Member Variables
    /// @{
private:
    PythonEngine*           m_pEngine;
    std::string             m_name;
    std::string             m_docString;

    type_collection_type    m_types;

    PyObject*               m_pModule;
    PyObject*               m_pModuleDict;

    /// @}

};  // class PythonModule

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace ZPython
}   // namespace IndieZen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // INDIEZEN_ZPYTHON_PYTHON_MODULE_HPP_INCLUDED
