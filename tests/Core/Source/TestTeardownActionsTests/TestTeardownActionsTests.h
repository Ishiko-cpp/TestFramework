/*
    Copyright (c) 2015-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TEST_TESTFRAMEWORK_CORE_TESTTEARDOWNACTIONSTESTS_TESTTEARDOWNACTIONSTESTS_H_
#define _ISHIKO_TEST_TESTFRAMEWORK_CORE_TESTTEARDOWNACTIONSTESTS_TESTTEARDOWNACTIONSTESTS_H_

#include <Ishiko/Tests/TestFrameworkCore.h>

class TestTeardownActionsTests : public Ishiko::Tests::TestSequence
{
public:
    TestTeardownActionsTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);
};

#endif
