
#ifndef JUCE_POSITIONALARGUMENT_HPP_INCLUDED
#define JUCE_POSITIONALARGUMENT_HPP_INCLUDED

template <typename Type>
PositionalArgument<Type>::PositionalArgument (const juce::String& name)
    : Argument<Type> (name)
{

}

template <typename Type>
bool PositionalArgument<Type>::isOptional() const
{
    return false;
}

template <typename Type>
bool PositionalArgument<Type>::isPositional() const
{
    return true;
}

template <typename Type>
juce::StringArray PositionalArgument<Type>::parseKnownArgs (const ArgumentParser& parser, const juce::StringArray& args)
{
    juce::StringArray unknownArgs;
    bool shouldConsume = true;
    
    for (auto arg : args)
    {
        if (shouldConsume && ! parser.isValidOptionalString (arg))
            shouldConsume = Argument<Type>::consume (arg);
        else
            unknownArgs.add (arg);
    }
    
    Argument<Type>::finishConsuming();
    return unknownArgs;
}

#endif  // JUCE_POSITIONALARGUMENT_HPP_INCLUDED