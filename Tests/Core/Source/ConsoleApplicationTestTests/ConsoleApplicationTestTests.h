/*
    Copyright (c) 2016-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TEST_TESTFRAMEWORK_CORE_CONSOLEAPPLICATIONTESTTESTS_CONSOLEAPPLICATIONTESTTESTS_H_
#define _ISHIKO_TEST_TESTFRAMEWORK_CORE_CONSOLEAPPLICATIONTESTTESTS_CONSOLEAPPLICATIONTESTTESTS_H_

#include <Ishiko/Tests/TestFrameworkCore.h>

class ConsoleApplicationTestTests : public Ishiko::Tests::TestSequence
{
public:
    ConsoleApplicationTestTests(const Ishiko::Tests::TestNumber& number,
        const Ishiko::Tests::TestEnvironment& environment);

private:
    static void CreationTest1(Ishiko::Tests::Test& test);
    static void RunSuccessTest1(Ishiko::Tests::Test& test);
    static void RunSuccessTest2(Ishiko::Tests::Test& test);
    static void RunFailureTest1(Ishiko::Tests::Test& test);
    static void RunSuccessTest3(Ishiko::Tests::Test& test);
    static void RunFailureTest2(Ishiko::Tests::Test& test);
};

#endif
