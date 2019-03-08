/*
    Copyright (c) 2007-2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "TestTests.h"

using namespace Ishiko::Tests;

TestTests::TestTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Test tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("Creation test 2", CreationTest2);
    append<HeapAllocationErrorsTest>("Creation test 3", CreationTest3);
    append<HeapAllocationErrorsTest>("Creation test 4", CreationTest4);
    append<HeapAllocationErrorsTest>("Creation test 5", CreationTest5);
    append<HeapAllocationErrorsTest>("pass test 1", PassTest1);
    append<HeapAllocationErrorsTest>("fail test 1", FailTest1);
    append<HeapAllocationErrorsTest>("run test 1", RunTest1);
    append<HeapAllocationErrorsTest>("run test 2", RunTest2);
    append<HeapAllocationErrorsTest>("run test 3", RunTest3);
    append<HeapAllocationErrorsTest>("run test 4", RunTest4);
}

void TestTests::CreationTest1(Test& test)
{
    Test myTest(TestNumber(1), "TestCreationTest1");
    ISHTF_PASS();
}

void TestTests::CreationTest2(Test& test)
{
    Test myTest(TestNumber(1), "TestCreationTest2", TestResult::ePassed);
    ISHTF_PASS();
}

void TestCreationTest3Helper(Test& test)
{
    test.pass();
}

void TestTests::CreationTest3(Test& test)
{
    Test myTest(TestNumber(), "TestCreationTest3", TestCreationTest3Helper);
    ISHTF_PASS();
}

void TestTests::CreationTest4(Test& test)
{
    Test myTest(TestNumber(), "TestCreationTest4", [](Test& test) {});
    ISHTF_PASS();
}

void TestTests::CreationTest5(Test& test)
{
    int data = 5;
    Test myTest(TestNumber(), "TestCreationTest4", [data](Test& test) {});
    ISHTF_PASS();
}

void TestTests::PassTest1(Test& test)
{
    Test myTest(TestNumber(1), "PassTest1");
    myTest.pass();

    ISHTF_FAIL_UNLESS(myTest.result() == TestResult::ePassed);
    ISHTF_PASS();
}

void TestTests::FailTest1(Test& test)
{
    Test myTest(TestNumber(1), "FailTest1");
    myTest.fail(__FILE__, __LINE__);

    ISHTF_FAIL_UNLESS(myTest.result() == TestResult::eFailed);
    ISHTF_PASS();
}

void TestTests::RunTest1(Test& test)
{
    Test myTest(TestNumber(1), "TestRunTest1");
    myTest.run();

    ISHTF_FAIL_UNLESS(myTest.result() == TestResult::eFailed);
    ISHTF_PASS();
}

void TestTests::RunTest2(Test& test)
{
    Test myTest(TestNumber(1), "TestRunTest2", TestResult::ePassed);
    myTest.run();

    ISHTF_FAIL_UNLESS(myTest.result() == TestResult::ePassed);
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

    ISHTF_FAIL_UNLESS(myTest.result() == TestResult::ePassed);
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

    ISHTF_FAIL_UNLESS(myTest.result() == TestResult::eFailed);
    ISHTF_PASS();
}
