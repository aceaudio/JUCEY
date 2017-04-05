
#pragma once

class ArgumentParser;

/**
    Deals with the base logic and data common to all argument types.
 
    @see Argument, OptionalArgument, PositionalArgument, ArgumentParser
 */
class ArgumentBase
{
public:
    enum NArgsSpecial
    {
        kDefault = -1,          // ?
        kAll = -2,              // *
        kAllWithAtLeastOne = -3 // +
    };
    
    virtual ~ArgumentBase() {}
    
    juce::StringArray getNames() const;
    
    void setNumberOfArguments (int numberOfArguments);
    int getNumberOfArguments() const;
    
    void setRequired (bool isRequired);
    bool isRequired() const;
    
    int count() const;
    virtual bool isPositional() const = 0;
    virtual bool isOptional() const = 0;
    
    virtual juce::StringArray parseKnownArgs (const ArgumentParser& parser, const juce::StringArray& args) = 0;
    
protected:
    ArgumentBase (const juce::StringArray& names);
    void addName (const juce::String& name);

private:
    juce::StringArray mNames;
    int mNumberOfArguments;
    bool mIsRequired;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArgumentBase)
};
