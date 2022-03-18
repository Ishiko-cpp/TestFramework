/*
    Copyright (c) 2007-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_TESTTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_TESTTESTS_H_

#include <Ishiko/Tests/Core.hpp>

class TestTests : public Ishiko::TestSequence
{
public:
    TestTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void ConstructorTest2(Ishiko::Test& test);
    static void ConstructorTest3(Ishiko::Test& test);
    static void ConstructorTest4(Ishiko::Test& test);
    static void ConstructorTest5(Ishiko::Test& test);
    static void PassTest1(Ishiko::Test& test);
    static void FailTest1(Ishiko::Test& test);
    static void FailTest2(Ishiko::Test& test);
    static void FailIfTest1(Ishiko::Test& test);
    static void FailIfTest2(Ishiko::Test& test);
    static void FailIfTest3(Ishiko::Test& test);
    static void RunTest1(Ishiko::Test& test);
    static void RunTest2(Ishiko::Test& test);
    static void RunTest3(Ishiko::Test& test);
    static void RunTest4(Ishiko::Test& test);
    static void RunTest5(Ishiko::Test& test);
    static void AbortTest1(Ishiko::Test& test);
    static void SkipTest1(Ishiko::Test& test);
};

#endif
