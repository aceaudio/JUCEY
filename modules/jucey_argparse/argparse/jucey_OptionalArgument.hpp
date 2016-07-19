
#ifndef JUCE_OPTIONALARGUMENT_HPP_INCLUDED
#define JUCE_OPTIONALARGUMENT_HPP_INCLUDED

template <typename Type>
OptionalArgument<Type>::OptionalArgument (const juce::String& name)
    : OptionalArgument<Type> (juce::StringArray (name))
{
    
}

template <typename Type>
OptionalArgument<Type>::OptionalArgument (const juce::String& longName,
                                          const juce::String& shortName)
    : OptionalArgument<Type> (juce::StringArray (longName))
{
    ArgumentBase::addName (shortName);
}

template <typename Type>
OptionalArgument<Type>::OptionalArgument (const juce::StringArray& names)
    : Argument<Type> (names)
{
    
}

template <typename Type>
bool OptionalArgument<Type>::isOptional() const
{
    return false;
}

template <typename Type>
bool OptionalArgument<Type>::isPositional() const
{
    return true;
}

template <typename Type>
juce::StringArray OptionalArgument<Type>::parseKnownArgs (const ArgumentParser& parser, const juce::StringArray& args)
{
    juce::StringArray unknownArgs;
    bool shouldConsume = false;
    
    for (auto arg : args)
    {
        if (ArgumentBase::getNames().contains (arg))
        {
            shouldConsume = true;
            
            if (ArgumentBase::getNumberOfArguments() >= 0)
                Argument<Type>::clearConsumedValues();
        }
        else if (parser.isValidOptionalString (arg))
        {
            if (shouldConsume)
            {
                Argument<Type>::finishConsuming();
                shouldConsume = false;
            }
            
            unknownArgs.add (arg);
        }
        else if (shouldConsume)
        {
            shouldConsume = Argument<Type>::consume (arg);
        }
        else
        {
            unknownArgs.add (arg);
        }
    }
    
    Argument<Type>::finishConsuming();
    return unknownArgs;
}

#endif  // JUCE_OPTIONALARGUMENT_HPP_INCLUDED
