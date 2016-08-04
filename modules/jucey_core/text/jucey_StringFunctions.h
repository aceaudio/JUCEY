
#ifndef JUCEY_STRINGFUNCTIONS_H_INCLUDED
#define JUCEY_STRINGFUNCTIONS_H_INCLUDED

class JUCE_API StringFunctions
{
public:
    /** Checks whether every character in a string is alphabetic or numeric. */
    static bool isLettersOrDigits (const juce::String& string) noexcept;
    
    /** Checks whether every character in a string is alphabetic. */
    static bool isLetters (const juce::String& string) noexcept;
    
    /** Checks whether every character in a string is numeric. */
    static bool isDigits (const juce::String& string) noexcept;
    
    /** Checks whether every character in a string is upper-case. */
    static bool isUpper (const juce::String& string) noexcept;
    
    /** Checks whether every character in a string is lower-case. */
    static bool isLower (const juce::String& string) noexcept;
    
    /** Checks whether any character in a string is whitespace. */
    static bool containsWhitespace (const juce::String& string) noexcept;
    
    /** Return a copy of the string with its first character capitalized and the 
        rest lowercased.
     */
    static juce::String capitalise (const juce::String& string) noexcept;
    
    /** Return a copy of the string with each word seperated by white space capitalized and the
     rest lowercased
     */
    static juce::String capitaliseWords (const juce::String& string) noexcept;
    
    /** Adds a pad character to both the front and back of the string . */
    static juce::String pad (const juce::String& string, juce::juce_wchar padCharacter, int minimumLength) noexcept;
    
    /** Checks whether every character in a string is upper-case. */
    static juce::String smartSubstring (const juce::String& string, int maximumLength) noexcept;
};

#endif // JUCEY_STRINGFUNCTIONS_H_INCLUDED