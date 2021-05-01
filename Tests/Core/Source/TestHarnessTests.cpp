/*
    Copyright (c) 2007-2019 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#include "TestHarnessTests.h"
#include "Ishiko/TestFramework/Core/TestHarness.h"

using namespace Ishiko::Tests;

TestHarnessTests::TestHarnessTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "TestHarness tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("run test 1", RunTest1);
}

void TestHarnessTests::CreationTest1(Test& test)
{
    TestHarness theTestHarness("TestHarnessTests_CreationTest1");
    ISHTF_PASS();
}

void TestHarnessTests::RunTest1(Test& test)
{
    TestHarness theTestHarness("TestHarnessTests_RunTest1");
    int returnCode = theTestHarness.run();

    ISHTF_FAIL_IF_NEQ(returnCode, eTestFailure);
    ISHTF_PASS();
}
