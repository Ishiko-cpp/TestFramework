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
    append<HeapAllocationErrorsTest>("pass test 1", PassTest1);
    append<HeapAllocationErrorsTest>("fail test 1", FailTest1);
}

void TestTests::CreationTest1(Test& test)
{
    Test testClass(TestNumber(1), "TestCreationTest1");
    ISHTF_PASS();
}

void TestCreationTest2Helper(Test& test)
{
    test.pass();
}

void TestTests::CreationTest2(Test& test)
{
    Test functionTest(TestNumber(), "TestCreationTest2", TestCreationTest2Helper);
    ISHTF_PASS();
}

void TestTests::PassTest1(Test& test)
{
    Test testClass(TestNumber(1), "PassTest1");
    testClass.pass();

    ISHTF_FAIL_UNLESS(testClass.result() == TestResult::ePassed);
    ISHTF_PASS();
}

void TestTests::FailTest1(Test& test)
{
    Test testClass(TestNumber(1), "FailTest1");
    testClass.fail(__FILE__, __LINE__);

    ISHTF_FAIL_UNLESS(testClass.result() == TestResult::eFailed);
    ISHTF_PASS();
}
