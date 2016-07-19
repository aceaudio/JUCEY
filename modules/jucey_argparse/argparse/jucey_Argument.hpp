
#ifndef JUCE_ARGUMENT_HPP_INCLUDED
#define JUCE_ARGUMENT_HPP_INCLUDED

template <typename Type>
Argument<Type>::Argument (const juce::StringArray& names)
    : ArgumentBase (names)
    , mDefaultValue (Type())
    , mNumberOfConsumedValues (0)
{
    
}

template <typename Type>
Type Argument<Type>::getValue() const
{
    if (mValues.size())
        return mValues[0];
    
    return mDefaultValue;
}

template <typename Type>
void Argument<Type>::setDefaultValue (const Type& defaultValue)
{
    mDefaultValue = defaultValue;
}

template <typename Type>
bool Argument<Type>::consume (const juce::String& string)
{
    int numberOfArguments = getNumberOfArguments();
    
    if (numberOfArguments == NArgsSpecial::kDefault)
    {
        if (mValues.size() == 0)
            mValues.add (fromString (string));
        else
            mValues.setUnchecked (0, fromString (string));
        
        return false;
    }
    
    if (mNumberOfConsumedValues < numberOfArguments
        || numberOfArguments == NArgsSpecial::kAll
        || numberOfArguments == NArgsSpecial::kAllWithAtLeastOne)
    {
        mValues.add (fromString (string));
        ++mNumberOfConsumedValues;
        
        return true;
    }
    
    // TODO: error too many arguments
    return false;
}

template <typename Type>
void Argument<Type>::finishConsuming() const
{
    if (isRequired() && ! mNumberOfConsumedValues)
    {
        // TODO: error required argument not passed
    }
    
    int numberOfArguments = getNumberOfArguments();
    
    if ((juce::isPositiveAndBelow (numberOfArguments, mNumberOfConsumedValues))
        || (numberOfArguments == NArgsSpecial::kAllWithAtLeastOne && mValues.size() == 0))
    {
        // TODO: error too few arguments
    }
}

template <typename Type>
void Argument<Type>::clearConsumedValues()
{
    mNumberOfConsumedValues = 0;
    mValues.clear();
}

#endif  // JUCE_ARGUMENT_HPP_INCLUDED