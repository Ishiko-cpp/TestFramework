// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTMACROS_HPP
#define GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTMACROS_HPP

#include "DebugHeap.hpp"
#include "Test.hpp"
#include "TestMacrosFormatter.hpp"
#include <Ishiko/BasePlatform.hpp>
#include <string>

// TODO: all macros need to follow the scheme where they print the data

#define ISHIKO_TEST_ABORT() test.abort(__FILE__, __LINE__)
// The double negation is needed to cope with classes that have an explicit operator bool
#define ISHIKO_TEST_ABORT_IF(condition) test.abortIf(!!(condition), __FILE__, __LINE__)
#define ISHIKO_TEST_ABORT_IF_NOT(condition) test.abortIf(!(condition), __FILE__, __LINE__)
#define ISHIKO_TEST_ABORT_IF_EQ(value1, value2) ISHIKO_TEST_ABORT_IF((value1) == (value2))

#define ISHIKO_TEST_ABORT_IF_NEQ(value, reference)                                                                 \
    if ((value) != (reference))                                                                                    \
    {                                                                                                              \
        std::string message =                                                                                      \
            Ishiko::TestMacrosFormatter::Format("ISHIKO_TEST_ABORT_IF_NEQ", #value, #reference, value, reference); \
        test.abort(message, __FILE__, __LINE__);                                                                   \
    }

#define ISHIKO_TEST_ABORT_IF_STR_EQ(value1, value2) ISHIKO_TEST_ABORT_IF(strcmp(value1, value2) == 0)
#define ISHIKO_TEST_ABORT_IF_STR_NEQ(value1, value2) ISHIKO_TEST_ABORT_IF(strcmp(value1, value2) != 0)

#define ISHIKO_TEST_FAIL()                                 \
    {                                                      \
        std::string message = "ISHIKO_TEST_FAIL() failed"; \
        test.fail(message, __FILE__, __LINE__);            \
    }

// The double negation is needed to cope with classes that have an explicit operator bool
#define ISHIKO_TEST_FAIL_IF(condition)                                                         \
    if (!!(condition))                                                                         \
    {                                                                                          \
        std::string message =                                                                  \
            Ishiko::TestMacrosFormatter::Format("ISHIKO_TEST_FAIL_IF", #condition, condition); \
        test.fail(message, __FILE__, __LINE__);                                                \
    }

#define ISHIKO_TEST_FAIL_IF_NOT(condition)                                                         \
    if (!(condition))                                                                              \
    {                                                                                              \
        std::string message =                                                                      \
            Ishiko::TestMacrosFormatter::Format("ISHIKO_TEST_FAIL_IF_NOT", #condition, condition); \
        test.fail(message, __FILE__, __LINE__);                                                    \
    }

#define ISHIKO_TEST_FAIL_IF_EQ(value, reference)                                                                 \
    if ((value) == (reference))                                                                                  \
    {                                                                                                            \
        std::string message =                                                                                    \
            Ishiko::TestMacrosFormatter::Format("ISHIKO_TEST_FAIL_IF_EQ", #value, #reference, value, reference); \
        test.fail(message, __FILE__, __LINE__);                                                                  \
    }

#define ISHIKO_TEST_FAIL_IF_NEQ(value, reference)                                                                 \
    if ((value) != (reference))                                                                                   \
    {                                                                                                             \
        std::string message =                                                                                     \
            Ishiko::TestMacrosFormatter::Format("ISHIKO_TEST_FAIL_IF_NEQ", #value, #reference, value, reference); \
        test.fail(message, __FILE__, __LINE__);                                                                   \
    }

#define ISHIKO_TEST_FAIL_IF_STR_EQ(value, reference)                                                                 \
    if (strcmp(value, reference) == 0)                                                                               \
    {                                                                                                                \
        std::string message =                                                                                        \
            Ishiko::TestMacrosFormatter::Format("ISHIKO_TEST_FAIL_IF_STR_EQ", #value, #reference, value, reference); \
        test.fail(message, __FILE__, __LINE__);                                                                      \
    }

#define ISHIKO_TEST_FAIL_IF_STR_NEQ(value, reference)                                                                 \
    if (strcmp(value, reference) != 0)                                                                                \
    {                                                                                                                 \
        std::string message =                                                                                         \
            Ishiko::TestMacrosFormatter::Format("ISHIKO_TEST_FAIL_IF_STR_NEQ", #value, #reference, value, reference); \
        test.fail(message, __FILE__, __LINE__);                                                                       \
    }

#define ISHIKO_TEST_FAIL_IF_NOT_CONTAIN(output, str)                                                            \
    if (std::string(output).find(str) == std::string::npos)                                                     \
    {                                                                                                           \
        std::string message =                                                                                   \
            Ishiko::TestMacrosFormatter::Format("ISHIKO_TEST_FAIL_IF_NOT_CONTAIN", #output, #str, output, str); \
        test.fail(message, __FILE__, __LINE__);                                                                 \
    }

#if ((ISHIKO_RUNTIME == ISHIKO_RUNTIME_MICROSOFT_CRT) && defined(_DEBUG))
#define ISHIKO_TEST_FAIL_IF_HEAP_ALLOCATION_COUNT_NEQ(reference)                                                         \
    if (test.allocationCount() != (reference))                                                                           \
    {                                                                                                                    \
        std::string message =                                                                                            \
            Ishiko::TestMacrosFormatter::Format("ISHIKO_TEST_FAIL_IF_HEAP_ALLOCATION_COUNT_NEQ", #reference, reference); \
        test.fail(message, __FILE__, __LINE__);                                                                          \
    }
#else
#define ISHIKO_TEST_FAIL_IF_HEAP_ALLOCATION_COUNT_NEQ(reference)
#endif

// TODO: can I avoid the tracking state nightmare here?
#define ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(...)                                 \
    {                                                                                           \
        Ishiko::DebugHeap::TrackingState trackingState;                                         \
        trackingState.disableTracking();                                                        \
        std::shared_ptr<Ishiko::FileComparisonTestCheck> check =                                \
            std::make_shared<Ishiko::FileComparisonTestCheck>(                                  \
                Ishiko::FileComparisonTestCheck::CreateFromContext(test.context(), __VA_ARGS__, \
                    Ishiko::TestContext::PathResolution::platform_specific));                   \
        test.appendCheck(check);                                                                \
        trackingState.restore();                                                                \
        check->run(test, __FILE__, __LINE__);                                                   \
    }

#define ISHIKO_TEST_PASS() test.pass()

#define ISHIKO_TEST_SKIP() test.skip()

#endif
