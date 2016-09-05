//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Python plugin for Zen Scripting
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
// Copyright (C)        2010 Jason Smith
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#include "PythonMethod.hpp"
#include "PythonType.hpp"
#include "PythonModule.hpp"
#include "PythonObject.hpp"
#include "PythonTypeMap.hpp"
#include "PythonEngine.hpp"

#include <Zen/Core/Scripting/I_ScriptObject.hpp>
#include <Zen/Core/Scripting/I_ObjectReference.hpp>

#include <iostream>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace ZPython {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
PythonMethod::PythonMethod(PythonType* _pType, const std::string& _name, const std::string& _docString, 
                           Scripting::I_ScriptType::void_function_no_args_type _function, PyCFunction _pCFunction)
:   m_pType(_pType)
,   m_name(_name)
,   m_docString(_docString)
,   m_pCFunction(_pCFunction)
,   m_functionType(VOID_FUNCTION_NO_ARGS)
,   m_function0(_function)
{
    init();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
PythonMethod::PythonMethod(PythonType* _pType, const std::string& _name, const std::string& _docString, 
                           Scripting::I_ScriptType::void_function_args_type _function, PyCFunction _pCFunction)
:   m_pType(_pType)
,   m_name(_name)
,   m_docString(_docString)
,   m_pCFunction(_pCFunction)
,   m_functionType(VOID_FUNCTION_ARGS)
,   m_function1(_function)
{
    init();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
PythonMethod::PythonMethod(PythonType* _pType, const std::string& _name, const std::string& _docString, 
                           Scripting::I_ScriptType::object_function_args_type _function, PyCFunction _pCFunction)
:   m_pType(_pType)
,   m_name(_name)
,   m_docString(_docString)
,   m_pCFunction(_pCFunction)
,   m_functionType(OBJ_FUNCTION_ARGS)
,   m_function2(_function)
{
    init();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
PythonMethod::PythonMethod(PythonType* _pType, const std::string& _name, const std::string& _docString, 
                           Scripting::I_ScriptType::object_function_no_args_type _function, PyCFunction _pCFunction)
:   m_pType(_pType)
,   m_name(_name)
,   m_docString(_docString)
,   m_pCFunction(_pCFunction)
,   m_functionType(OBJ_FUNCTION_NO_ARGS)
,   m_function3(_function)
{
    init();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
PythonMethod::PythonMethod(PythonType* _pType, const std::string& _name, const std::string& _docString, 
                           Scripting::I_ScriptType::string_function_args_type _function, PyCFunction _pCFunction)
:   m_pType(_pType)
,   m_name(_name)
,   m_docString(_docString)
,   m_pCFunction(_pCFunction)
,   m_functionType(STRING_FUNCTION_ARGS)
,   m_function4(_function)
{
    init();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
PythonMethod::PythonMethod(PythonType* _pType, const std::string& _name, const std::string& _docString, 
                           Scripting::I_ScriptType::string_function_no_args_type _function, PyCFunction _pCFunction)
:   m_pType(_pType)
,   m_name(_name)
,   m_docString(_docString)
,   m_pCFunction(_pCFunction)
,   m_functionType(STRING_FUNCTION_NO_ARGS)
,   m_function5(_function)
{
    init();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
PythonMethod::PythonMethod(PythonType* _pType, const std::string& _name, const std::string& _docString, 
                           Scripting::I_ScriptType::bool_function_no_args_type  _function, PyCFunction _pCFunction)
:   m_pType(_pType)
,   m_name(_name)
,   m_docString(_docString)
,   m_pCFunction(_pCFunction)
,   m_functionType(BOOL_FUNCTION_NO_ARGS)
,   m_function6(_function)
{
    init();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
PythonMethod::PythonMethod(PythonType* _pType, const std::string& _name, const std::string& _docString, 
                           Scripting::I_ScriptType::bool_function_args_type _function, PyCFunction _pCFunction)
:   m_pType(_pType)
,   m_name(_name)
,   m_docString(_docString)
,   m_pCFunction(_pCFunction)
,   m_functionType(BOOL_FUNCTION_ARGS)
,   m_function7(_function)
{
    init();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
PythonMethod::PythonMethod(PythonType* _pType, const std::string& _name, const std::string& _docString, 
                           Scripting::I_ScriptType::int_function_no_args_type _function, PyCFunction _pCFunction)
:   m_pType(_pType)
,   m_name(_name)
,   m_docString(_docString)
,   m_pCFunction(_pCFunction)
,   m_functionType(INT_FUNCTION_NO_ARGS)
,   m_function8(_function)
{
    init();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
PythonMethod::PythonMethod(PythonType* _pType, const std::string& _name, const std::string& _docString, 
                           Scripting::I_ScriptType::int_function_args_type _function, PyCFunction _pCFunction)
:   m_pType(_pType)
,   m_name(_name)
,   m_docString(_docString)
,   m_pCFunction(_pCFunction)
,   m_functionType(INT_FUNCTION_ARGS)
,   m_function9(_function)
{
    init();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
PythonMethod::PythonMethod(PythonType* _pType, const std::string& _name, const std::string& _docString,
                           Scripting::I_ScriptMethod* _function, PyCFunction _pCFunction)
:   m_pType(_pType)
,   m_name(_name)
,   m_docString(_docString)
,   m_pCFunction(_pCFunction)
,   m_functionType(GENERIC_FUNCTION_ARGS)
,   m_function10(_function)
{
    init();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
PythonMethod::~PythonMethod()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
PythonMethod::init()
{
    m_pDef = new PyMethodDef;
    memset(m_pDef, 0, sizeof(PyMethodDef));
    m_pDef->ml_name = m_name.c_str();
    m_pDef->ml_meth = m_pCFunction;

    //m_pFunction = PyCFunction_New(m_pDef, NULL);

    PyObject* pMethod = PyDescr_NewMethod(m_pType->getRawType(), m_pDef);

    PyDict_SetItemString(m_pType->getRawType()->tp_dict, m_pDef->ml_name, pMethod);
    Py_DECREF(pMethod);
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
PyMethodDef*
PythonMethod::getDef()
{
    return m_pDef;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
PyObject*
PythonMethod::operator ()(PyObject* _pObj, PyObject* _pArgs)
{
    pObjectReference_type const pObj = m_pType->getModule().getEngine().getObject(_pObj);

    if (pObj)
    {
        // TODO Throw a Python exception
        std::cout << "Error mapping Python object to Zen object" << std::endl;
    }
    else
    {
        switch(m_functionType)
        {
        case VOID_FUNCTION_NO_ARGS:
            m_function0(pObj);
            return Py_None;
        case OBJ_FUNCTION_NO_ARGS:
            {
                pObjectReference_type const pObjReference = m_function3(pObj);
                pScriptObject_type const pReturnObj = pObjReference->getScriptObject();
                return dynamic_cast<PythonObject*>(pReturnObj.get())->get();
            }
        case STRING_FUNCTION_NO_ARGS:
            {
                const std::string& returnValue = m_function5(pObj);
                return PyString_FromString(returnValue.c_str());
            }
        case BOOL_FUNCTION_NO_ARGS:
            {
                const bool returnValue = m_function6(pObj);
                return returnValue ? Py_True : Py_False;
            }
        case INT_FUNCTION_NO_ARGS:
            {
                const int returnValue = m_function8(pObj);
                return PyLong_FromLong(returnValue);
            }
        case VOID_FUNCTION_ARGS:
        case OBJ_FUNCTION_ARGS:
        case STRING_FUNCTION_ARGS:
        case BOOL_FUNCTION_ARGS:
        case INT_FUNCTION_ARGS:
        case GENERIC_FUNCTION_ARGS:
            {
                std::vector<boost::any> parms;

                PythonTypeMap& typeMap = m_pType->getModule().getEngine().getTypeMap();

                if (PyTuple_Check(_pArgs))
                {
                    Py_ssize_t size = PyTuple_Size(_pArgs);

                    for(int x = 0; x < size; x++)
                    {
                        PyObject* const pArg = PyTuple_GetItem(_pArgs, x);

                        if (typeMap.push_back(parms, pArg))
                        {
                            // It's converted
                        }
                        else
                        {
                            pObjectReference_type const pObjRef = m_pType->getModule().getEngine().getObject(pArg);

                            if (pObj)
                            {
                                parms.push_back(pObj);
                            }
                            else
                            {
                                // Error, type not supported
                                std::string unknown("Unknown Argument Type");
                                parms.push_back(unknown);
                            }
                        }

                        _typeobject* pType = pArg->ob_type;
                    }
                }
                else
                {
                    // TODO Don't copy / paste this logic from above
                    if (typeMap.push_back(parms, _pArgs))
                    {
                        // It's converted
                    }
                    else
                    {
                        pObjectReference_type const pObjRef = m_pType->getModule().getEngine().getObject(_pArgs);

                        if (pObjRef)
                        {
                            parms.push_back(pObjRef);
                        }
                        else
                        {
                            // Error, type not supported
                            std::string unknown("Unknown Argument Type");
                            parms.push_back(unknown);
                        }
                    }
                }

                if (m_functionType == VOID_FUNCTION_ARGS)
                {
                    m_function1(pObj, parms);
                    return Py_None;
                }
                else if (m_functionType == OBJ_FUNCTION_ARGS)
                {
                    pObjectReference_type const pObjReference = m_function2(pObj, parms);
                    pScriptObject_type const pReturnObj = pObjReference->getScriptObject();
                    return dynamic_cast<PythonObject*>(pReturnObj.get())->get();
                }
                else if (m_functionType == STRING_FUNCTION_ARGS)
                {
                    const std::string& returnValue = m_function4(pObj, parms);

                    return PyString_FromString(returnValue.c_str());
                }
                else if (m_functionType == BOOL_FUNCTION_ARGS)
                {
                    const bool returnValue = m_function7(pObj, parms);
                    return returnValue ? Py_True : Py_False;
                }
                else if (m_functionType == INT_FUNCTION_ARGS)
                {
                    const int returnValue = m_function9(pObj, parms);
                    return PyLong_FromLong(returnValue);
                }
                else if (m_functionType == GENERIC_FUNCTION_ARGS)
                {
                    boost::any anyReturn = m_function10->dispatch(pObj, parms);

                    // TODO this is inefficient... do a map of functors instead.
                    if(anyReturn.type() == typeid(void))
                    {
                        // no return, don't bother doing anything
                        return Py_None;
                    }
                    else if(anyReturn.type() == typeid(Zen::Scripting::I_ObjectReference*))
                    {
                        // object
                        pObjectReference_type pObjReference = boost::any_cast<pObjectReference_type>(anyReturn);
                        pScriptObject_type const pReturnObj = pObjReference->getScriptObject();

                        return dynamic_cast<PythonObject*>(pReturnObj.get())->get();
                    }
                    else if(anyReturn.type() == typeid(std::string))
                    {
                        std::string returnValue = boost::any_cast<std::string>(anyReturn);

                        return PyString_FromString(returnValue.c_str());
                    }
                    else if(anyReturn.type() == typeid(bool))
                    {
                        bool returnValue = boost::any_cast<bool>(anyReturn);

                        return returnValue ? Py_True : Py_False;
                    }
                    else if(anyReturn.type() == typeid(int))
                    {
                        int returnValue = boost::any_cast<int>(anyReturn);

                        return PyLong_FromLong(returnValue);
                    }
                    else if(anyReturn.type() == typeid(Zen::Math::Real))
                    {
                        Zen::Math::Real returnValue = boost::any_cast<Zen::Math::Real>(anyReturn);
                        // TR - I don't like this because it means
                        // we cannot support Real as a return type.
                        // We'll fix it later.
                        return PyLong_FromLong((long)returnValue);
                    }else
                    {
                        // TODO Make this error message a little more detailed
                        throw Zen::Utility::runtime_exception("Script method returned unknown type.");
                    }

                    // TODO Throw an exception since the type wasn't valid
                    return 0;
                }
            } // case All functions that take args
            break;
        } // switch(m_functionType)
    }

    // TODO Throw an exception because we should never get here.
    return Py_None;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace ZPython
}   // namespace IndieZen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
