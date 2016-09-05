//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Python plugin for Zen Scripting
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
// Copyright (C)        2008 Matthew Alan Gray
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef INDIEZEN_ZPYTHON_PYTHON_ENGINE_FACTORY_HPP_INCLUDED
#define INDIEZEN_ZPYTHON_PYTHON_ENGINE_FACTORY_HPP_INCLUDED

#include <Zen/Core/Scripting/I_ScriptEngineFactory.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace Zen {
namespace ZPython {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class PythonEngineFactory
:   public Scripting::I_ScriptEngineFactory
{
    /// @name Types
    /// @{
public:
    /// @}

    /// @name I_ScriptEngineFactory implementation
    /// @{
public:
    virtual pScriptEngine_type create(const std::string& _name);
    /// @}

    /// @name PythonEngineFactory implementation
    /// @{
public:
    void onDestroy(wpScriptEngine_type _pScriptEngine);
    /// @}

    /// @name Static methods
    /// @{
public:
    static PythonEngineFactory& getSingleton();
    /// @}

    /// @name 'Structors
    /// @{
public:
             PythonEngineFactory();
    virtual ~PythonEngineFactory();
    /// @}

    /// @name Member variables
    /// @{
private:
    /// @}

};  // class PythonEngineFactory

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace ZPython
}   // namespace IndieZen
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // INDIEZEN_ZPYTHON_PYTHON_ENGINE_FACTORY_HPP_INCLUDED
