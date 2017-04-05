
/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.txt file.
 
 
 BEGIN_JUCE_MODULE_DECLARATION
 
 ID:               jucey_argparse
 vendor:           jucey
 version:          0.0.1
 name:             JUCEY Command-line options and arguments parser
 description:      Command-line options and arguments parser
 website:          https://github.com/aceaudio/JUCEY
 license:          GPL/Commercial
 
 dependencies:
 
 END_JUCE_MODULE_DECLARATION
 
 *******************************************************************************/

#pragma once

#include "juce_core.h"

namespace jucey
{
#include "argparse/jucey_ArgumentBase.h"
#include "argparse/jucey_Argument.h"
#include "argparse/jucey_OptionalArgument.h"
#include "argparse/jucey_PositionalArgument.h"
#include "argparse/jucey_ArgumentParser.h"

#include "argparse/jucey_Argument.hpp"
#include "argparse/jucey_OptionalArgument.hpp"
#include "argparse/jucey_PositionalArgument.hpp"
}
