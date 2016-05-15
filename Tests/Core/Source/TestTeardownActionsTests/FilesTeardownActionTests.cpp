/*
	Copyright (c) 2015 Xavier Leclercq

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

#include "FilesTeardownActionTests.h"
#include <boost/filesystem.hpp>

void AddFilesTeardownActionTests(Ishiko::TestFramework::TestSequence& testSequence)
{
	Ishiko::TestFramework::TestSequence* filesTeardownTestSequence =
		new Ishiko::TestFramework::TestSequence("FileesTeardownAction tests", testSequence);

	new Ishiko::TestFramework::HeapAllocationErrorsTest("Creation test 1",
		FilesTeardownActionCreationTest1, *filesTeardownTestSequence);

	new Ishiko::TestFramework::HeapAllocationErrorsTest("run test 1",
		FilesTeardownActionRunTest1, *filesTeardownTestSequence);
}

Ishiko::TestFramework::TestResult::EOutcome FilesTeardownActionCreationTest1()
{
	Ishiko::TestFramework::FilesTeardownAction action;
	return Ishiko::TestFramework::TestResult::ePassed;
}

Ishiko::TestFramework::TestResult::EOutcome FilesTeardownActionRunTest1Helper(Ishiko::TestFramework::Test& test)
{
	const char* path = "../../TestOutput/TestTeardownActionsTests/FilesTeardownActionRunTest1";
	std::shared_ptr<Ishiko::TestFramework::FilesTeardownAction> action =
		std::make_shared<Ishiko::TestFramework::FilesTeardownAction>();
	action->add(path);
	test.addTeardownAction(action);

	std::ofstream file(path);
	file.close();

	if (boost::filesystem::exists(path))
	{
		return Ishiko::TestFramework::TestResult::ePassed;
	}
	else
	{
		return Ishiko::TestFramework::TestResult::eFailed;
	}
}

Ishiko::TestFramework::TestResult::EOutcome FilesTeardownActionRunTest1()
{
	const char* path = "../../TestOutput/TestTeardownActionsTests/FilesTeardownActionRunTest1";

	Ishiko::TestFramework::FunctionBasedTest test(Ishiko::TestFramework::TestNumber(),
		"FilesTeardownActionRunTest1", FilesTeardownActionRunTest1Helper);
	test.run();

	if (!boost::filesystem::exists(path) && test.passed())
	{
		return Ishiko::TestFramework::TestResult::ePassed;
	}
	else
	{
		return Ishiko::TestFramework::TestResult::eFailed;
	}
}
