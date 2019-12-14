/*
    Copyright (c) 2019 Xavier Leclercq

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

#include "TestMacrosTests.h"

using namespace Ishiko::Tests;

TestMacrosTests::TestMacrosTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Test macros tests", environment)
{
    append<HeapAllocationErrorsTest>("ISHTF_PASS test 1", PassMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL test 1", FailMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL_IF test 1", FailIfMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL_IF test 2", FailIfMacroTest2);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL_IF_EQ test 1", FailIfEqMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL_IF_EQ test 2", FailIfEqMacroTest2);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL_IF_NEQ test 1", FailIfNeqMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL_IF_NEQ test 2", FailIfNeqMacroTest2);
    append<HeapAllocationErrorsTest>("ISHTF_ABORT test 1", AbortMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_ABORT_IF test 1", AbortIfMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_ABORT_IF test 2", AbortIfMacroTest2);
    append<HeapAllocationErrorsTest>("ISHTF_ABORT_IF_EQ test 1", AbortIfEqMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_ABORT_IF_EQ test 2", AbortIfEqMacroTest2);
    append<HeapAllocationErrorsTest>("ISHTF_ABORT_IF_NEQ test 1", AbortIfNeqMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_ABORT_IF_NEQ test 2", AbortIfNeqMacroTest2);
}

void TestMacrosTests::PassMacroTest1(Test& test)
{
    Test myTest(TestNumber(), "PassMacroTest1",
        [](Test& test)
        {
            ISHTF_PASS();
        });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::ePassed);
    ISHTF_PASS();
}

void TestMacrosTests::FailMacroTest1(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "FailMacroTest1",
        [&canary](Test& test)
        {
            ISHTF_FAIL();

            canary = true;

            ISHTF_PASS();
        });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eFailed);
    ISHTF_FAIL_IF_NOT(canary);
    ISHTF_PASS();
}

void TestMacrosTests::FailIfMacroTest1(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "FailIfMacroTest1",
        [&canary](Test& test)
        {
            ISHTF_FAIL_IF(false);

            canary = true;

            ISHTF_PASS();
        });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::ePassed);
    ISHTF_FAIL_IF_NOT(canary);
    ISHTF_PASS();
}

void TestMacrosTests::FailIfMacroTest2(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "FailIfMacroTest2",
        [&canary](Test& test)
        {
            ISHTF_FAIL_IF(true);

            canary = true;

            ISHTF_PASS();
        });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eFailed);
    ISHTF_FAIL_IF_NOT(canary);
    ISHTF_PASS();
}

void TestMacrosTests::FailIfEqMacroTest1(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "FailIfEqMacroTest1",
        [&canary](Test& test)
    {
        ISHTF_FAIL_IF_EQ(0, 1);

        canary = true;

        ISHTF_PASS();
    });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::ePassed);
    ISHTF_FAIL_IF_NOT(canary);
    ISHTF_PASS();
}

void TestMacrosTests::FailIfEqMacroTest2(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "FailIfEqMacroTest2",
        [&canary](Test& test)
    {
        ISHTF_FAIL_IF_EQ(0, 0);

        canary = true;

        ISHTF_PASS();
    });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eFailed);
    ISHTF_FAIL_IF_NOT(canary);
    ISHTF_PASS();
}

void TestMacrosTests::FailIfNeqMacroTest1(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "FailIfNeqMacroTest1",
        [&canary](Test& test)
    {
        ISHTF_FAIL_IF_NEQ(0, 0);

        canary = true;

        ISHTF_PASS();
    });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::ePassed);
    ISHTF_FAIL_IF_NOT(canary);
    ISHTF_PASS();
}

void TestMacrosTests::FailIfNeqMacroTest2(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "FailIfNeqMacroTest2",
        [&canary](Test& test)
    {
        ISHTF_FAIL_IF_NEQ(0, 1);

        canary = true;

        ISHTF_PASS();
    });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eFailed);
    ISHTF_FAIL_IF_NOT(canary);
    ISHTF_PASS();
}

void TestMacrosTests::AbortMacroTest1(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "AbortMacroTest1",
        [&canary](Test& test)
        {
            ISHTF_ABORT();

            canary = true;

            ISHTF_PASS();
        });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eFailed);
    ISHTF_FAIL_IF(canary);
    ISHTF_PASS();
}

void TestMacrosTests::AbortIfMacroTest1(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "AbortIfMacroTest1",
        [&canary](Test& test)
        {
            ISHTF_ABORT_IF(false);

            canary = true;

            ISHTF_PASS();
        });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::ePassed);
    ISHTF_FAIL_IF_NOT(canary);
    ISHTF_PASS();
}

void TestMacrosTests::AbortIfMacroTest2(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "AbortIfMacroTest2",
        [&canary](Test& test)
        {
            ISHTF_ABORT_IF(true);

            canary = true;

            ISHTF_PASS();
        });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eFailed);
    ISHTF_FAIL_IF(canary);
    ISHTF_PASS();
}

void TestMacrosTests::AbortIfEqMacroTest1(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "AbortIfEqMacroTest1",
        [&canary](Test& test)
    {
        ISHTF_ABORT_IF_EQ(0, 1);

        canary = true;

        ISHTF_PASS();
    });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::ePassed);
    ISHTF_FAIL_IF_NOT(canary);
    ISHTF_PASS();
}

void TestMacrosTests::AbortIfEqMacroTest2(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "AbortIfEqMacroTest2",
        [&canary](Test& test)
    {
        ISHTF_ABORT_IF_EQ(0, 0);

        canary = true;

        ISHTF_PASS();
    });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eFailed);
    ISHTF_FAIL_IF(canary);
    ISHTF_PASS();
}

void TestMacrosTests::AbortIfNeqMacroTest1(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "AbortIfNeqMacroTest1",
        [&canary](Test& test)
    {
        ISHTF_ABORT_IF_NEQ(0, 0);

        canary = true;

        ISHTF_PASS();
    });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::ePassed);
    ISHTF_FAIL_IF_NOT(canary);
    ISHTF_PASS();
}

void TestMacrosTests::AbortIfNeqMacroTest2(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "AbortIfNeqMacroTest2",
        [&canary](Test& test)
    {
        ISHTF_ABORT_IF_NEQ(0, 1);

        canary = true;

        ISHTF_PASS();
    });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eFailed);
    ISHTF_FAIL_IF(canary);
    ISHTF_PASS();
}
