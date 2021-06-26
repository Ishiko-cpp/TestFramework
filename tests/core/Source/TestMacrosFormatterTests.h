/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_TESTMACROSFORMATTERTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_TESTMACROSFORMATTERTESTS_H_

#include <Ishiko/Tests/core.h>

class TestMacrosFormatterTests : public Ishiko::Tests::TestSequence
{
public:
    TestMacrosFormatterTests(const Ishiko::Tests::TestNumber& number,
        const Ishiko::Tests::TestEnvironment& environment);

private:
    static void FormatTest1(Ishiko::Tests::Test& test);
    static void FormatTest2(Ishiko::Tests::Test& test);
    static void FormatTest3(Ishiko::Tests::Test& test);
    static void FormatTest4(Ishiko::Tests::Test& test);
    static void FormatTest5(Ishiko::Tests::Test& test);
    static void FormatTest6(Ishiko::Tests::Test& test);
};

#endif
