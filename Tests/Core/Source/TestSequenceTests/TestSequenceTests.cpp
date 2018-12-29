/*
	Copyright (c) 2007-2018 Xavier Leclercq

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
