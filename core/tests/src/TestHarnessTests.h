/*
    Copyright (c) 2007-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_TESTHARNESSTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_TESTHARNESSTESTS_H_

#include <Ishiko/TestFramework/Core.hpp>

class TestHarnessTests : public Ishiko::TestSequence
{
public:
    TestHarnessTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void CreationTest1(Ishiko::Test& test);
    static void RunTest1(Ishiko::Test& test);
    static void RunTest2(Ishiko::Test& test);
    static void RunTest3(Ishiko::Test& test);
};

#endif
