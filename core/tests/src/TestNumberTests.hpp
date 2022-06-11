/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTS_TESTNUMBERTESTS_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTS_TESTNUMBERTESTS_HPP_

#include <Ishiko/TestFramework/Core.hpp>

class TestNumberTests : public Ishiko::TestSequence
{
public:
    TestNumberTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void ConstructorTest2(Ishiko::Test& test);
    static void GetDeeperNumberTest1(Ishiko::Test& test);
};

#endif
