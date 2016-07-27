
#ifndef JUCEY_UNITTEST_H_INCLUDED
#define JUCEY_UNITTEST_H_INCLUDED

#if JUCE_LOG_ASSERTIONS

    #define expectMessageLogged_3(expr, text, failureMessage)               \
        {                                                                   \
            jucey::ScopedLogger scopedLogger;                               \
            {expr;}                                                         \
            expect (scopedLogger.containsMessage (text), failureMessage);   \
        }

    #define expectMessageNotLogged_3(expr, text, failureMessage)                \
        {                                                                       \
            jucey::ScopedLogger scopedLogger;                                   \
            {expr;}                                                             \
            expect ( ! scopedLogger.containsMessage (text), failureMessage);    \
        }

    #define expectMessageLoggedStartingWith_3(expr, text, failureMessage)               \
        {                                                                               \
            jucey::ScopedLogger scopedLogger;                                           \
            {expr;}                                                                     \
            expect (scopedLogger.containsMessageStartingWith (text), failureMessage);   \
        }

    #define expectMessageNotLoggedStartingWith_3(expr, text, failureMessage)                \
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

    #define expectMessageLogged_3(expr, text, failureMessage) \
        static_jassert (false)

    #define expectMessageNotLogged_3(expr, text, failureMessage) \
        static_jassert (false)

    #define expectMessageLoggedStartingWith_3(expr, text, failureMessage) \
        static_jassert (false)

    #define expectMessageNotLoggedStartingWith_3(expr, text, failureMessage) \
        static_jassert (false)

#endif // JUCE_LOG_ASSERTIONS

#if JUCE_WINDOWS
    #define JUCEY_EXPAND_VA_ARGS(x) x
#else // JUCE_WINDOWS
    #define JUCEY_EXPAND_VA_ARGS(...) __VA_ARGS__
#endif // JUCE_WINDOWS

#define JUCEY_COUNT_ARGS_HELPER(_10, _9, _8, _7, _6, _5, _4, _3, _2, _1, N, ...) N

#define JUCEY_COUNT_ARGS(...) \
    JUCEY_COUNT_ARGS_HELPER(JUCEY_EXPAND_MACRO (__VA_ARGS__), 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define expectMessageLogged_2(expr, text) \
    expectMessageLogged_3 (expr, text, juce::String())

#define expectMessageNotLogged_2(expr, text) \
    expectMessageNotLogged_3 (expr, text, juce::String())

#define expectMessageLoggedStartingWith_2(expr, text) \
    expectMessageLoggedStartingWith_3 (expr, text, juce::String())

#define expectMessageNotLoggedStartingWith_2(expr, text) \
    expectMessageNotLoggedStartingWith_3 (expr, text, juce::String())

#define expectMessageLogged(...) \
    JUCE_JOIN_MACRO (expectMessageLogged_, JUCEY_COUNT_ARGS (JUCEY_EXPAND_MACRO (__VA_ARGS__))) (__VA_ARGS__)

#define expectMessageNotLogged(...) \
    JUCE_JOIN_MACRO (expectMessageNotLogged_, JUCEY_COUNT_ARGS(__VA_ARGS__)) (__VA_ARGS__)

#define expectMessageLoggedStartingWith(...) \
    JUCE_JOIN_MACRO (expectMessageLoggedStartingWith_, JUCEY_COUNT_ARGS(__VA_ARGS__)) (__VA_ARGS__)

#define expectMessageNotLoggedStartingWith(...) \
    JUCE_JOIN_MACRO (expectMessageNotLoggedStartingWith_, JUCEY_COUNT_ARGS(__VA_ARGS__)) (__VA_ARGS__)

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
