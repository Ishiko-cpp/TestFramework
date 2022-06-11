/*
    Copyright (c) 2007-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_TESTSEQUENCETESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_TESTSEQUENCETESTS_H_

#include <Ishiko/TestFramework/Core.hpp>

class TestSequenceTests : public Ishiko::TestSequence
{
public:
    TestSequenceTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void AppendTest1(Ishiko::Test& test);
    static void AppendTest2(Ishiko::Test& test);
    static void GetResultTest1(Ishiko::Test& test);
    static void GetResultTest2(Ishiko::Test& test);
    static void GetResultTest3(Ishiko::Test& test);
    static void GetResultTest4(Ishiko::Test& test);
    static void GetResultTest5(Ishiko::Test& test);
    static void GetResultTest6(Ishiko::Test& test);
};

#endif
