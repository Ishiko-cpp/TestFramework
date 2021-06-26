/*
    Copyright (c) 2019-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "TestMacrosTests.h"
#include "Ishiko/Tests/Core/TestProgressObserver.h"
#include <Ishiko/Text.h>
#include <sstream>

using namespace Ishiko::Tests;
using namespace Ishiko::Text;

TestMacrosTests::TestMacrosTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Test macros tests", environment)
{
    append<HeapAllocationErrorsTest>("ISHTF_PASS test 1", PassMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL test 1", FailMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL_IF test 1", FailIfMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL_IF test 2", FailIfMacroTest2);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL_IF_NOT test 1", FailIfNotMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL_IF_NOT test 2", FailIfNotMacroTest2);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL_IF_EQ test 1", FailIfEqMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL_IF_EQ test 2", FailIfEqMacroTest2);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL_IF_NEQ test 1", FailIfNeqMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL_IF_NEQ test 2", FailIfNeqMacroTest2);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL_IF_STR_EQ test 1", FailIfStrEqMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL_IF_STR_EQ test 2", FailIfStrEqMacroTest2);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL_IF_STR_NEQ test 1", FailIfStrNeqMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL_IF_STR_NEQ test 2", FailIfStrNeqMacroTest2);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL_IF_NOT_CONTAIN test 1", FailIfNotContainMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_FAIL_IF_NOT_CONTAIN test 2", FailIfNotContainMacroTest2);
    append<HeapAllocationErrorsTest>("ISHTF_ABORT test 1", AbortMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_ABORT_IF test 1", AbortIfMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_ABORT_IF test 2", AbortIfMacroTest2);
    append<HeapAllocationErrorsTest>("ISHTF_ABORT_IF_NOT test 1", AbortIfNotMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_ABORT_IF_NOT test 2", AbortIfNotMacroTest2);
    append<HeapAllocationErrorsTest>("ISHTF_ABORT_IF_EQ test 1", AbortIfEqMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_ABORT_IF_EQ test 2", AbortIfEqMacroTest2);
    append<HeapAllocationErrorsTest>("ISHTF_ABORT_IF_NEQ test 1", AbortIfNeqMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_ABORT_IF_NEQ test 2", AbortIfNeqMacroTest2);
    append<HeapAllocationErrorsTest>("ISHTF_ABORT_IF_STR_EQ test 1", AbortIfStrEqMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_ABORT_IF_STR_EQ test 2", AbortIfStrEqMacroTest2);
    append<HeapAllocationErrorsTest>("ISHTF_ABORT_IF_STR_NEQ test 1", AbortIfStrNeqMacroTest1);
    append<HeapAllocationErrorsTest>("ISHTF_ABORT_IF_STR_NEQ test 2", AbortIfStrNeqMacroTest2);
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

    std::stringstream progressOutput;
    std::shared_ptr<TestProgressObserver> observer = std::make_shared<TestProgressObserver>(progressOutput);
    myTest.observers().add(observer);

    myTest.run();

    std::vector<std::string> progressOutputLines = ASCII::GetLines(progressOutput.str());

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eFailed);
    ISHTF_ABORT_IF_NEQ(progressOutputLines.size(), 3);
    ISHTF_FAIL_IF_NOT_CONTAIN(progressOutputLines[1], "ISHTF_FAIL_IF(true) failed with actual value (true)");
    ISHTF_FAIL_IF_NOT(canary);
    ISHTF_PASS();
}

void TestMacrosTests::FailIfNotMacroTest1(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "FailIfNotMacroTest1",
        [&canary](Test& test)
    {
        ISHTF_FAIL_IF_NOT(true);

        canary = true;

        ISHTF_PASS();
    });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::ePassed);
    ISHTF_FAIL_IF_NOT(canary);
    ISHTF_PASS();
}

void TestMacrosTests::FailIfNotMacroTest2(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "FailIfNotMacroTest2",
        [&canary](Test& test)
    {
        ISHTF_FAIL_IF_NOT(false);

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

void TestMacrosTests::FailIfStrEqMacroTest1(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "FailIfStrEqMacroTest1",
        [&canary](Test& test)
    {
        ISHTF_FAIL_IF_STR_EQ("a", "b");

        canary = true;

        ISHTF_PASS();
    });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::ePassed);
    ISHTF_FAIL_IF_NOT(canary);
    ISHTF_PASS();
}

void TestMacrosTests::FailIfStrEqMacroTest2(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "FailIfStrEqMacroTest2",
        [&canary](Test& test)
    {
        ISHTF_FAIL_IF_STR_EQ("a", "a");

        canary = true;

        ISHTF_PASS();
    });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eFailed);
    ISHTF_FAIL_IF_NOT(canary);
    ISHTF_PASS();
}

void TestMacrosTests::FailIfStrNeqMacroTest1(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "FailIfStrNeqMacroTest1",
        [&canary](Test& test)
    {
        ISHTF_FAIL_IF_STR_NEQ("a", "a");

        canary = true;

        ISHTF_PASS();
    });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::ePassed);
    ISHTF_FAIL_IF_NOT(canary);
    ISHTF_PASS();
}

void TestMacrosTests::FailIfStrNeqMacroTest2(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "FailIfStrNeqMacroTest2",
        [&canary](Test& test)
    {
        ISHTF_FAIL_IF_STR_NEQ("a", "b");

        canary = true;

        ISHTF_PASS();
    });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eFailed);
    ISHTF_FAIL_IF_NOT(canary);
    ISHTF_PASS();
}

void TestMacrosTests::FailIfNotContainMacroTest1(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "FailIfNotContainMacroTest1",
        [&canary](Test& test)
    {
        ISHTF_FAIL_IF_NOT_CONTAIN("abc", "b");

        canary = true;

        ISHTF_PASS();
    });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::ePassed);
    ISHTF_FAIL_IF_NOT(canary);
    ISHTF_PASS();
}

void TestMacrosTests::FailIfNotContainMacroTest2(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "FailIfNotContainMacroTest2",
        [&canary](Test& test)
    {
        ISHTF_FAIL_IF_NOT_CONTAIN("abc", "d");

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

void TestMacrosTests::AbortIfNotMacroTest1(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "AbortIfNotMacroTest1",
        [&canary](Test& test)
    {
        ISHTF_ABORT_IF_NOT(true);

        canary = true;

        ISHTF_PASS();
    });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::ePassed);
    ISHTF_FAIL_IF_NOT(canary);
    ISHTF_PASS();
}

void TestMacrosTests::AbortIfNotMacroTest2(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "AbortIfNotMacroTest2",
        [&canary](Test& test)
    {
        ISHTF_ABORT_IF_NOT(false);

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

void TestMacrosTests::AbortIfStrEqMacroTest1(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "AbortIfStrEqMacroTest1",
        [&canary](Test& test)
    {
        ISHTF_ABORT_IF_STR_EQ("a", "b");

        canary = true;

        ISHTF_PASS();
    });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::ePassed);
    ISHTF_FAIL_IF_NOT(canary);
    ISHTF_PASS();
}

void TestMacrosTests::AbortIfStrEqMacroTest2(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "AbortIfStrEqMacroTest2",
        [&canary](Test& test)
    {
        ISHTF_ABORT_IF_STR_EQ("a", "a");

        canary = true;

        ISHTF_PASS();
    });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eFailed);
    ISHTF_FAIL_IF(canary);
    ISHTF_PASS();
}

void TestMacrosTests::AbortIfStrNeqMacroTest1(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "AbortIfStrNeqMacroTest1",
        [&canary](Test& test)
    {
        ISHTF_ABORT_IF_STR_NEQ("a", "a");

        canary = true;

        ISHTF_PASS();
    });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::ePassed);
    ISHTF_FAIL_IF_NOT(canary);
    ISHTF_PASS();
}

void TestMacrosTests::AbortIfStrNeqMacroTest2(Test& test)
{
    bool canary = false;
    Test myTest(TestNumber(), "AbortIfStrNeqMacroTest2",
        [&canary](Test& test)
    {
        ISHTF_ABORT_IF_STR_NEQ("a", "b");

        canary = true;

        ISHTF_PASS();
    });
    myTest.run();

    ISHTF_FAIL_IF_NEQ(myTest.result(), TestResult::eFailed);
    ISHTF_FAIL_IF(canary);
    ISHTF_PASS();
}
