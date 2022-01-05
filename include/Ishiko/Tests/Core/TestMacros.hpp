/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_CORE_TESTMACROS_HPP_
#define _ISHIKO_TESTS_CORE_TESTMACROS_HPP_

#include "TestMacrosFormatter.h"

#define ISHIKO_ABORT() test.abort(__FILE__, __LINE__)
// The double negation is needed to cope with classes that have an explicit operator bool
#define ISHIKO_ABORT_IF(condition) test.abortIf(!!(condition), __FILE__, __LINE__)
#define ISHIKO_ABORT_IF_NOT(condition) test.abortIf(!(condition), __FILE__, __LINE__)
#define ISHIKO_ABORT_IF_EQ(value1, value2) ISHIKO_ABORT_IF((value1) == (value2))
#define ISHIKO_ABORT_IF_NEQ(value1, value2) ISHIKO_ABORT_IF((value1) != (value2))
#define ISHIKO_ABORT_IF_STR_EQ(value1, value2) ISHIKO_ABORT_IF(strcmp(value1, value2) == 0)
#define ISHIKO_ABORT_IF_STR_NEQ(value1, value2) ISHIKO_ABORT_IF(strcmp(value1, value2) != 0)
#define ISHIKO_FAIL() test.fail(__FILE__, __LINE__)

// The double negation is needed to cope with classes that have an explicit operator bool
#define ISHIKO_FAIL_IF(condition)                                                                \
    if (!!(condition))                                                                           \
    {                                                                                            \
        std::string message =                                                                    \
            Ishiko::Tests::TestMacrosFormatter::Format("ISHIKO_FAIL_IF", #condition, condition); \
        test.fail(message, __FILE__, __LINE__);                                                  \
    }

#define ISHIKO_FAIL_IF_NOT(condition)                                                                \
    if (!(condition))                                                                                \
    {                                                                                                \
        std::string message =                                                                        \
            Ishiko::Tests::TestMacrosFormatter::Format("ISHIKO_FAIL_IF_NOT", #condition, condition); \
        test.fail(message, __FILE__, __LINE__);                                                      \
    }

#define ISHIKO_FAIL_IF_EQ(value, reference)                                                                        \
    if ((value) == (reference))                                                                                    \
    {                                                                                                              \
        std::string message =                                                                                      \
            Ishiko::Tests::TestMacrosFormatter::Format("ISHIKO_FAIL_IF_EQ", #value, #reference, value, reference); \
        test.fail(message, __FILE__, __LINE__);                                                                    \
    }

#define ISHIKO_FAIL_IF_NEQ(value, reference)                                                                        \
    if ((value) != (reference))                                                                                     \
    {                                                                                                               \
        std::string message =                                                                                       \
            Ishiko::Tests::TestMacrosFormatter::Format("ISHIKO_FAIL_IF_NEQ", #value, #reference, value, reference); \
        test.fail(message, __FILE__, __LINE__);                                                                     \
    }

#define ISHIKO_FAIL_IF_STR_EQ(value1, value2) ISHIKO_FAIL_IF(strcmp(value1, value2) == 0)
#define ISHIKO_FAIL_IF_STR_NEQ(value1, value2) ISHIKO_FAIL_IF(strcmp(value1, value2) != 0)

#define ISHIKO_FAIL_IF_NOT_CONTAIN(output, str)                                                                   \
    if (std::string(output).find(str) == std::string::npos)                                                       \
    {                                                                                                             \
        std::string message =                                                                                     \
            Ishiko::Tests::TestMacrosFormatter::Format("ISHIKO_FAIL_IF_NOT_CONTAIN", #output, #str, output, str); \
        test.fail(message, __FILE__, __LINE__);                                                                   \
    }

#define ISHIKO_PASS() test.pass()

#define ISHIKO_SKIP() test.skip()

#endif
