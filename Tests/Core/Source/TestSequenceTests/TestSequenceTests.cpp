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

#include "TestSequenceTests.h"
#include "../TestClasses/SimpleTestClass1.h"

void TestSequenceTests::AddTests(Ishiko::TestFramework::TestHarness& theTestHarness)
{
    Ishiko::TestFramework::TestSequence& testSequenceTestSequence =
        theTestHarness.appendTestSequence("TestSequence tests");

    new Ishiko::TestFramework::HeapAllocationErrorsTest("Creation test 1", CreationTest1, testSequenceTestSequence);
    new Ishiko::TestFramework::HeapAllocationErrorsTest("append test 1", AppendTest1, testSequenceTestSequence);
    new Ishiko::TestFramework::HeapAllocationErrorsTest("append test 2", AppendTest2, testSequenceTestSequence);
    new Ishiko::TestFramework::HeapAllocationErrorsTest("getResult test 1", GetResultTest1, testSequenceTestSequence);
    new Ishiko::TestFramework::HeapAllocationErrorsTest("getResult test 2", GetResultTest2, testSequenceTestSequence);
    new Ishiko::TestFramework::HeapAllocationErrorsTest("getResult test 3", GetResultTest3, testSequenceTestSequence);
}

Ishiko::TestFramework::TestResult::EOutcome TestSequenceTests::CreationTest1()
{
    Ishiko::TestFramework::TestSequence seq(Ishiko::TestFramework::TestNumber(1), "Sequence");
    return Ishiko::TestFramework::TestResult::ePassed;
}

Ishiko::TestFramework::TestResult::EOutcome TestSequenceTests::AppendTest1()
{
    // Creating test sequence
    Ishiko::TestFramework::TestSequence seq(Ishiko::TestFramework::TestNumber(1), "Sequence");

    // Creating test
    std::shared_ptr<Ishiko::TestFramework::Test> test = std::make_shared<SimpleTestClass1>(
        Ishiko::TestFramework::TestNumber(1), "Test", Ishiko::TestFramework::TestResult::ePassed);

    // Append test to sequence
    seq.append(test);

    // Check the test count
    if (seq.size() == 1)
    {
        return Ishiko::TestFramework::TestResult::ePassed;
    }
    else
    {
        return Ishiko::TestFramework::TestResult::eFailed;
    }
}

Ishiko::TestFramework::TestResult::EOutcome TestSequenceTests::AppendTest2()
{
    // Creating test sequence
    Ishiko::TestFramework::TestSequence seq(Ishiko::TestFramework::TestNumber(1), "Sequence");

    // Create and append a test to the sequence in one go using the templated append function
    seq.append<SimpleTestClass1>("Test", Ishiko::TestFramework::TestResult::ePassed);

    // Check the test count
    if (seq.size() == 1)
    {
        return Ishiko::TestFramework::TestResult::ePassed;
    }
    else
    {
        return Ishiko::TestFramework::TestResult::eFailed;
    }
}

Ishiko::TestFramework::TestResult::EOutcome TestSequenceTests::GetResultTest1()
{
    Ishiko::TestFramework::TestSequence seq(Ishiko::TestFramework::TestNumber(1), "Sequence");

    if (seq.result().outcome() == Ishiko::TestFramework::TestResult::eUnknown)
    {
        return Ishiko::TestFramework::TestResult::ePassed;
    }
    else
    {
        return Ishiko::TestFramework::TestResult::eFailed;
    }
}

Ishiko::TestFramework::TestResult::EOutcome TestSequenceTests::GetResultTest2()
{
    // Creating test sequence
    Ishiko::TestFramework::TestSequence seq(Ishiko::TestFramework::TestNumber(1), "Sequence");

    // Creating test
    std::shared_ptr<Ishiko::TestFramework::Test> test = std::make_shared<SimpleTestClass1>(
        Ishiko::TestFramework::TestNumber(1), "Test", Ishiko::TestFramework::TestResult::ePassed);

    // Append test to sequence
    seq.append(test);

    // Run the sequence to update the test result
    seq.run();

    if (seq.result().outcome() == Ishiko::TestFramework::TestResult::ePassed)
    {
        return Ishiko::TestFramework::TestResult::ePassed;
    }
    else
    {
        return Ishiko::TestFramework::TestResult::eFailed;
    }
}

Ishiko::TestFramework::TestResult::EOutcome TestSequenceTests::GetResultTest3()
{
    // Creating test sequence
    Ishiko::TestFramework::TestSequence seq(Ishiko::TestFramework::TestNumber(1), "Sequence");

    // Creating first test (passes)
    std::shared_ptr<Ishiko::TestFramework::Test> test1 = std::make_shared<SimpleTestClass1>(
        Ishiko::TestFramework::TestNumber(1), "Test", Ishiko::TestFramework::TestResult::ePassed);
    seq.append(test1);

    // Creating second test (fails)
    std::shared_ptr<Ishiko::TestFramework::Test> test2 = std::make_shared<SimpleTestClass1>(
        Ishiko::TestFramework::TestNumber(1), "Test", Ishiko::TestFramework::TestResult::eFailed);
    seq.append(test2);

    // Run the sequence to update the test result
    seq.run();

    if (seq.result().outcome() == Ishiko::TestFramework::TestResult::eFailed)
    {
        return Ishiko::TestFramework::TestResult::ePassed;
    }
    else
    {
        return Ishiko::TestFramework::TestResult::eFailed;
    }
}
