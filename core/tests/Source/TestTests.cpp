/*
    Copyright (c) 2007-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#include "TestTests.h"

using namespace Ishiko::Tests;

TestTests::TestTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Test tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("Constructor test 3", ConstructorTest3);
    append<HeapAllocationErrorsTest>("Constructor test 4", ConstructorTest4);
    append<HeapAllocationErrorsTest>("Constructor test 5", ConstructorTest5);
    append<HeapAllocationErrorsTest>("pass test 1", PassTest1);
    append<HeapAllocationErrorsTest>("fail test 1", FailTest1);
    append<HeapAllocationErrorsTest>("fail test 2", FailTest2);
    append<HeapAllocationErrorsTest>("failIf test 1", FailIfTest1);
    append<HeapAllocationErrorsTest>("failIf test 2", FailIfTest2);
    append<HeapAllocationErrorsTest>("failIf test 3", FailIfTest3);
    append<HeapAllocationErrorsTest>("run test 1", RunTest1);
    append<HeapAllocationErrorsTest>("run test 2", RunTest2);
    append<HeapAllocationErrorsTest>("run test 3", RunTest3);
    append<HeapAllocationErrorsTest>("run test 4", RunTest4);
    append<HeapAllocationErrorsTest>("run test 5", RunTest5);
    append<HeapAllocationErrorsTest>("abort test 1", AbortTest1);
}

void TestTests::ConstructorTest1(Test& test)
{
    Test myTest(TestNumber(1), "TestConstructorTest1");

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eUnknown);
    ISHTF_PASS();
}

void TestTests::ConstructorTest2(Test& test)
{
    Test myTest(TestNumber(1), "TestConstructorTest2", TestResult::ePassed);

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::ePassed);
    ISHTF_PASS();
}

void TestConstructorTest3Helper(Test& test)
{
    test.pass();
}

void TestTests::ConstructorTest3(Test& test)
{
    Test myTest(TestNumber(), "TestConstructorTest3", TestConstructorTest3Helper);

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eUnknown);
    ISHTF_PASS();
}

void TestTests::ConstructorTest4(Test& test)
{
    Test myTest(TestNumber(), "TestConstructorTest4", [](Test& test) {});

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eUnknown);
    ISHTF_PASS();
}

void TestTests::ConstructorTest5(Test& test)
{
    int data = 5;
    Test myTest(TestNumber(), "TestConstructorTest5", [data](Test& test) {});

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eUnknown);
    ISHTF_PASS();
}

void TestTests::PassTest1(Test& test)
{
    Test myTest(TestNumber(1), "PassTest1");
    myTest.pass();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::ePassed);
    ISHTF_PASS();
}

void TestTests::FailTest1(Test& test)
{
    Test myTest(TestNumber(1), "FailTest1");
    myTest.fail(__FILE__, __LINE__);

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eFailed);
    ISHTF_PASS();
}

void TestTests::FailTest2(Test& test)
{
    Test myTest(TestNumber(1), "FailTest2");
    myTest.fail(__FILE__, __LINE__);
    myTest.pass();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eFailed);
    ISHTF_PASS();
}

void TestTests::FailIfTest1(Test& test)
{
    Test myTest(TestNumber(1), "FailIfTest1");
    myTest.failIf(true, __FILE__, __LINE__);
    myTest.pass();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eFailed);
    ISHTF_PASS();
}

void TestTests::FailIfTest2(Test& test)
{
    Test myTest(TestNumber(1), "FailIfTest2");
    myTest.failIf(false, __FILE__, __LINE__);
    myTest.pass();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::ePassed);
    ISHTF_PASS();
}

void TestTests::FailIfTest3(Test& test)
{
    Test myTest(TestNumber(1), "FailIfTest3");
    myTest.failIf(false, __FILE__, __LINE__);

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eUnknown);
    ISHTF_PASS();
}

void TestTests::RunTest1(Test& test)
{
    Test myTest(TestNumber(1), "TestRunTest1");
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eFailed);
    ISHTF_PASS();
}

void TestTests::RunTest2(Test& test)
{
    Test myTest(TestNumber(1), "TestRunTest2", TestResult::ePassed);
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::ePassed);
    ISHTF_PASS();
}

void TestRunTest3Helper(Test& test)
{
    if (test.name() == "TestRunTest3")
    {
        test.pass();
    }
}

void TestTests::RunTest3(Test& test)
{
    Test myTest(TestNumber(1), "TestRunTest3", TestRunTest3Helper);
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::ePassed);
    ISHTF_PASS();
}

void TestRunTest4Helper(Test& test)
{
    if (test.name() != "TestRunTest4")
    {
        test.pass();
    }
}

void TestTests::RunTest4(Test& test)
{
    Test myTest(TestNumber(1), "TestRunTest4", TestRunTest4Helper);
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eFailed);
    ISHTF_PASS();
}

void TestRunTest5Helper(Test& test)
{
    throw std::runtime_error("TestRunTest5Helper threw exception");
}

void TestTests::RunTest5(Test& test)
{
    Test myTest(TestNumber(1), "TestRunTest5", TestRunTest5Helper);
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eException);
    ISHTF_PASS();
}

void TestTests::AbortTest1(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(1), "TestAbortTest1",
        [&canary](Test& test)
        {
            test.abort(__FILE__, __LINE__);
            canary = true;
        });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eFailed);
    ISHTF_FAIL_IF(canary);
    ISHTF_PASS();
}
