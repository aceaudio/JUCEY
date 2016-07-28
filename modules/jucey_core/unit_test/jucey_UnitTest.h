
#ifndef JUCEY_UNITTEST_H_INCLUDED
#define JUCEY_UNITTEST_H_INCLUDED

#if JUCE_LOG_ASSERTIONS

    #define expectMessageLogged(expr, text, failureMessage)                 \
        {                                                                   \
            jucey::ScopedLogger scopedLogger;                               \
            {expr;}                                                         \
            expect (scopedLogger.containsMessage (text), failureMessage);   \
        }

    #define expectMessageNotLogged(expr, text, failureMessage)                  \
        {                                                                       \
            jucey::ScopedLogger scopedLogger;                                   \
            {expr;}                                                             \
            expect ( ! scopedLogger.containsMessage (text), failureMessage);    \
        }

    #define expectMessageLoggedStartingWith(expr, text, failureMessage)                 \
        {                                                                               \
            jucey::ScopedLogger scopedLogger;                                           \
            {expr;}                                                                     \
            expect (scopedLogger.containsMessageStartingWith (text), failureMessage);   \
        }

    #define expectMessageNotLoggedStartingWith(expr, text, failureMessage)                  \
        {                                                                                   \
            jucey::ScopedLogger scopedLogger;                                               \
            {expr;}                                                                         \
            expect ( ! scopedLogger.containsMessageStartingWith (text), failureMessage);    \
        }

#else // JUCE_LOG_ASSERTIONS

    /** If you hit any of these static asserts it's because JUCE_LOG_ASSERTIONS
        must be enabled when using any of the expectmessage... or expextJassert...
        definitions.
     */

    #define expectMessageLogged(expr, text, failureMessage) \
        static_jassert (false)

    #define expectMessageNotLogged(expr, text, failureMessage) \
        static_jassert (false)

    #define expectMessageLoggedStartingWith(expr, text, failureMessage) \
        static_jassert (false)

    #define expectMessageNotLoggedStartingWith(expr, text, failureMessage) \
        static_jassert (false)

#endif // JUCE_LOG_ASSERTIONS

#define expectJassert(expr) \
    expectMessageLoggedStartingWith (expr, "JUCE Assertion failure in ", \
                                    "Expected: does jassert, Actual: does not jassert")

#define expectJassertIn(expr, file) \
    expectMessageLoggedStartingWith (expr, "JUCE Assertion failure in " file, \
                                    "Expected: does jassert in " file " , Actual: does not jassert in " file)

#define expectDoesNotJassert(expr) \
    expectMessageNotLoggedStartingWith (expr, "JUCE Assertion failure in ", \
                                       "Expected: does not jassert, Actual: does jassert.");

#define expectDoesNotJassertIn(expr, file) \
    expectMessageNotLoggedStartingWith (expr, "JUCE Assertion failure in " file, \
                                       "Expected: does not jassert in " file " , Actual: does jassert in " file)

#endif // JUCEY_UNITTEST_H_INCLUDED
