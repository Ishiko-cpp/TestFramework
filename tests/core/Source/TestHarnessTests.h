/*
    Copyright (c) 2007-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_TESTHARNESSTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_TESTHARNESSTESTS_H_

#include <Ishiko/Tests/Core.h>

class TestHarnessTests : public Ishiko::Tests::TestSequence
{
public:
    TestHarnessTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void CreationTest1(Ishiko::Tests::Test& test);
    static void RunTest1(Ishiko::Tests::Test& test);
};

#endif
