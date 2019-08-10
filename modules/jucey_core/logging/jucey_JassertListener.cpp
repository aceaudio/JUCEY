#if JUCE_LOG_ASSERTIONS || JUCE_DEBUG

JassertListener::JassertListener() noexcept
    : logger (juce::Logger::getCurrentLogger())
{
    setCurrentLogger (this);
}
    
JassertListener::~JassertListener()
{
    const bool isCurrentLoggerOnExit = juce::Logger::getCurrentLogger() == this;
    
    juce::Logger::setCurrentLogger (logger);
    
    // push all the captured messages back into the original logger.
    for (const auto& message : messages)
        juce::Logger::writeToLog (message);
    
    // if you've hit this then Logger::setCurrentLogger() has been called some
    // time between this object being constructed and destroyed. This might mean
    // messages and importantly jasserts were missed.
    jassert (isCurrentLoggerOnExit);
}
    
void JassertListener::logMessage (const juce::String& message)
{
    static juce::CriticalSection mutex;
    juce::ScopedLock lock (mutex);
    
    messages.add (message);
    
    const juce::String jassertDetails = message.fromLastOccurrenceOf ("JUCE Assertion failure in ", false, false);
    
    if (message != jassertDetails)
    {
        Jassertion jassertion;
        jassertion.threadId = juce::Thread::getCurrentThreadId();
        jassertion.filename = jassertDetails.upToFirstOccurrenceOf (":", false, false);
        jassertion.lineNumber = jassertDetails.fromLastOccurrenceOf (":", false, false).getIntValue();
        
        jassertions.add (jassertion);
    }
}
    
int JassertListener::getNumJasserts (bool currentThreadOnly,
                                     const juce::String& inFilename,
                                     int onLineNumber) const
{
    int numJasserts = 0;
    
    for (const auto& jassertion : jassertions)
    {
        if (currentThreadOnly && jassertion.threadId != juce::Thread::getCurrentThreadId())
            continue;
        
        // The File constructor will only take an absolute path, calling
        // `getChildFile` allows us to pass an absolute or relative path without
        // triggering a jassert!
        if (inFilename.isNotEmpty() && jassertion.filename != juce::File().getChildFile (inFilename).getFileName())
            continue;
        
        if (onLineNumber >= 0 && jassertion.lineNumber != onLineNumber)
            continue;
        
        ++numJasserts;
    }
    
    return numJasserts;
}
    
void JassertListener::clearJasserts()
{
    jassertions.clear();
}

#endif // JUCE_LOG_ASSERTIONS || JUCE_DEBUG

#ifdef JUCEY_UNIT_TESTS

class JassertListenerUnitTests : public juce::UnitTest
{
public:
    JassertListenerUnitTests() : juce::UnitTest ("JassertListener") {}
    
    void runTest() override
    {
        JassertListener jassertListener;
        
        //======================================================================
        beginTest ("constructor");
        expect (jassertListener.getNumJasserts() == 0);
        
        //======================================================================
        beginTest ("getNumJasserts 1");
        
        // adding 'two' because the jassert is 'two' lines below this one, doing
        // this non-programatically would mean we would have to update this
        // variable everytime a new line was added to this file!
        const int lineNumber = __LINE__ + 2;
        
        jassertfalse;
        expect (jassertListener.getNumJasserts() == 1);
        expect (jassertListener.getNumJasserts (true) == 1);
        expect (jassertListener.getNumJasserts (true, __FILE__) == 1);
        expect (jassertListener.getNumJasserts (true, "dummy filename") == 0);
        expect (jassertListener.getNumJasserts (true, __FILE__, lineNumber) == 1);
        expect (jassertListener.getNumJasserts (true, __FILE__, lineNumber - 1) == 0);
        
        //======================================================================
        beginTest ("getNumJasserts 2");
        
        jassert (false);
        expect (jassertListener.getNumJasserts() == 2);
        expect (jassertListener.getNumJasserts (true) == 2);
        expect (jassertListener.getNumJasserts (true, __FILE__) == 2);
        expect (jassertListener.getNumJasserts (true, "dummy filename") == 0);
        expect (jassertListener.getNumJasserts (true, __FILE__, lineNumber) == 1);
        expect (jassertListener.getNumJasserts (true, __FILE__, lineNumber - 1) == 0);
        
        //======================================================================
        beginTest ("clearJasserts");
        
        jassertListener.clearJasserts();
        expect (jassertListener.getNumJasserts() == 0);
        
        //======================================================================
        beginTest ("filename");
        
        jassert (false);
        expect (jassertListener.getNumJasserts (true, "jucey_JassertListener.cpp") == 1);
        expect (jassertListener.getNumJasserts (true, "~/jucey_JassertListener.cpp") == 1);
        expect (jassertListener.getNumJasserts (true, "../jucey_JassertListener.cpp") == 1);
        expect (jassertListener.getNumJasserts (true, "/foo/jucey_JassertListener.cpp") == 1);
        expect (jassertListener.getNumJasserts (true, "jucey_JassertListener.h") == 0);
        expect (jassertListener.getNumJasserts (true, "~/jucey_JassertListener.h") == 0);
        expect (jassertListener.getNumJasserts (true, "../jucey_JassertListener.h") == 0);
        expect (jassertListener.getNumJasserts (true, "/foo/jucey_JassertListener.h") == 0);
        
        //======================================================================
        beginTest ("JUCE multi-threaded jasserts");
        
        jassertListener.clearJasserts();
        
        juce::WaitableEvent hasTriggeredJassert;
        juce::Thread::launch ([&](){ jassertfalse; hasTriggeredJassert.signal(); });
        hasTriggeredJassert.wait();
        
        expect (jassertListener.getNumJasserts() == 1);
        expect (jassertListener.getNumJasserts (true) == 0);
        
        //======================================================================
        beginTest ("STL multi-threaded jasserts");
        
        jassertListener.clearJasserts();
        
        std::thread stdThread ([](){ jassertfalse; });
        stdThread.join();
        
        expect (jassertListener.getNumJasserts() == 1);
        expect (jassertListener.getNumJasserts (true) == 0);
      
        //======================================================================
        beginTest ("destructor");
        
        jassertListener.clearJasserts();
        
        {
            JassertListener jassertListener2;
            juce::Logger::setCurrentLogger (nullptr);
        }
        
        expect (jassertListener.getNumJasserts (true) == 1);
    }
};

static JassertListenerUnitTests staticJassertListenerUnitTests;

#endif // JUCEY_UNIT_TESTS
