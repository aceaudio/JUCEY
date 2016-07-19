
#ifdef JUCEY_UNIT_TESTS

class JuceyUnitTest : public juce::UnitTest
{
public:
    JuceyUnitTest()  : juce::UnitTest ("Jucey Unit Test") {}
    
    void runTest() override
    {
        //======================================================================
        beginTest ("expectMessageLogged");

        expectMessageLogged (juce::Logger::writeToLog ("abc123"), "abc123");
        expectMessageLogged (juce::Logger::writeToLog ("abc123"), "abc123", "failure message");
        
        //======================================================================
        beginTest ("expectMessageNotLogged");
        
        expectMessageNotLogged (juce::Logger::writeToLog ("123abc"), "abc123");
        expectMessageNotLogged (juce::Logger::writeToLog ("123abc"), "abc123", "failure message");
        
        //======================================================================
        beginTest ("expectMessageLoggedStartingWith");

        expectMessageLoggedStartingWith (juce::Logger::writeToLog ("abc123"), "abc");
        expectMessageLoggedStartingWith (juce::Logger::writeToLog ("abc123"), "abc", "failure message");
        
        //======================================================================
        beginTest ("expectMessageNotLoggedStartingWith");
        
        expectMessageNotLoggedStartingWith (juce::Logger::writeToLog ("abc"), "123");
        expectMessageNotLoggedStartingWith (juce::Logger::writeToLog ("abc"), "123", "failure message");
        
        //======================================================================
        beginTest ("expectJassert");
        
        expectJassert (jassertfalse);
        
        //======================================================================
        beginTest ("expectJassertIn: jucey_UnitTest.cpp");
        
        expectJassertIn (jassertfalse, "jucey_UnitTest.cpp");
        
        //======================================================================
        beginTest ("expectDoesNotJassert");
        
        expectDoesNotJassert (jassert (true));
        
        //======================================================================
        beginTest ("expectDoesNotJassertIn: jucey_UnitTest.cpp");
        
        expectDoesNotJassertIn (jassert (true), "jucey_UnitTest.cpp");
        
        //======================================================================
        beginTest ("expectDoesNotJassertIn: jucey_Other.cpp");
        
        expectDoesNotJassertIn (jassertfalse, "jucey_Other.cpp");
    }
};

static JuceyUnitTest staticJuceyUnitTest;

#endif // JUCEY_UNIT_TESTS
