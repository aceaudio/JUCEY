
bool StringFunctions::isLettersOrDigits (const juce::String& string) noexcept
{
    if ( ! string.length())
        return false;
    
    for (juce::String::CharPointerType character (string.getCharPointer()); ! character.isEmpty();)
        if ( ! juce::CharacterFunctions::isLetterOrDigit (character.getAndAdvance()))
            return false;
    
    return true;
}

bool StringFunctions::isLetters (const juce::String& string) noexcept
{
    if ( ! string.length())
        return false;
    
    for (juce::String::CharPointerType character (string.getCharPointer()); ! character.isEmpty();)
        if ( ! juce::CharacterFunctions::isLetter (character.getAndAdvance()))
            return false;
    
    return true;
}

bool StringFunctions::isDigits (const juce::String& string) noexcept
{
    if ( ! string.length())
        return false;
    
    for (juce::String::CharPointerType character (string.getCharPointer()); ! character.isEmpty();)
        if ( ! juce::CharacterFunctions::isDigit (character.getAndAdvance()))
            return false;
    
    return true;
}

bool StringFunctions::isUpper (const juce::String& string) noexcept
{
    if ( ! string.length())
        return false;
    
    for (juce::String::CharPointerType character (string.getCharPointer()); ! character.isEmpty();)
        if ( ! juce::CharacterFunctions::isUpperCase (character.getAndAdvance()))
            return false;
    
    return true;
}

bool StringFunctions::isLower (const juce::String& string) noexcept
{
    if ( ! string.length())
        return false;
    
    for (juce::String::CharPointerType character (string.getCharPointer()); ! character.isEmpty();)
        if ( ! juce::CharacterFunctions::isLowerCase (character.getAndAdvance()))
            return false;
    
    return true;
}

bool StringFunctions::containsWhitespace (const juce::String& string) noexcept
{
    for (juce::String::CharPointerType character (string.getCharPointer()); ! character.isEmpty();)
        if (juce::CharacterFunctions::isWhitespace (character.getAndAdvance()))
            return true;
    
    return false;
}

juce::String StringFunctions::capitalise (const juce::String& string) noexcept
{
    int length = string.length();
    
    if ( ! length)
        return juce::String::empty;
        
    if (length == 1)
        return string.toUpperCase();
        
    return string.substring (0, 1).toUpperCase() + string.substring (1, length);
}

juce::String StringFunctions::capitaliseWords (const juce::String& string) noexcept
{
    juce::StringArray words = juce::StringArray::fromTokens (string, " ", "");
    
    for (int i = 0; i < words.size(); ++i)
        words.set (i, capitalise (words.getReference (i)));
        
    return words.joinIntoString (" ");
}

juce::String StringFunctions::pad (const juce::String& string, juce::juce_wchar padCharacter, int minimumLength) noexcept
{
    jassert (minimumLength > 0);
    
    int numberOfPaddedCharacters = minimumLength - string.length();
    
    if (numberOfPaddedCharacters < 1)
        return  string;
    
    int numberOfPaddedCharactersLeft = numberOfPaddedCharacters / 2;
    int numberOfPaddedCharactersRight = numberOfPaddedCharacters - numberOfPaddedCharactersLeft;
    
    juce::String padString = juce::String::charToString (padCharacter);
    juce::String padStringLeft = juce::String::repeatedString (padString, numberOfPaddedCharactersLeft);
    juce::String padStringRight = juce::String::repeatedString (padString, numberOfPaddedCharactersRight);
    
    return padStringLeft + string + padStringRight;
}

juce::String StringFunctions::smartSubstring (const juce::String& string, int maximumLength) noexcept
{
    int numberOfCharactersToRemove = string.length() - maximumLength;
    
    if (numberOfCharactersToRemove < 1)
        return string;
    
    // remove whitespace from the start and the end
    juce::String newString = string.trim();
    
    if ((numberOfCharactersToRemove = newString.length() - maximumLength) < 1)
        return newString;
    
    // replace multiple whitespace characters with a single whitespace character
    juce::StringArray words = juce::StringArray::fromTokens (newString.replaceCharacters ("\t\r\n", "   "), " ", "");
    words.removeEmptyStrings (true);
    newString = words.joinIntoString (" ");
    
    if ((numberOfCharactersToRemove = newString.length() - maximumLength) < 1)
        return newString;
    
    // remove special characters
    newString = newString.retainCharacters ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ");
    
    if ((numberOfCharactersToRemove = newString.length() - maximumLength) < 1)
        return newString;
    
    // remove whitespace and capitilise words
    newString = capitaliseWords (newString);
    newString = newString.removeCharacters (" ");
    
    if ((numberOfCharactersToRemove = newString.length() - maximumLength) < 1)
        return newString;
    
    for (int i = 0; i < numberOfCharactersToRemove; ++i)
    {
        // remove non capital vowels
        if (newString.containsAnyOf ("aeiou"))
        {
            int index = newString.lastIndexOfAnyOf ("aeiou");
            newString = newString.substring (0, index) + newString.substring (index + 1);
        }
        // remove non capital consonants
        else if (newString.containsAnyOf ("bcdfghjklmnpqrstvwxyz"))
        {
            int index = newString.lastIndexOfAnyOf ("bcdfghjklmnpqrstvwxyz");
            newString = newString.substring (0, index) + newString.substring (index + 1);
        }
        // remove charaters from the end of the string
        else
        {
            newString = newString.dropLastCharacters (1);
        }
    }
    
    return newString;
}

#ifdef JUCEY_UNIT_TESTS

class StringFunctionUnitTests : public juce::UnitTest
{
public:
    StringFunctionUnitTests() : juce::UnitTest ("StringFunctions") {}
    
    void runTest() override
    {
        beginTest ("isLettersOrDigits");
        expect (StringFunctions::isLettersOrDigits ("a"));
        expect (StringFunctions::isLettersOrDigits ("A"));
        expect (StringFunctions::isLettersOrDigits ("1"));
        expect (StringFunctions::isLettersOrDigits ("a1"));
        expect (StringFunctions::isLettersOrDigits ("A1"));
        expect ( ! StringFunctions::isLettersOrDigits (":a1"));
        expect ( ! StringFunctions::isLettersOrDigits (":A1"));
        
        beginTest ("isLetters");
        expect (StringFunctions::isLetters ("a"));
        expect (StringFunctions::isLetters ("A"));
        expect ( ! StringFunctions::isLetters ("1"));
        expect ( ! StringFunctions::isLetters ("a1"));
        expect ( ! StringFunctions::isLetters ("A1"));
        expect ( ! StringFunctions::isLetters (":a1"));
        expect ( ! StringFunctions::isLetters (":A1"));
        
        beginTest ("isDigits");
        expect ( ! StringFunctions::isDigits ("a"));
        expect ( ! StringFunctions::isDigits ("A"));
        expect (StringFunctions::isDigits ("1"));
        expect ( ! StringFunctions::isDigits ("a1"));
        expect ( ! StringFunctions::isDigits ("A1"));
        expect ( ! StringFunctions::isDigits (":a1"));
        expect ( ! StringFunctions::isDigits (":A1"));
        
        beginTest ("isUpper");
        expect ( ! StringFunctions::isUpper ("a"));
        expect (StringFunctions::isUpper ("A"));
        expect ( ! StringFunctions::isUpper ("1"));
        expect ( ! StringFunctions::isUpper ("a1"));
        expect ( ! StringFunctions::isUpper ("A1"));
        expect ( ! StringFunctions::isUpper (":a1"));
        expect ( ! StringFunctions::isUpper (":A1"));
        
        beginTest ("isLower");
        expect (StringFunctions::isLower ("a"));
        expect ( ! StringFunctions::isLower ("A"));
        expect ( ! StringFunctions::isLower ("1"));
        expect ( ! StringFunctions::isLower ("a1"));
        expect ( ! StringFunctions::isLower ("A1"));
        expect ( ! StringFunctions::isLower (":a1"));
        expect ( ! StringFunctions::isLower (":A1"));
        
        beginTest ("containsWhitespace");
        expect ( ! StringFunctions::containsWhitespace (""));
        expect ( ! StringFunctions::containsWhitespace ("a"));
        expect (StringFunctions::containsWhitespace (" "));
        expect (StringFunctions::containsWhitespace ("\n"));
        expect (StringFunctions::containsWhitespace ("\t"));
        expect (StringFunctions::containsWhitespace ("\r"));
        
        beginTest ("capitalise");
        expect (StringFunctions::capitalise ("test") == "Test");
        expect (StringFunctions::capitalise (" test") == " test");
        expect (StringFunctions::capitalise ("test this") == "Test this");
        expect (StringFunctions::capitalise ("") == "");
        expect (StringFunctions::capitalise ("TEST") == "TEST");
        
        beginTest ("pad");
        expect (StringFunctions::pad ("test", '*', 10) == "***test***");
        expect (StringFunctions::pad ("test", '*', 9) == "**test***");
        expect (StringFunctions::pad ("test", '*', 4) == "test");
        expect (StringFunctions::pad ("test", '*', 3) == "test");
    }
};

static StringFunctionUnitTests stringFunctionUnitTests;

#endif // JUCEY_UNIT_TESTS
