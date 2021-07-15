/*
    Copyright (c) 2007-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_TESTTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_TESTTESTS_H_

#include <Ishiko/Tests/Core.h>

class TestTests : public Ishiko::Tests::TestSequence
{
public:
    TestTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void ConstructorTest2(Ishiko::Tests::Test& test);
    static void ConstructorTest3(Ishiko::Tests::Test& test);
    static void ConstructorTest4(Ishiko::Tests::Test& test);
    static void ConstructorTest5(Ishiko::Tests::Test& test);
    static void PassTest1(Ishiko::Tests::Test& test);
    static void FailTest1(Ishiko::Tests::Test& test);
    static void FailTest2(Ishiko::Tests::Test& test);
    static void FailIfTest1(Ishiko::Tests::Test& test);
    static void FailIfTest2(Ishiko::Tests::Test& test);
    static void FailIfTest3(Ishiko::Tests::Test& test);
    static void RunTest1(Ishiko::Tests::Test& test);
    static void RunTest2(Ishiko::Tests::Test& test);
    static void RunTest3(Ishiko::Tests::Test& test);
    static void RunTest4(Ishiko::Tests::Test& test);
    static void RunTest5(Ishiko::Tests::Test& test);
    static void AbortTest1(Ishiko::Tests::Test& test);
    static void SkipTest1(Ishiko::Tests::Test& test);
};

#endif
