/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_TESTNUMBERTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_TESTNUMBERTESTS_H_

#include <Ishiko/Tests/Core.hpp>

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
