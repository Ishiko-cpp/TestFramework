/*
    Copyright (c) 2007-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "TestHarnessTests.h"
#include "Ishiko/Tests/Core/TestHarness.hpp"

using namespace Ishiko;

TestHarnessTests::TestHarnessTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "TestHarness tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("run test 1", RunTest1);
    append<HeapAllocationErrorsTest>("run test 2", RunTest2);
    append<HeapAllocationErrorsTest>("run test 3", RunTest3);
}

void TestHarnessTests::CreationTest1(Test& test)
{
    TestHarness theTestHarness("TestHarnessTests_CreationTest1");

    ISHIKO_TEST_PASS();
}

void TestHarnessTests::RunTest1(Test& test)
{
    TestHarness theTestHarness("TestHarnessTests_RunTest1");
    int returnCode = theTestHarness.run();

    ISHIKO_TEST_FAIL_IF_NEQ(returnCode, eTestFailure);
    ISHIKO_TEST_PASS();
}

void TestHarnessTests::RunTest2(Test& test)
{
    TestHarness theTestHarness("TestHarnessTests_RunTest2");

    std::shared_ptr<Test> test1 = std::make_shared<Test>(TestNumber(1), "Test", TestResult::passed);
    theTestHarness.tests().append(test1);

    int returnCode = theTestHarness.run();

    ISHIKO_TEST_FAIL_IF_NEQ(returnCode, eOK);
    ISHIKO_TEST_PASS();
}

void TestHarnessTests::RunTest3(Test& test)
{
    TestHarness theTestHarness("TestHarnessTests_RunTest3");

    std::shared_ptr<Test> test1 = std::make_shared<Test>(TestNumber(1), "Test", TestResult::skipped);
    theTestHarness.tests().append(test1);

    int returnCode = theTestHarness.run();

    ISHIKO_TEST_FAIL_IF_NEQ(returnCode, eOK);
    ISHIKO_TEST_PASS();
}
