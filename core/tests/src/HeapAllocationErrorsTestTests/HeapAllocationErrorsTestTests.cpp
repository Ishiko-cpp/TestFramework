/*
    Copyright (c) 2007-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "HeapAllocationErrorsTestTests.h"

using namespace Ishiko;

HeapAllocationErrorsTestTests::HeapAllocationErrorsTestTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "HeapAllocationErrorsTest tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
}

void HeapAllocationErrorsTestCreationTest1Helper(Test& test)
{
    test.pass();
}

void HeapAllocationErrorsTestTests::CreationTest1(Test& test)
{
    HeapAllocationErrorsTest allocTest(TestNumber(), "HeapAllocationErrorsTestCreationTest1",
        HeapAllocationErrorsTestCreationTest1Helper);

    ISHIKO_TEST_PASS();
}
