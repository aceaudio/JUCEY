
#include "jucey_ScopedLogger.h"

ScopedLogger::ScopedLogger()
    : logger (Logger::getCurrentLogger())
{
    Logger::setCurrentLogger (this);
}
    
ScopedLogger::~ScopedLogger()
{
    Logger::setCurrentLogger (logger);
    
    for (juce::String message : messages)
    {
        Logger::writeToLog (message);
    }
}
    
bool ScopedLogger::containsMessage (juce::StringRef text) const
{
    for (int i = 0; i < messages.size(); ++i)
    {
        if (messages[i] == text)
            return true;
    }
    
    return false;
}
    
bool ScopedLogger::containsMessageStartingWith (juce::StringRef text) const
{
    for (int i = 0; i < messages.size(); ++i)
    {
        if (messages[i].startsWith (text))
            return true;
    }
    
    return false;
}
    
void ScopedLogger::logMessage (const juce::String& message)
{
    messages.add (message);
}
