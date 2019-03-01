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

#include "FileComparisonTestTests.h"

using namespace Ishiko::TestFramework;

void AddFileComparisonTestTests(TestHarness& theTestHarness)
{
    TestSequence& testSequence = theTestHarness.appendTestSequence("FileComparisonTest tests");

    testSequence.append<HeapAllocationErrorsTest>("Creation test 1", FileComparisonTestCreationTest1);
    testSequence.append<HeapAllocationErrorsTest>("run success test 1", FileComparisonTestRunSuccessTest1);
    testSequence.append<HeapAllocationErrorsTest>("run failure test 1", FileComparisonTestRunFailureTest1);
}

TestResult::EOutcome FileComparisonTestCreationTest1Helper(FileComparisonTest& test)
{
    return TestResult::ePassed;
}

TestResult::EOutcome FileComparisonTestCreationTest1()
{
    FileComparisonTest test(TestNumber(), "FileComparisonTestCreationTest1", FileComparisonTestCreationTest1Helper);
    return TestResult::ePassed;
}

TestResult::EOutcome FileComparisonTestRunSuccessTest1Helper(FileComparisonTest& test)
{
    test.setOutputFilePath("../../TestData/ComparisonTestFiles/Hello.txt");
    test.setReferenceFilePath("../../TestData/ComparisonTestFiles/Hello2.txt");
    return TestResult::ePassed;
}

TestResult::EOutcome FileComparisonTestRunSuccessTest1()
{
    FileComparisonTest test(TestNumber(), "FileComparisonTestRunSuccessTest1",
        FileComparisonTestRunSuccessTest1Helper);
    
    test.run();
    
    return test.result().outcome();
}

TestResult::EOutcome FileComparisonTestRunFailureTest1Helper(FileComparisonTest& test)
{
    test.setOutputFilePath("../../TestData/ComparisonTestFiles/Hello.txt");
    test.setReferenceFilePath("../../TestData/ComparisonTestFiles/NotHello.txt");
    return TestResult::ePassed;
}

TestResult::EOutcome FileComparisonTestRunFailureTest1()
{
    FileComparisonTest test(TestNumber(), "FileComparisonTestRunFailureTest1",
        FileComparisonTestRunFailureTest1Helper);

    test.run();
    
    if (test.result().outcome() == TestResult::eFailed)
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}
