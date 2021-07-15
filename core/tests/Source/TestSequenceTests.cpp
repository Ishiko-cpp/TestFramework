/*
    Copyright (c) 2007-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "TestSequenceTests.h"

using namespace Ishiko::Tests;

TestSequenceTests::TestSequenceTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "TestSequence tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("append test 1", AppendTest1);
    append<HeapAllocationErrorsTest>("append test 2", AppendTest2);
    append<HeapAllocationErrorsTest>("getResult test 1", GetResultTest1);
    append<HeapAllocationErrorsTest>("getResult test 2", GetResultTest2);
    append<HeapAllocationErrorsTest>("getResult test 3", GetResultTest3);
    append<HeapAllocationErrorsTest>("getResult test 4", GetResultTest4);
    append<HeapAllocationErrorsTest>("getResult test 5", GetResultTest5);
    append<HeapAllocationErrorsTest>("getResult test 6", GetResultTest6);
}

void TestSequenceTests::ConstructorTest1(Test& test)
{
    TestSequence seq(TestNumber(1), "Sequence");

    ISHTF_PASS();
}

void TestSequenceTests::AppendTest1(Test& test)
{
    // Creating test sequence
    TestSequence seq(TestNumber(1), "Sequence");

    // Creating test
    std::shared_ptr<Test> simpleTest = std::make_shared<Test>(TestNumber(1), "Test", TestResult::passed);

    // Append test to sequence
    seq.append(simpleTest);

    // Check the test sequence
    ISHTF_FAIL_IF_NEQ(seq.size(), 1);
    ISHTF_FAIL_IF_NEQ(seq[0].name(), "Test");
    ISHTF_FAIL_IF_NEQ(simpleTest->number(), TestNumber(1, 1));
    ISHTF_PASS();
}

void TestSequenceTests::AppendTest2(Test& test)
{
    // Creating test sequence
    TestSequence seq(TestNumber(1), "Sequence");

    // Create and append a test to the sequence in one go using the templated append function
    seq.append<Test>("Test", TestResult::passed);

    // Check the test sequence
    ISHTF_FAIL_IF_NEQ(seq.size(), 1);
    ISHTF_FAIL_IF_NEQ(seq[0].name(), "Test");
    ISHTF_FAIL_IF_NEQ(seq[0].number(), TestNumber(1, 1));
    ISHTF_PASS();
}

void TestSequenceTests::GetResultTest1(Test& test)
{
    TestSequence seq(TestNumber(1), "Sequence");

    ISHTF_FAIL_IF_NEQ(seq.result(), TestResult::unknown);
    ISHTF_PASS();
}

void TestSequenceTests::GetResultTest2(Test& test)
{
    // Creating test sequence
    TestSequence seq(TestNumber(1), "Sequence");

    // Creating test
    std::shared_ptr<Test> simpleTest = std::make_shared<Test>(TestNumber(1), "Test", TestResult::passed);

    // Append test to sequence
    seq.append(simpleTest);

    // Run the sequence to update the test result
    seq.run();

    ISHTF_FAIL_IF_NEQ(seq.result(), TestResult::passed);
    ISHTF_PASS();
}

void TestSequenceTests::GetResultTest3(Test& test)
{
    // Creating test sequence
    TestSequence seq(TestNumber(1), "Sequence");

    // Creating first test (passes)
    std::shared_ptr<Test> test1 = std::make_shared<Test>(TestNumber(1), "Test", TestResult::passed);
    seq.append(test1);

    // Creating second test (fails)
    std::shared_ptr<Test> test2 = std::make_shared<Test>(TestNumber(1), "Test", TestResult::failed);
    seq.append(test2);

    // Run the sequence to update the test result
    seq.run();

    ISHTF_FAIL_IF_NEQ(seq.result(), TestResult::failed);
    ISHTF_PASS();
}

void TestSequenceTests::GetResultTest4(Test& test)
{
    // Creating test sequence
    TestSequence seq(TestNumber(1), "Sequence");

    // Creating first test (skipped)
    std::shared_ptr<Test> test1 = std::make_shared<Test>(TestNumber(1), "Test", TestResult::skipped);
    seq.append(test1);

    // Run the sequence to update the test result
    seq.run();

    ISHTF_FAIL_IF_NEQ(seq.result(), TestResult::skipped);
    ISHTF_PASS();
}

void TestSequenceTests::GetResultTest5(Test& test)
{
    // Creating test sequence
    TestSequence seq(TestNumber(1), "Sequence");

    // Creating first test (skipped)
    std::shared_ptr<Test> test1 = std::make_shared<Test>(TestNumber(1), "Test", TestResult::skipped);
    seq.append(test1);

    // Creating second test (fails)
    std::shared_ptr<Test> test2 = std::make_shared<Test>(TestNumber(2), "Test", TestResult::failed);
    seq.append(test2);

    // Run the sequence to update the test result
    seq.run();

    ISHTF_FAIL_IF_NEQ(seq.result(), TestResult::failed);
    ISHTF_PASS();
}

void TestSequenceTests::GetResultTest6(Test& test)
{
    // Creating test sequence
    TestSequence seq(TestNumber(1), "Sequence");

    // Creating first test (passed)
    std::shared_ptr<Test> test1 = std::make_shared<Test>(TestNumber(1), "Test", TestResult::passed);
    seq.append(test1);

    // Creating second test (skipped)
    std::shared_ptr<Test> test2 = std::make_shared<Test>(TestNumber(2), "Test", TestResult::skipped);
    seq.append(test2);

    // Run the sequence to update the test result
    seq.run();

    ISHTF_FAIL_IF_NEQ(seq.result(), TestResult::passed);
    ISHTF_PASS();
}
