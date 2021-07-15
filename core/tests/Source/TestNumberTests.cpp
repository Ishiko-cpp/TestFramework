/*
    Copyright (c) 2019 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "TestNumberTests.h"

using namespace Ishiko::Tests;

TestNumberTests::TestNumberTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "TestNumber tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("getDeeperNumber test 1", GetDeeperNumberTest1);
}

void TestNumberTests::ConstructorTest1(Test& test)
{
    TestNumber number;

    ISHTF_FAIL_IF_NEQ(number.depth(), 0);
    ISHTF_PASS();
}

void TestNumberTests::ConstructorTest2(Test& test)
{
    TestNumber number(2);

    ISHTF_FAIL_IF_NEQ(number.depth(), 1);
    ISHTF_FAIL_IF_NEQ(number.part(0), 2);
    ISHTF_PASS();
}

void TestNumberTests::GetDeeperNumberTest1(Ishiko::Tests::Test& test)
{
    TestNumber number;
    TestNumber deeperNumber = number.getDeeperNumber();

    ISHTF_FAIL_IF_NEQ(deeperNumber.depth(), 1);
    ISHTF_FAIL_IF_NEQ(deeperNumber.part(0), 1);
    ISHTF_PASS();
}
