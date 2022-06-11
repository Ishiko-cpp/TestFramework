/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_CONSOLEAPPLICATIONTESTTESTS_CONSOLEAPPLICATIONTESTTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_CONSOLEAPPLICATIONTESTTESTS_CONSOLEAPPLICATIONTESTTESTS_H_

#include <Ishiko/TestFramework/Core.hpp>

class ConsoleApplicationTestTests : public Ishiko::TestSequence
{
public:
    ConsoleApplicationTestTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void CreationTest1(Ishiko::Test& test);
    static void RunSuccessTest1(Ishiko::Test& test);
    static void RunSuccessTest2(Ishiko::Test& test);
    static void RunFailureTest1(Ishiko::Test& test);
    static void RunSuccessTest3(Ishiko::Test& test);
    static void RunFailureTest2(Ishiko::Test& test);
};

#endif
