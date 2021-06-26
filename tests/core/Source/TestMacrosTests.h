/*
    Copyright (c) 2019-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_TESTMACROSTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_TESTMACROSTESTS_H_

#include <Ishiko/Tests/Core.h>

class TestMacrosTests : public Ishiko::Tests::TestSequence
{
public:
    TestMacrosTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void PassMacroTest1(Ishiko::Tests::Test& test);
    static void FailMacroTest1(Ishiko::Tests::Test& test);
    static void FailIfMacroTest1(Ishiko::Tests::Test& test);
    static void FailIfMacroTest2(Ishiko::Tests::Test& test);
    static void FailIfNotMacroTest1(Ishiko::Tests::Test& test);
    static void FailIfNotMacroTest2(Ishiko::Tests::Test& test);
    static void FailIfEqMacroTest1(Ishiko::Tests::Test& test);
    static void FailIfEqMacroTest2(Ishiko::Tests::Test& test);
    static void FailIfNeqMacroTest1(Ishiko::Tests::Test& test);
    static void FailIfNeqMacroTest2(Ishiko::Tests::Test& test);
    static void FailIfStrEqMacroTest1(Ishiko::Tests::Test& test);
    static void FailIfStrEqMacroTest2(Ishiko::Tests::Test& test);
    static void FailIfStrNeqMacroTest1(Ishiko::Tests::Test& test);
    static void FailIfStrNeqMacroTest2(Ishiko::Tests::Test& test);
    static void FailIfNotContainMacroTest1(Ishiko::Tests::Test& test);
    static void FailIfNotContainMacroTest2(Ishiko::Tests::Test& test);
    static void AbortMacroTest1(Ishiko::Tests::Test& test);
    static void AbortIfMacroTest1(Ishiko::Tests::Test& test);
    static void AbortIfMacroTest2(Ishiko::Tests::Test& test);
    static void AbortIfNotMacroTest1(Ishiko::Tests::Test& test);
    static void AbortIfNotMacroTest2(Ishiko::Tests::Test& test);
    static void AbortIfEqMacroTest1(Ishiko::Tests::Test& test);
    static void AbortIfEqMacroTest2(Ishiko::Tests::Test& test);
    static void AbortIfNeqMacroTest1(Ishiko::Tests::Test& test);
    static void AbortIfNeqMacroTest2(Ishiko::Tests::Test& test);
    static void AbortIfStrEqMacroTest1(Ishiko::Tests::Test& test);
    static void AbortIfStrEqMacroTest2(Ishiko::Tests::Test& test);
    static void AbortIfStrNeqMacroTest1(Ishiko::Tests::Test& test);
    static void AbortIfStrNeqMacroTest2(Ishiko::Tests::Test& test);
};

#endif
