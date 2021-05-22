/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_TESTFRAMEWORK_TESTS_CORE_TESTHARNESSCOMMANDLINETESTS_H_
#define _ISHIKO_TESTFRAMEWORK_TESTS_CORE_TESTHARNESSCOMMANDLINETESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"

class TestHarnessCommandLineTests : public Ishiko::Tests::TestSequence
{
public:
    TestHarnessCommandLineTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
};

#endif
