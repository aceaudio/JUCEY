
#ifndef JUCE_ARGUMENTPARSER_H_INCLUDED
#define JUCE_ARGUMENTPARSER_H_INCLUDED

/**
    Deals with parsing command line arguments to corrsponding optional and
    positional arguments.
 
    @see ArgumentBase, Argument, OptionalArgument, PositionalArgument
 */
class ArgumentParser
{
public:
    ArgumentParser (const juce::String& description = "");
    
    void addArgument (ArgumentBase& argument);
    void parseArgs (const juce::StringArray& args);
    juce::StringArray parseKnownArgs (const juce::StringArray& args);
    void setPrefixChars (const juce::String& chars);
    juce::String getPrefixChars() const;
    bool isValidOptionalString (const juce::String& string) const;
    
private:
    juce::String mDescription;
    juce::String mPrefixChars;
    juce::Array<ArgumentBase*> mOptionalArguments;
    juce::Array<ArgumentBase*> mPositionalArguments;
};

#endif  // JUCE_ARGUMENTPARSER_H_INCLUDED
