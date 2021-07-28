/*
    Copyright (c) 2007-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
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
    ISHIKO_PASS();
}

void FileComparisonTestTests::CreationTest1(Test& test)
{
    FileComparisonTest comparisonTest(TestNumber(), "FileComparisonTestCreationTest1",
        FileComparisonTestCreationTest1Helper);

    ISHIKO_PASS();
}

void FileComparisonTestRunSuccessTest1Helper(FileComparisonTest& test)
{
    test.setOutputFilePath("../../data/ComparisonTestFiles/Hello.txt");
    test.setReferenceFilePath("../../data/ComparisonTestFiles/Hello2.txt");

    ISHIKO_PASS();
}

void FileComparisonTestTests::RunSuccessTest1(Test& test)
{
    FileComparisonTest comparisonTest(TestNumber(), "FileComparisonTestRunSuccessTest1",
        FileComparisonTestRunSuccessTest1Helper);
    
    comparisonTest.run();
    
    ISHIKO_FAIL_IF_NEQ(comparisonTest.result(), TestResult::passed);
    ISHIKO_PASS();
}

void FileComparisonTestRunFailureTest1Helper(FileComparisonTest& test)
{
    test.setOutputFilePath("../../data/ComparisonTestFiles/Hello.txt");
    test.setReferenceFilePath("../../data/ComparisonTestFiles/NotHello.txt");

    ISHIKO_PASS();
}

void FileComparisonTestTests::RunFailureTest1(Test& test)
{
    FileComparisonTest comparisonTest(TestNumber(), "FileComparisonTestRunFailureTest1",
        FileComparisonTestRunFailureTest1Helper);

    comparisonTest.run();
    
    ISHIKO_FAIL_IF_NEQ(comparisonTest.result(), TestResult::failed);
    ISHIKO_PASS();
}
