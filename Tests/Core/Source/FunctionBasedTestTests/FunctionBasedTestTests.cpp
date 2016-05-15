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

#include "FunctionBasedTestTests.h"

void AddFunctionBasedTestTests(Ishiko::TestFramework::TestHarness& theTestHarness)
{
	Ishiko::TestFramework::TestSequence& functionBasedTestSequence =
		theTestHarness.appendTestSequence("FunctionBasedTest tests");

	new Ishiko::TestFramework::HeapAllocationErrorsTest("Creation test 1",
		FunctionBasedTestCreationTest1, functionBasedTestSequence);
	new Ishiko::TestFramework::HeapAllocationErrorsTest("Creation test 2",
		FunctionBasedTestCreationTest2, functionBasedTestSequence);

	new Ishiko::TestFramework::HeapAllocationErrorsTest("run success test 1",
		FunctionBasedTestRunSuccessTest1, functionBasedTestSequence);
	new Ishiko::TestFramework::HeapAllocationErrorsTest("run success test 2",
		FunctionBasedTestRunSuccessTest2, functionBasedTestSequence);

	new Ishiko::TestFramework::HeapAllocationErrorsTest("run failure test 1",
		FunctionBasedTestRunFailureTest1, functionBasedTestSequence);
	new Ishiko::TestFramework::HeapAllocationErrorsTest("run failure test 2",
		FunctionBasedTestRunFailureTest2, functionBasedTestSequence);
}

Ishiko::TestFramework::TestResult::EOutcome FunctionBasedTestCreationTest1Helper()
{
	return Ishiko::TestFramework::TestResult::ePassed;
}

Ishiko::TestFramework::TestResult::EOutcome FunctionBasedTestCreationTest1()
{
	Ishiko::TestFramework::FunctionBasedTest test(Ishiko::TestFramework::TestNumber(), 
		"FunctionBasedTestCreationTest1", FunctionBasedTestCreationTest1Helper);
	return Ishiko::TestFramework::TestResult::ePassed;
}

Ishiko::TestFramework::TestResult::EOutcome FunctionBasedTestCreationTest2Helper(Ishiko::TestFramework::Test& test)
{
	return Ishiko::TestFramework::TestResult::ePassed;
}

Ishiko::TestFramework::TestResult::EOutcome FunctionBasedTestCreationTest2()
{
	Ishiko::TestFramework::FunctionBasedTest test(Ishiko::TestFramework::TestNumber(),
		"FunctionBasedTestCreationTest2", FunctionBasedTestCreationTest2Helper);
	return Ishiko::TestFramework::TestResult::ePassed;
}

Ishiko::TestFramework::TestResult::EOutcome FunctionBasedTestRunSuccessTest1Helper()
{
	return Ishiko::TestFramework::TestResult::ePassed;
}

Ishiko::TestFramework::TestResult::EOutcome FunctionBasedTestRunSuccessTest1()
{
	Ishiko::TestFramework::FunctionBasedTest test(Ishiko::TestFramework::TestNumber(),
		"FunctionBasedTestRunSuccessTest1", FunctionBasedTestRunSuccessTest1Helper);
	test.run();

	if (test.result().outcome() == Ishiko::TestFramework::TestResult::ePassed)
	{
		return Ishiko::TestFramework::TestResult::ePassed;
	}
	else
	{
		return Ishiko::TestFramework::TestResult::eFailed;
	}
}

Ishiko::TestFramework::TestResult::EOutcome FunctionBasedTestRunSuccessTest2Helper(Ishiko::TestFramework::Test& test)
{
	if (test.name() == "FunctionBasedTestRunSuccessTest2")
	{
		return Ishiko::TestFramework::TestResult::ePassed;
	}
	else
	{
		return Ishiko::TestFramework::TestResult::eFailed;
	}
}

Ishiko::TestFramework::TestResult::EOutcome FunctionBasedTestRunSuccessTest2()
{
	Ishiko::TestFramework::FunctionBasedTest test(Ishiko::TestFramework::TestNumber(),
		"FunctionBasedTestRunSuccessTest2", FunctionBasedTestRunSuccessTest2Helper);
	test.run();

	if (test.result().outcome() == Ishiko::TestFramework::TestResult::ePassed)
	{
		return Ishiko::TestFramework::TestResult::ePassed;
	}
	else
	{
		return Ishiko::TestFramework::TestResult::eFailed;
	}
}

Ishiko::TestFramework::TestResult::EOutcome FunctionBasedTestRunFailureTest1Helper()
{
	return Ishiko::TestFramework::TestResult::eFailed;
}

Ishiko::TestFramework::TestResult::EOutcome FunctionBasedTestRunFailureTest1()
{
	Ishiko::TestFramework::FunctionBasedTest test(Ishiko::TestFramework::TestNumber(),
		"FunctionBasedTestRunFailureTest1", FunctionBasedTestRunFailureTest1Helper);
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

Ishiko::TestFramework::TestResult::EOutcome FunctionBasedTestRunFailureTest2Helper(Ishiko::TestFramework::Test& test)
{
	if (test.name() != "FunctionBasedTestRunFailureTest2")
	{
		return Ishiko::TestFramework::TestResult::ePassed;
	}
	else
	{
		return Ishiko::TestFramework::TestResult::eFailed;
	}
}

Ishiko::TestFramework::TestResult::EOutcome FunctionBasedTestRunFailureTest2()
{
	Ishiko::TestFramework::FunctionBasedTest test(Ishiko::TestFramework::TestNumber(),
		"FunctionBasedTestRunFailureTest2", FunctionBasedTestRunFailureTest2Helper);
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
