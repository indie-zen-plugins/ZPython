//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Python plugin for Zen Scripting
//
// Copyright (C) 2001 - 2016 Raymond A. Richards
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#include <Zen/Core/Plugins/Utilities.hpp>

#include "PythonEngineFactory.hpp"

// Don't normally do this.  Just here because it's convenient.
using namespace Zen::ZPython;

IMPLEMENT_SINGLE_ZEN_PLUGIN(ZPythonModule, ZPythonPlugin)

BEGIN_ZEN_EXTENSION_MAP(ZPythonPlugin)
    ZEN_EXTENSION("Zen::Scripting::Engine", &PythonEngineFactory::getSingleton())
END_ZEN_EXTENSION_MAP()
