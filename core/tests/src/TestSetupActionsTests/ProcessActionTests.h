/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_TESTSETUPACTIONSTESTS_PROCESSACTIONTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_TESTSETUPACTIONSTESTS_PROCESSACTIONTESTS_H_

#include <Ishiko/TestFramework/Core.hpp>

class ProcessActionTests : public Ishiko::TestSequence
{
public:
    ProcessActionTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void CreationTest1(Ishiko::Test& test);
    static void SetupFailureTest1(Ishiko::Test& test);
    static void SetupWaitForExitTest1(Ishiko::Test& test);
    static void SetupTerminateTest1(Ishiko::Test& test);
};

#endif
