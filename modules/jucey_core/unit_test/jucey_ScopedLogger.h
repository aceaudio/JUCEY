
#ifndef JUCEY_SCOPEDLOGGER_H_INCLUDED
#define JUCEY_SCOPEDLOGGER_H_INCLUDED

class ScopedLogger : public juce::Logger
{
public:
    ScopedLogger();
    ~ScopedLogger();
    
    bool containsMessage (juce::StringRef text) const;
    bool containsMessageStartingWith (juce::StringRef text) const;
    void logMessage (const juce::String& message) final;
    
private:
    juce::Logger* logger;
    juce::StringArray messages;
};

#endif // JUCEY_SCOPEDLOGGER_H_INCLUDED
