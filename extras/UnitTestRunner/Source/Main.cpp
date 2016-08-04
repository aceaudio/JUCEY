
#include "JuceHeader.h"

class ConsoleLogger : public Logger
{
    void logMessage (const String& message) override
    {
        std::cout << message << std::endl;
    }
};
        
//==============================================================================
int main (int argc, char* argv[])
{
    ignoreUnused (argc, argv);
    
    ConsoleLogger consoleLogger;
    Logger::setCurrentLogger (&consoleLogger);
    
    UnitTestRunner unitTestRunner;
    unitTestRunner.setAssertOnFailure (false);
    unitTestRunner.runAllTests();
    
    int numTestsPassed = 0;
    int numTestsFailed = 0;
    
    for (int resultIndex = 0; resultIndex < unitTestRunner.getNumResults(); ++resultIndex)
    {
        if (const UnitTestRunner::TestResult* testResult = unitTestRunner.getResult (resultIndex))
        {
            numTestsPassed += testResult->passes;
            numTestsFailed += testResult->failures;
        }
    }
    
    String message;
    message << "\n";
    message << numTestsPassed << " tests passed\n";
    message << numTestsFailed << " tests failed";
    Logger::writeToLog (message);
    Logger::setCurrentLogger (nullptr);
    
    return numTestsFailed;
}
