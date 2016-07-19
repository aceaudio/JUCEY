
template <>
juce::String Argument<juce::String>::fromString (const juce::String& string)
{
    return string;
}

template <>
bool Argument<bool>::fromString (const juce::String& string)
{
    return string.getIntValue() != 0
    || string.trim().equalsIgnoreCase ("true")
    || string.trim().equalsIgnoreCase ("yes");
}

template <>
int Argument<int>::fromString (const juce::String& string)
{
    return string.getIntValue();
}

template <>
juce::int64 Argument<juce::int64>::fromString (const juce::String& string)
{
    return string.getLargeIntValue();
}

template <>
float Argument<float>::fromString (const juce::String& string)
{
    return string.getFloatValue();
}

template <>
double Argument<double>::fromString (const juce::String& string)
{
    return string.getDoubleValue();
}

template <>
juce::File Argument<juce::File>::fromString (const juce::String& string)
{
    return juce::File (string);
}
