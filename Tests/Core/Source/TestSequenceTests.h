/*
    Copyright (c) 2007-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TEST_TESTFRAMEWORK_CORE_TESTSEQUENCETESTS_H_
#define _ISHIKO_TEST_TESTFRAMEWORK_CORE_TESTSEQUENCETESTS_H_

#include <Ishiko/Tests/TestFrameworkCore.h>

class TestSequenceTests : public Ishiko::Tests::TestSequence
{
public:
    TestSequenceTests(const Ishiko::Tests::TestNumber& number,
        const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void AppendTest1(Ishiko::Tests::Test& test);
    static void AppendTest2(Ishiko::Tests::Test& test);
    static void GetResultTest1(Ishiko::Tests::Test& test);
    static void GetResultTest2(Ishiko::Tests::Test& test);
    static void GetResultTest3(Ishiko::Tests::Test& test);
};

#endif
