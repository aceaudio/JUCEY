
#ifndef JUCE_OPTIONALARGUMENT_H_INCLUDED
#define JUCE_OPTIONALARGUMENT_H_INCLUDED

/**
    Defines the behaviour for parsing an optional argument, that is an argument 
    that is precieded by an identifier that starts with a specified prefix 
    character.
 
    An optional argument might loop like this on the command line

    myprog "positional argument" --option "optional arugment"
 
    @see ArgumentParser, ArgumentBase, Argument, PositionalArgument
 */
template <typename Type>
class OptionalArgument : public Argument<Type>
{
public:
    OptionalArgument (const juce::String& name);
    OptionalArgument (const juce::String& longName, const juce::String& shortName);
    OptionalArgument (const juce::StringArray& names);
    
    bool isOptional() const final;
    bool isPositional() const final;
    juce::StringArray parseKnownArgs (const ArgumentParser& parser, const juce::StringArray& args) final;
    
private:    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OptionalArgument)
};

#endif  // JUCE_OPTIONALARGUMENT_H_INCLUDED
