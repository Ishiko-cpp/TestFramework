/*
    Copyright (c) 2015-2019 Xavier Leclercq

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

using namespace Ishiko::TestFramework;
using namespace boost::filesystem;

void AddFilesTeardownActionTests(TestSequence& parentTestSequence)
{
    TestSequence& testSequence = parentTestSequence.append<TestSequence>("FilesTeardownAction tests");

    testSequence.append<HeapAllocationErrorsTest>("Creation test 1", FilesTeardownActionCreationTest1);
    testSequence.append<HeapAllocationErrorsTest>("teardown() test 1", FilesTeardownActionTeardownTest1);
}

TestResult::EOutcome FilesTeardownActionCreationTest1()
{
    FilesTeardownAction action;
    return TestResult::ePassed;
}

TestResult::EOutcome FilesTeardownActionTeardownTest1Helper(Test& test)
{
    const char* path = "../../TestOutput/TestTeardownActionsTests/FilesTeardownActionTeardownTest1";
    std::shared_ptr<FilesTeardownAction> action = std::make_shared<FilesTeardownAction>();
    action->add(path);
    test.addTeardownAction(action);

    std::ofstream file(path);
    file.close();

    if (exists(path))
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome FilesTeardownActionTeardownTest1()
{
    const char* path = "../../TestOutput/TestTeardownActionsTests/FilesTeardownActionTeardownTest1";

    FunctionBasedTest test(TestNumber(), "FilesTeardownActionTeardownTest1", FilesTeardownActionTeardownTest1Helper);
    test.run();

    if (!exists(path) && test.passed())
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}
