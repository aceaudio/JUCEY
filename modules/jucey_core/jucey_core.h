
/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.txt file.
 
 
 BEGIN_JUCE_MODULE_DECLARATION
 
 ID:               jucey_core
 vendor:           jucey
 version:          0.0.1
 name:             JUCEY core classes
 description:      3rd party JUCE module to extend the funcionality of the juce_core module.
 website:          https://github.com/aceaudio/JUCEY
 license:          GPL/Commercial
 
 dependencies:     juce_core
 
 END_JUCE_MODULE_DECLARATION
 
 *******************************************************************************/

#pragma once

#include <juce_core/juce_core.h>

namespace jucey
{
#include "text/jucey_StringFunctions.h"
#include "logging/jucey_JassertListener.h"
}
