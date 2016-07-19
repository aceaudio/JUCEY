
#ifndef JUCE_POSITIONALARGUMENT_H_INCLUDED
#define JUCE_POSITIONALARGUMENT_H_INCLUDED

/**
    Defines the behaviour for parsing a posistional argument, that is an 
    argument that is defined by it's position in the command line.

    A positional argument might loop like this on the command line

    myprog "positional argument" --option "optional arugment"

    @see ArgumentParser, ArgumentBase, Argument, OptionalArgument
 */
template <typename Type>
class PositionalArgument : public Argument<Type>
{
public:
    PositionalArgument (const juce::String& name);
    
    bool isOptional() const final;
    bool isPositional() const final;
    juce::StringArray parseKnownArgs (const ArgumentParser& parser, const juce::StringArray& args) final;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PositionalArgument)
};

#endif  // JUCE_POSITIONALARGUMENT_H_INCLUDED
