/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_TESTNUMBERTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_TESTNUMBERTESTS_H_

#include <Ishiko/Tests/Core.hpp>

class TestNumberTests : public Ishiko::Tests::TestSequence
{
public:
    TestNumberTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void ConstructorTest2(Ishiko::Tests::Test& test);
    static void GetDeeperNumberTest1(Ishiko::Tests::Test& test);
};

#endif
