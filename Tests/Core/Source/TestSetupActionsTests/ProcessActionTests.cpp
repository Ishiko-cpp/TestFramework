/*
	Copyright (c) 2016 Xavier Leclercq

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

#include "ProcessActionTests.h"
#include "Ishiko/TestFramework/Core/ProcessAction.h"
#include <boost/filesystem/operations.hpp>

void AddProcessActionTests(Ishiko::TestFramework::TestSequence& testSequence)
{
    Ishiko::TestFramework::TestSequence* processActionTestSequence =
        new Ishiko::TestFramework::TestSequence("ProcessAction tests", testSequence);

    new Ishiko::TestFramework::HeapAllocationErrorsTest("Creation test 1",
        ProcessActionCreationTest1, *processActionTestSequence);
    new Ishiko::TestFramework::FileComparisonTest("setup() test 1",
        ProcessActionSetupTest1, *processActionTestSequence);
}

Ishiko::TestFramework::TestResult::EOutcome ProcessActionCreationTest1()
{
    Ishiko::TestFramework::ProcessAction action("../../TestData/Binaries/WriteFileTestHelper.exe");
    return Ishiko::TestFramework::TestResult::ePassed;
}

Ishiko::TestFramework::TestResult::EOutcome ProcessActionSetupTest1(Ishiko::TestFramework::FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "TestSetupActionsTests/ProcessActionSetupTest1.txt");
    test.setOutputFilePath(outputPath);
    boost::filesystem::create_directories(test.environment().getTestOutputDirectory() / "TestSetupActionsTests");
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "TestSetupActionsTests/ProcessActionSetupTest1.txt");

    Ishiko::TestFramework::ProcessAction action("../../TestData/Binaries/WriteFileTestHelper.exe " + outputPath.generic_string());
    action.setup();
    action.teardown();
    return Ishiko::TestFramework::TestResult::ePassed;
}
