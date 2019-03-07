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

using namespace Ishiko::Tests;

FileComparisonTestTests::FileComparisonTestTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "FileComparisonTest tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("run success test 1", RunSuccessTest1);
    append<HeapAllocationErrorsTest>("run failure test 1", RunFailureTest1);
}

void FileComparisonTestCreationTest1Helper(FileComparisonTest& test)
{
    ISHTF_PASS();
}

void FileComparisonTestTests::CreationTest1(Test& test)
{
    FileComparisonTest comparisonTest(TestNumber(), "FileComparisonTestCreationTest1",
        FileComparisonTestCreationTest1Helper);
    ISHTF_PASS();
}

void FileComparisonTestRunSuccessTest1Helper(FileComparisonTest& test)
{
    test.setOutputFilePath("../../TestData/ComparisonTestFiles/Hello.txt");
    test.setReferenceFilePath("../../TestData/ComparisonTestFiles/Hello2.txt");
    ISHTF_PASS();
}

void FileComparisonTestTests::RunSuccessTest1(Test& test)
{
    FileComparisonTest comparisonTest(TestNumber(), "FileComparisonTestRunSuccessTest1",
        FileComparisonTestRunSuccessTest1Helper);
    
    comparisonTest.run();
    
    ISHTF_FAIL_IF(comparisonTest.result() != TestResult::ePassed);
    ISHTF_PASS();
}

void FileComparisonTestRunFailureTest1Helper(FileComparisonTest& test)
{
    test.setOutputFilePath("../../TestData/ComparisonTestFiles/Hello.txt");
    test.setReferenceFilePath("../../TestData/ComparisonTestFiles/NotHello.txt");
    ISHTF_PASS();
}

void FileComparisonTestTests::RunFailureTest1(Test& test)
{
    FileComparisonTest comparisonTest(TestNumber(), "FileComparisonTestRunFailureTest1",
        FileComparisonTestRunFailureTest1Helper);

    comparisonTest.run();
    
    ISHTF_FAIL_IF(comparisonTest.result() != TestResult::eFailed);
    ISHTF_PASS();
}
