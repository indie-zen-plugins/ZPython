//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Python plugin for Zen Scripting
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#include "../PythonType.hpp"
#include "../PythonMethod.hpp"

#include <boost/preprocessor/iteration/local.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace ZPython {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#define METHOD_MAX_SIZE 100

// Create the hundred C methods

#define METHOD_LOOP(n) \
static PythonMethod* sm_pMethod##n; \
static PyObject* cfunc##n(PyObject* _pObj, PyObject* _pArgs) \
{ \
    return (*sm_pMethod##n)(_pObj, _pArgs); \
}

#define BOOST_PP_LOCAL_MACRO(n)     METHOD_LOOP(n)
#define BOOST_PP_LOCAL_LIMITS       (0, METHOD_MAX_SIZE - 1)
#include BOOST_PP_LOCAL_ITERATE()

// Create the hundred entries in the method table

#define METHOD_TABLE_LOOP(n) cfunc##n, &sm_pMethod##n,

#define BOOST_PP_LOCAL_MACRO(n)     METHOD_TABLE_LOOP(n)
#define BOOST_PP_LOCAL_LIMITS       (0, METHOD_MAX_SIZE - 1)

static unsigned int sm_methodItem = 0;
struct
{
    PyCFunction     m_cFunction;
    PythonMethod**  m_ppMethod;
} static sm_methodTable[METHOD_MAX_SIZE] =
{
#include BOOST_PP_LOCAL_ITERATE()
};

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
PythonType::addMethod(const std::string& _name, const std::string& _docString, Scripting::I_ScriptType::int_function_args_type _function)
{
    unsigned item = sm_methodItem++;

    (*sm_methodTable[item].m_ppMethod) = new PythonMethod(this, _name, _docString, _function, sm_methodTable[item].m_cFunction);

    m_methods.push_back(*sm_methodTable[item].m_ppMethod);
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace ZPython
}   // namespace IndieZen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
