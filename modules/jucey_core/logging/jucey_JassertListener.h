
#pragma once

#if JUCE_LOG_ASSERTIONS

/** Listens to and captures jassert events by monitoring logger messages.

    NOTE:   JUCE_LOG_ASSERTIONS must be enabled for this class to function
            correctly. juce::Logger::setCurrentLogger() mustn't be called during
            the lifetime of this object.
 */
class JassertListener : private juce::Logger
{
public:
    /** Constructor */
    JassertListener() noexcept;
    
    /** Destructor */
    ~JassertListener();
    
    /** Returns the number of captured jassert events.
     
        @param currentThreadOnly    If true this function will disregard jassert
                                    events that did not occur on the currently
                                    executing thread.
     
        @param inFilename           If non-empty this function will disregard
                                    jassert events that occured in files that
                                    do not match the specified filename. Note
                                    this argument ignores everything except the
                                    last section of the path.
     
                                    e.g. "foo.cpp", "../../foo.cpp",
                                    "/bar/foo.cpp", "~/foo.cpp" are all the same
                                    as far as this argument is concerned.
     
        @param onLineNumber         If non-negative this function will disregard
                                    jassert events that occured on line numbers
                                    that do not match the specified line number.
                                    This is best used in conjunction with the
                                    `inFilename` argument to more precisely
                                    identify a jassert that was triggered.
     
        @see clearJasserts, juce::File::getFileName
     */
    int getNumJasserts (bool currentThreadOnly = false,
                        const juce::String& inFilename = juce::String(),
                        int onLineNumber = -1) const;
    
    /** Discards any previosuly captured jassert events, such that
        `getNumJasserts` will return 0.
     
        @see getNumJasserts
     */
    void clearJasserts();
    
private:
    void logMessage (const juce::String& message) override;
    
    struct Jassertion
    {
        juce::Thread::ThreadID threadId {};
        juce::String filename {};
        int lineNumber = -1;
    };
    
    juce::Logger* logger {};
    juce::StringArray messages;
    juce::Array<Jassertion> jassertions;
};

#else // JUCE_LOG_ASSERTIONS

#define JassertListener \
    static_assert (false, "Enable JUCE_LOG_ASSERTIONS to use the JassertListener class");

#endif // JUCE_LOG_ASSERTIONS
