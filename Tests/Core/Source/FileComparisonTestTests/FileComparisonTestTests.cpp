/*
	Copyright (c) 2007-2015 Xavier Leclercq

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

#include "FileComparisonTestTests.h"

void AddFileComparisonTestTests(Ishiko::TestFramework::TestHarness& theTestHarness)
{
	Ishiko::TestFramework::TestSequence& fileComparisonTestSequence =
		theTestHarness.appendTestSequence("FileComparisonTest tests");

	new Ishiko::TestFramework::HeapAllocationErrorsTest("Creation test 1",
		FileComparisonTestCreationTest1, fileComparisonTestSequence);

	new Ishiko::TestFramework::HeapAllocationErrorsTest("run success test 1",
		FileComparisonTestRunSuccessTest1, fileComparisonTestSequence);

	new Ishiko::TestFramework::HeapAllocationErrorsTest("run failure test 1",
		FileComparisonTestRunFailureTest1, fileComparisonTestSequence);
}

Ishiko::TestFramework::TestResult::EOutcome FileComparisonTestCreationTest1Helper(Ishiko::TestFramework::FileComparisonTest& test)
{
	return Ishiko::TestFramework::TestResult::ePassed;
}

Ishiko::TestFramework::TestResult::EOutcome FileComparisonTestCreationTest1()
{
	Ishiko::TestFramework::FileComparisonTest test(
		Ishiko::TestFramework::TestNumber(), "FileComparisonTestCreationTest1",
		FileComparisonTestCreationTest1Helper);
	return Ishiko::TestFramework::TestResult::ePassed;
}

Ishiko::TestFramework::TestResult::EOutcome FileComparisonTestRunSuccessTest1Helper(Ishiko::TestFramework::FileComparisonTest& test)
{
	test.setOutputFilePath("../../TestData/ComparisonTestFiles/Hello.txt");
	test.setReferenceFilePath("../../TestData/ComparisonTestFiles/Hello2.txt");
	return Ishiko::TestFramework::TestResult::ePassed;
}

Ishiko::TestFramework::TestResult::EOutcome FileComparisonTestRunSuccessTest1()
{
	Ishiko::TestFramework::FileComparisonTest test(
		Ishiko::TestFramework::TestNumber(), "FileComparisonTestRunSuccessTest1",
		FileComparisonTestRunSuccessTest1Helper);
	
	test.run();
	
	return test.result().outcome();
}

Ishiko::TestFramework::TestResult::EOutcome FileComparisonTestRunFailureTest1Helper(Ishiko::TestFramework::FileComparisonTest& test)
{
	test.setOutputFilePath("../../TestData/ComparisonTestFiles/Hello.txt");
	test.setReferenceFilePath("../../TestData/ComparisonTestFiles/NotHello.txt");
	return Ishiko::TestFramework::TestResult::ePassed;
}

Ishiko::TestFramework::TestResult::EOutcome FileComparisonTestRunFailureTest1()
{
	Ishiko::TestFramework::FileComparisonTest test(
		Ishiko::TestFramework::TestNumber(), "FileComparisonTestRunFailureTest1",
		FileComparisonTestRunFailureTest1Helper);

	test.run();
	
	if (test.result().outcome() == Ishiko::TestFramework::TestResult::eFailed)
	{
		return Ishiko::TestFramework::TestResult::ePassed;
	}
	else
	{
		return Ishiko::TestFramework::TestResult::eFailed;
	}
}
