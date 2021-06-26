/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_TESTFRAMEWORK_CORE_TESTMACROS_H_
#define _ISHIKO_TESTFRAMEWORK_CORE_TESTMACROS_H_

#include "TestMacrosFormatter.h"

#define ISHTF_ABORT() test.abort(__FILE__, __LINE__)
// The double negation is needed to cope with classes that have an explicit operator bool
#define ISHTF_ABORT_IF(condition) test.abortIf(!!(condition), __FILE__, __LINE__)
#define ISHTF_ABORT_IF_NOT(condition) test.abortIf(!(condition), __FILE__, __LINE__)
#define ISHTF_ABORT_IF_EQ(value1, value2) ISHTF_ABORT_IF((value1) == (value2))
#define ISHTF_ABORT_IF_NEQ(value1, value2) ISHTF_ABORT_IF((value1) != (value2))
#define ISHTF_ABORT_IF_STR_EQ(value1, value2) ISHTF_ABORT_IF(strcmp(value1, value2) == 0)
#define ISHTF_ABORT_IF_STR_NEQ(value1, value2) ISHTF_ABORT_IF(strcmp(value1, value2) != 0)
#define ISHTF_FAIL() test.fail(__FILE__, __LINE__)

// The double negation is needed to cope with classes that have an explicit operator bool
#define ISHTF_FAIL_IF(condition)                                                                \
    if (!!(condition))                                                                          \
    {                                                                                           \
        std::string message =                                                                   \
            Ishiko::Tests::TestMacrosFormatter::Format("ISHTF_FAIL_IF", #condition, condition); \
        test.fail(message, __FILE__, __LINE__);                                                 \
    }

#define ISHTF_FAIL_IF_NOT(condition) test.failIf(!(condition), __FILE__, __LINE__)
#define ISHTF_FAIL_IF_EQ(value1, value2) ISHTF_FAIL_IF((value1) == (value2))

#define ISHTF_FAIL_IF_NEQ(value, reference)                                                                        \
    if ((value) != (reference))                                                                                    \
    {                                                                                                              \
        std::string message =                                                                                      \
            Ishiko::Tests::TestMacrosFormatter::Format("ISHTF_FAIL_IF_NEQ", #value, #reference, value, reference); \
        test.fail(message, __FILE__, __LINE__);                                                                    \
    }

#define ISHTF_FAIL_IF_STR_EQ(value1, value2) ISHTF_FAIL_IF(strcmp(value1, value2) == 0)
#define ISHTF_FAIL_IF_STR_NEQ(value1, value2) ISHTF_FAIL_IF(strcmp(value1, value2) != 0)

#define ISHTF_FAIL_IF_NOT_CONTAIN(output, str)                                                                   \
    if (std::string(output).find(str) == std::string::npos)                                                      \
    {                                                                                                            \
        std::string message =                                                                                    \
            Ishiko::Tests::TestMacrosFormatter::Format("ISHTF_FAIL_IF_NOT_CONTAIN", #output, #str, output, str); \
        test.fail(message, __FILE__, __LINE__);                                                                  \
    }

#define ISHTF_PASS() test.pass()

#endif
