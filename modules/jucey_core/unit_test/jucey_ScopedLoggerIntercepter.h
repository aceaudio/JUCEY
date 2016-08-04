
#ifndef JUCEY_SCOPEDLOGGERINTERCEPTER_H_INCLUDED
#define JUCEY_SCOPEDLOGGERINTERCEPTER_H_INCLUDED

/**
    Intercepts messages sent to the global logger during the lifetime of this
    object, allowing them to be easily read.
 
    Messages can optionally be forwarded back to the original logger before
    this logger is destoyed.
     
    @see Logger, FileLogger
 */
class ScopedLoggerIntercepter : public juce::Logger
{
public:
    ScopedLoggerIntercepter();
    ~ScopedLoggerIntercepter();
    
    /** Enables or disables intercepted messages from appearing in the original 
        logger.
     */
    void setShouldForwardMessagesOnExit (bool shouldForwardMessagesOnExit);
    
    /** Returns true if any intercepted messages match the given string.
     
        @param message      the message to find
        @param ignoreCase   whether messages should be matched case-insensitive
     */
    bool containsMessage (juce::StringRef message, bool ignoreCase = false) const;
    
    /** Returns true if any intercepted messages start with the given string.
     
        @param messageStart    the start of a message to find
        @param ignoreCase      whether messages should be matched case-insensitive
     */
    bool containsMessageStartingWith (juce::StringRef messageStart, bool ignoreCase = false) const;
    
    /** This will remove all messages matching the given string.
        Feturns true if any messages were removed.
        
        @param message      the message to find and remove
        @param ignoreCase   whether messages should be matched case-insensitive
     */
    bool removeMessage (juce::StringRef message, bool ignoreCase = false);
    
    /** This will remove all messages starting with the given string.
        Returns true if any messages were removed.
     
        @param messageStart    the start of a message to find and remove
        @param ignoreCase      whether messages should be matched case-insensitive
     */
    bool removeMessageStartingWith (juce::StringRef messageStart, bool ignoreCase = false);
    
    /** Intercepts messages */
    void logMessage (const juce::String& message) final;
    
private:
    juce::Logger* logger;
    juce::StringArray messages;
    bool shouldForwardMessagesOnExitFlag;
};

#endif // JUCEY_SCOPEDLOGGER_H_INCLUDED
