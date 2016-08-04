
#include "jucey_ScopedLoggerIntercepter.h"

ScopedLoggerIntercepter::ScopedLoggerIntercepter()
    : logger (juce::Logger::getCurrentLogger())
    , shouldForwardMessagesOnExitFlag (true)
{
    juce::Logger::setCurrentLogger (this);
}
    
ScopedLoggerIntercepter::~ScopedLoggerIntercepter()
{
    juce::Logger::setCurrentLogger (logger);
    
    if (logger && shouldForwardMessagesOnExitFlag)
    {
        for (int i = 0; i < messages.size(); ++i)
        {
            Logger::writeToLog (messages[i]);
        }
    }
}

void ScopedLoggerIntercepter::setShouldForwardMessagesOnExit (bool shouldForwardMessagesOnExit)
{
    shouldForwardMessagesOnExitFlag = shouldForwardMessagesOnExit;
}
    
bool ScopedLoggerIntercepter::containsMessage (juce::StringRef message, bool ignoreCase) const
{
    for (int i = 0; i < messages.size(); ++i)
    {
        if (messages[i] == message)
            return true;
    }
    
    return false;
}
    
bool ScopedLoggerIntercepter::containsMessageStartingWith (juce::StringRef messageStart, bool ignoreCase) const
{
    for (int i = 0; i < messages.size(); ++i)
    {
        if (messages[i].startsWith (messageStart))
            return true;
    }
    
    return false;
}

bool ScopedLoggerIntercepter::removeMessage (juce::StringRef message, bool ignoreCase)
{
    int size = messages.size();
    messages.removeString (message, ignoreCase);
    return size > messages.size();
}

bool ScopedLoggerIntercepter::removeMessageStartingWith (juce::StringRef messageStart, bool ignoreCase)
{
    int size = messages.size();
    if (ignoreCase)
    {
        for (int i = size; --i >= 0;)
            if (messages.getReference (i).startsWithIgnoreCase (messageStart))
                messages.remove (i);
    }
    else
    {
        for (int i = size; --i >= 0;)
            if (messages.getReference (i).startsWith (messageStart))
                messages.remove (i);
    }
    return size > messages.size();
}

void ScopedLoggerIntercepter::logMessage (const juce::String& message)
{
    messages.add (message);
}
