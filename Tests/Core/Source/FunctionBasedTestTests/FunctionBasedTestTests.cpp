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

#include "FunctionBasedTestTests.h"

using namespace Ishiko::Tests;

FunctionBasedTestTests::FunctionBasedTestTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "FunctionBasedTest tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("Creation test 2", CreationTest2);
    append<HeapAllocationErrorsTest>("run success test 1", RunSuccessTest1);
    append<HeapAllocationErrorsTest>("run success test 2", RunSuccessTest2);
    append<HeapAllocationErrorsTest>("run failure test 1", RunFailureTest1);
    append<HeapAllocationErrorsTest>("run failure test 2", RunFailureTest2);
}

TestResult FunctionBasedTestCreationTest1Helper()
{
    return TestResult::ePassed;
}

TestResult FunctionBasedTestTests::CreationTest1()
{
    FunctionBasedTest test(TestNumber(), "FunctionBasedTestCreationTest1", FunctionBasedTestCreationTest1Helper);
    return TestResult::ePassed;
}

TestResult FunctionBasedTestCreationTest2Helper(Test& test)
{
    return TestResult::ePassed;
}

TestResult FunctionBasedTestTests::CreationTest2()
{
    FunctionBasedTest test(TestNumber(), "FunctionBasedTestCreationTest2", FunctionBasedTestCreationTest2Helper);
    return TestResult::ePassed;
}

TestResult FunctionBasedTestRunSuccessTest1Helper()
{
    return TestResult::ePassed;
}

TestResult FunctionBasedTestTests::RunSuccessTest1()
{
    FunctionBasedTest test(TestNumber(), "FunctionBasedTestRunSuccessTest1", FunctionBasedTestRunSuccessTest1Helper);
    test.run();

    if (test.result() == TestResult::ePassed)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult FunctionBasedTestRunSuccessTest2Helper(Test& test)
{
    if (test.name() == "FunctionBasedTestRunSuccessTest2")
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult FunctionBasedTestTests::RunSuccessTest2()
{
    FunctionBasedTest test(TestNumber(), "FunctionBasedTestRunSuccessTest2", FunctionBasedTestRunSuccessTest2Helper);
    test.run();

    if (test.result() == TestResult::ePassed)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult FunctionBasedTestRunFailureTest1Helper()
{
    return TestResult::eFailed;
}

TestResult FunctionBasedTestTests::RunFailureTest1()
{
    FunctionBasedTest test(TestNumber(), "FunctionBasedTestRunFailureTest1", FunctionBasedTestRunFailureTest1Helper);
    test.run();

    if (test.result() == TestResult::eFailed)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult FunctionBasedTestRunFailureTest2Helper(Test& test)
{
    if (test.name() != "FunctionBasedTestRunFailureTest2")
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult FunctionBasedTestTests::RunFailureTest2()
{
    FunctionBasedTest test(TestNumber(), "FunctionBasedTestRunFailureTest2", FunctionBasedTestRunFailureTest2Helper);
    test.run();

    if (test.result() == TestResult::eFailed)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}
