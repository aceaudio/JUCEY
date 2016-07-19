 
#ifndef JUCE_ARGUMENT_H_INCLUDED
#define JUCE_ARGUMENT_H_INCLUDED

/**
    Template base class for defining how to convert a command line argument into 
    a specified type.
     
    @see ArgumentBase, OptionalArgument, PositionalArgument, ArgumentParser
 */
template <typename Type>
class Argument : public ArgumentBase
{
public:
    Argument (const juce::StringArray& names);
    Type getValue() const;
    void setDefaultValue (const Type& defaultValue);
    void setConstValue (const Type& constValue);
    
protected:
    bool consume (const juce::String& string);
    void finishConsuming() const;
    void clearConsumedValues();
    
private:
    Type fromString (const juce::String& string);
    
    juce::Array<Type> mValues;
    Type mDefaultValue;
    int mNumberOfConsumedValues;
};

#endif  // JUCE_ARGUMENT_H_INCLUDED
