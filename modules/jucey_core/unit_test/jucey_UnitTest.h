
#ifndef JUCEY_UNITTEST_H_INCLUDED
#define JUCEY_UNITTEST_H_INCLUDED

#if JUCE_LOG_ASSERTIONS

    /** Checks that the result of an expression logs a message matching some 
        specific text. 
     */
    #define expectMessageLogged(expr, text, failureMessage)                     \
        {                                                                       \
            jucey::ScopedLoggerIntercepter loggerIntercepter;                   \
            {expr;}                                                             \
            expect (loggerIntercepter.removeMessage (text), failureMessage);    \
        }

    /** Checks that the result of an expression does not logs a message matching
        some specific text
     */
    #define expectMessageNotLogged(expr, text, failureMessage)                  \
        {                                                                       \
            jucey::ScopedLoggerIntercepter loggerIntercepter;                   \
            {expr;}                                                             \
            expect ( ! loggerIntercepter.removeMessage (text), failureMessage); \
        }

    /** Checks that the result of an expression logs a message that starts with 
        some specific text.
     */
    #define expectMessageLoggedStartingWith(expr, text, failureMessage)                     \
        {                                                                                   \
            jucey::ScopedLoggerIntercepter loggerIntercepter;                               \
            {expr;}                                                                         \
            expect (loggerIntercepter.removeMessageStartingWith (text), failureMessage);    \
        }
    /** Checks that the result of an expression does not log a message that starts
        with some specific text.
     */
    #define expectMessageNotLoggedStartingWith(expr, text, failureMessage)                  \
        {                                                                                   \
            jucey::ScopedLoggerIntercepter loggerIntercepter;                               \
            {expr;}                                                                         \
            expect ( ! loggerIntercepter.removeMessageStartingWith (text), failureMessage); \
        }

#else // JUCE_LOG_ASSERTIONS

    /** If you hit any of these static asserts it's because JUCE_LOG_ASSERTIONS
        must be enabled when using any of the expectmessage... or expextJassert...
        macros.
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

/** Checks that the result of an expression causes a jassert to be logged. */
#define expectJassert(expr) \
    expectMessageLoggedStartingWith (expr, "JUCE Assertion failure in ", \
                                    "Expected: does jassert, Actual: does not jassert")

/** Checks that the result of an expression causes a jassert to be logged in a 
    specific file only.
 */
#define expectJassertIn(expr, file) \
    expectMessageLoggedStartingWith (expr, "JUCE Assertion failure in " file, \
                                    "Expected: does jassert in " file " , Actual: does not jassert in " file)

/** Checks that the result of an expression does not cause a jassert to be logged. */
#define expectDoesNotJassert(expr) \
    expectMessageNotLoggedStartingWith (expr, "JUCE Assertion failure in ", \
                                       "Expected: does not jassert, Actual: does jassert.");

/** Checks that the result of an expression does not cause a jassert to be logged
    in a secific file only. 
 */
#define expectDoesNotJassertIn(expr, file) \
    expectMessageNotLoggedStartingWith (expr, "JUCE Assertion failure in " file, \
                                       "Expected: does not jassert in " file " , Actual: does jassert in " file)

#endif // JUCEY_UNITTEST_H_INCLUDED
