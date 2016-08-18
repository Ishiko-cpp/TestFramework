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

#include "TestEnvironmentTests.h"
#include "Ishiko/Process/Environment.h"

void AddTestEnvironmentTests(Ishiko::TestFramework::TestHarness& theTestHarness)
{
	Ishiko::TestFramework::TestSequence& environmentTestSequence =
		theTestHarness.appendTestSequence("TestEnvironment tests");

	new Ishiko::TestFramework::HeapAllocationErrorsTest("Creation test 1",
		TestEnvironmentCreationTest1, environmentTestSequence);

	new Ishiko::TestFramework::HeapAllocationErrorsTest("getTestDataDirectory test 1",
		TestEnvironmentGetTestDataDirectoryTest1, environmentTestSequence);
	new Ishiko::TestFramework::HeapAllocationErrorsTest("getTestDataDirectory test 2",
		TestEnvironmentGetTestDataDirectoryTest2, environmentTestSequence);
	new Ishiko::TestFramework::HeapAllocationErrorsTest("getTestDataDirectory test 3",
		TestEnvironmentGetTestDataDirectoryTest3, environmentTestSequence);
}

Ishiko::TestFramework::TestResult::EOutcome TestEnvironmentCreationTest1()
{
	Ishiko::TestFramework::TestEnvironment environment;
	return Ishiko::TestFramework::TestResult::ePassed;
}

Ishiko::TestFramework::TestResult::EOutcome TestEnvironmentGetTestDataDirectoryTest1()
{
	Ishiko::TestFramework::TestResult::EOutcome result = Ishiko::TestFramework::TestResult::eFailed;
	try
	{
		Ishiko::TestFramework::TestEnvironment environment;
		environment.getTestDataDirectory("dummy");
	}
	catch (const Ishiko::TestFramework::TestException& exception)
	{
		result = Ishiko::TestFramework::TestResult::ePassed;
	}
	return result;
}

Ishiko::TestFramework::TestResult::EOutcome TestEnvironmentGetTestDataDirectoryTest2()
{
	Ishiko::TestFramework::TestEnvironment environment;
	environment.setTestDataDirectory("id1", "path1");
	if (environment.getTestDataDirectory("id1") == "path1")
	{
		return Ishiko::TestFramework::TestResult::ePassed;
	}
	else
	{
		return Ishiko::TestFramework::TestResult::eFailed;
	}
}

Ishiko::TestFramework::TestResult::EOutcome TestEnvironmentGetTestDataDirectoryTest3()
{
	Ishiko::Process::Environment::set("TestEnvironmentGetTestDataDirectoryTest3", "dummy");

	Ishiko::TestFramework::TestEnvironment environment;
	environment.setTestDataDirectory("id1", "$(TestEnvironmentGetTestDataDirectoryTest3)/path1");
	if (environment.getTestDataDirectory("id1") == "dummy/path1")
	{
		return Ishiko::TestFramework::TestResult::ePassed;
	}
	else
	{
		return Ishiko::TestFramework::TestResult::eFailed;
	}
}
