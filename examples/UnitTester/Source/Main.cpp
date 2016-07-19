
#include "JuceHeader.h"

//==============================================================================
int main (int argc, char* argv[])
{
    UnitTestRunner unitTestRunner;
    unitTestRunner.setAssertOnFailure (false);
    unitTestRunner.runAllTests();
    
    int numFailedTests = 0;
    int numTests = unitTestRunner.getNumResults();
    
    for (int resultIndex = 0; resultIndex < numTests; ++resultIndex)
    {
        if (const UnitTestRunner::TestResult* testResult = unitTestRunner.getResult (resultIndex))
            numFailedTests += testResult->failures;
    }
    
    String message;
    message <<  newLine << "Completed " << numTests << " tests";
    Logger::outputDebugString (message);
    
    return numFailedTests;
}
