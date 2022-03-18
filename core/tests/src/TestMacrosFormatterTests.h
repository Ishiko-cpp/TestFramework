/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_TESTMACROSFORMATTERTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_TESTMACROSFORMATTERTESTS_H_

#include <Ishiko/Tests/Core.hpp>

class TestMacrosFormatterTests : public Ishiko::TestSequence
{
public:
    TestMacrosFormatterTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void FormatTest1(Ishiko::Test& test);
    static void FormatTest2(Ishiko::Test& test);
    static void FormatTest3(Ishiko::Test& test);
    static void FormatTest4(Ishiko::Test& test);
    static void FormatTest5(Ishiko::Test& test);
    static void FormatTest6(Ishiko::Test& test);
};

#endif
