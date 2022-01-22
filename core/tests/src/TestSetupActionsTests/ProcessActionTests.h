/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_TESTSETUPACTIONSTESTS_PROCESSACTIONTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_TESTSETUPACTIONSTESTS_PROCESSACTIONTESTS_H_

#include <Ishiko/Tests/Core.hpp>

class ProcessActionTests : public Ishiko::Tests::TestSequence
{
public:
    ProcessActionTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestContext& context);

private:
    static void CreationTest1(Ishiko::Tests::Test& test);
    static void SetupFailureTest1(Ishiko::Tests::Test& test);
    static void SetupWaitForExitTest1(Ishiko::Tests::FileComparisonTest& test);
    static void SetupTerminateTest1(Ishiko::Tests::Test& test);
};

#endif
