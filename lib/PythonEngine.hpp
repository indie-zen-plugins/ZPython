//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Python plugin for Zen Scripting
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
// Copyright (C)        2008 Matthew Alan Gray
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef INDIEZEN_ZPYTHON_PYTHON_ENGINE_HPP_INCLUDED
#define INDIEZEN_ZPYTHON_PYTHON_ENGINE_HPP_INCLUDED

#include <Zen/Core/Memory/managed_ptr.hpp>
#include <Zen/Core/Memory/managed_weak_ptr.hpp>
#include <Zen/Core/Memory/managed_self_ref.hpp>

#include <Zen/Core/Scripting/I_ScriptEngine.hpp>
#include <Zen/Core/Scripting/I_ObjectHeap.hpp>

#include "PythonHeap.hpp"
#include "PythonTypeMap.hpp"

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace ZPython {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
class PythonObject;

class PythonEngine
:   public Scripting::I_ScriptEngine
,   public Memory::managed_self_ref<Scripting::I_ScriptEngine>
{
    /// @name Types
    /// @{
public:
    typedef Zen::Memory::managed_ptr<Scripting::I_ObjectHeap>           pObjectHeap_type;
    typedef Zen::Memory::managed_weak_ptr<Scripting::I_ObjectHeap>      wpObjectHeap_type;

    typedef Zen::Memory::managed_ptr<Scripting::I_ScriptModule>         pScriptModule_type;
    typedef Zen::Memory::managed_weak_ptr<Scripting::I_ScriptModule>    wpScriptModule_type;

    typedef Scripting::I_ObjectReference*                               pObjectReference_type;
    typedef std::map<PyObject*, pObjectReference_type>                  object_map_type;
    /// @}

    /// @name I_ScriptEngine implementation
    /// @{
public:
    virtual Scripting::I_ObjectHeap& heap();
    virtual bool executeScript(const std::string& _fileName);
    virtual void executeMethod(boost::any& _object, boost::any& _method, std::vector<boost::any>& _parms);
    virtual pScriptModule_type createScriptModule(const std::string& _moduleName, const std::string& _docString);
    /// @}

    /// @name PythonEngine implementation
    /// @{
public:
    PythonTypeMap& getTypeMap();
    pObjectReference_type getObject(PyObject* _pObject);
    void setObject(PyObject* _pPyObject, pObjectReference_type _pCPPObject);
    /// @}

    /// @name Event handlers
    /// @{
public:
    void onDestroyObjectHeap(wpObjectHeap_type _pObjectHeap);
    void onDestroyScriptModule(wpScriptModule_type _pScriptModule);
    /// @}

    /// @name 'Structors
    /// @{
public:
             PythonEngine();
    virtual ~PythonEngine();
    /// @}

    /// @name Member Variables
    /// @{
private:
    pObjectHeap_type    m_pHeap;
    PythonTypeMap       m_typeMap;

    object_map_type     m_objectMap;
    /// @}

};  // class PythonEngine

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace ZPython
}   // namespace Zen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // INDIEZEN_ZPYTHON_PYTHON_ENGINE_HPP_INCLUDED
