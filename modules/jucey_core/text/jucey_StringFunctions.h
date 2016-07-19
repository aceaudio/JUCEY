
#ifndef JUCEY_STRINGFUNCTIONS_H_INCLUDED
#define JUCEY_STRINGFUNCTIONS_H_INCLUDED

class JUCE_API StringFunctions
{
public:
    static bool isLettersOrDigits (const juce::String& string) noexcept;
    static bool isLetters (const juce::String& string) noexcept;
    static bool isDigits (const juce::String& string) noexcept;
    static bool isUpper (const juce::String& string) noexcept;
    static bool isLower (const juce::String& string) noexcept;
    static bool containsWhitespace (const juce::String& string) noexcept;
    static juce::String capitalise (const juce::String& string) noexcept;
    static juce::String capitaliseWords (const juce::String& string) noexcept;
    static juce::String pad (const juce::String& string, juce::juce_wchar padCharacter, int minimumLength) noexcept;
    static juce::String smartSubstring (const juce::String& string, int maximumLength) noexcept;
};

#endif // JUCEY_STRINGFUNCTIONS_H_INCLUDED