/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_TEST_TESTFRAMEWORK_CORE_TESTSETUPACTIONSTESTS_PROCESSACTIONTESTS_H_
#define _ISHIKO_TEST_TESTFRAMEWORK_CORE_TESTSETUPACTIONSTESTS_PROCESSACTIONTESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"

class ProcessActionTests : public Ishiko::Tests::TestSequence
{
public:
    ProcessActionTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void CreationTest1(Ishiko::Tests::Test& test);
    static void SetupFailureTest1(Ishiko::Tests::Test& test);
    static void SetupWaitForExitTest1(Ishiko::Tests::FileComparisonTest& test);
    static void SetupTerminateTest1(Ishiko::Tests::Test& test);
};

#endif
