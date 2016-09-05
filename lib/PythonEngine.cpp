//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Python plugin for Zen Scripting
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#include <Python.h>

#include "PythonEngine.hpp"
#include "PythonModule.hpp"

#include <Zen/Core/Scripting/I_ScriptModule.hpp>
#include <Zen/Core/Scripting/I_ObjectReference.hpp>

#include <Zen/Core/Utility/runtime_exception.hpp>

#include <boost/bind.hpp>
#include <boost/function.hpp>

#include <stdio.h>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace ZPython {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
PythonEngine::PythonEngine()
{
    m_pHeap = 
        pObjectHeap_type(new PythonHeap(this),
        boost::bind(&PythonEngine::onDestroyObjectHeap,this,_1));

    // http://docs.python.org/api/embedding.html
    Py_Initialize();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
PythonEngine::~PythonEngine()
{
    Py_Finalize();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
Scripting::I_ObjectHeap&
PythonEngine::heap()
{
    return *m_pHeap;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
bool
PythonEngine::executeScript(const std::string& _fileName)
{
    // TODO This should really use a resource manager, but for now just do it this way
    
    FILE* pFile = fopen(_fileName.c_str(), "r+b");

    if (pFile)
    {
        PyRun_AnyFile(pFile, _fileName.c_str());
        fclose(pFile);
        return true;
    }

    return false;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
PythonEngine::executeMethod(boost::any& _object, boost::any& _method, std::vector<boost::any>& _parms)
{
    throw Utility::runtime_exception("PythonEngine::executeMethod(): Error, not implemented.");
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
PythonEngine::pScriptModule_type
PythonEngine::createScriptModule(const std::string& _moduleName, const std::string& _docString)
{
    return pScriptModule_type(new PythonModule(this, _moduleName, _docString),
        boost::bind(&PythonEngine::onDestroyScriptModule,this,_1));
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
PythonTypeMap&
PythonEngine::getTypeMap()
{
    return m_typeMap;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
PythonEngine::pObjectReference_type
PythonEngine::getObject(PyObject* _pObject)
{
    return m_objectMap[_pObject];
}


//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
PythonEngine::setObject(PyObject* _pPyObject, pObjectReference_type _pCPPObject)
{
    // Isn't there a better way to do this?  Is there a way to use the PyObject to store the
    // raw C++ pointer?  For now, we just use this map.
    m_objectMap[_pPyObject] = _pCPPObject;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
PythonEngine::onDestroyObjectHeap(wpObjectHeap_type _pObjectHeap)
{
    /// Fire the ObjectHeap's onDestroyEvent
    _pObjectHeap->onDestroyEvent(_pObjectHeap);

    /// Delete the ObjectHeap
    PythonHeap* pObjectHeap = dynamic_cast<PythonHeap*>(_pObjectHeap.get());

    if( pObjectHeap )
    {
        delete pObjectHeap;
    }
    else
    {
        throw std::exception("Zen::ZPython::PythonEngine::onDestroyObjectHeap() : _pObjectHeap is an invalid PythonHeap.");
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
PythonEngine::onDestroyScriptModule(wpScriptModule_type _pScriptModule)
{
    /// Fire the ScriptModule's onDestroyEvent
    _pScriptModule->onDestroyEvent(_pScriptModule);

    /// Delete the ScriptModule
    PythonModule* pScriptModule = dynamic_cast<PythonModule*>(_pScriptModule.get());

    if( pScriptModule )
    {
        delete pScriptModule;
    }
    else
    {
        throw std::exception("Zen::ZPython::PythonEngine::onDestroyScriptModule() : _pScriptModule is an invalid PythonModule.");
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace ZPython
}   // namespace IndieZen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
