/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "FileComparisonTestCheckTests.hpp"

using namespace boost::filesystem;
using namespace Ishiko;

FileComparisonTestCheckTests::FileComparisonTestCheckTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "FileComparisonTestCheck tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("run test 1", RunTest1);
}

void FileComparisonTestCheckTests::ConstructorTest1(Test& test)
{
    path outputFilePath = test.context().getTestOutputPath("ComparisonTestFiles/Hello.txt");
    path referenceFilePath = test.context().getReferenceDataPath("ComparisonTestFiles/NotHello.txt");

    FileComparisonTestCheck fileComparisonCheck(outputFilePath, referenceFilePath);

    ISHIKO_TEST_PASS();
}

void FileComparisonTestCheckTests::RunTest1(Test& test)
{
    path outputFilePath = test.context().getTestOutputPath("ComparisonTestFiles/Hello.txt");
    path referenceFilePath = test.context().getReferenceDataPath("ComparisonTestFiles/NotHello.txt");

    FileComparisonTestCheck fileComparisonCheck(outputFilePath, referenceFilePath);

    TestCheck::Result result = fileComparisonCheck.run();

    ISHIKO_TEST_FAIL_IF_NEQ(result, TestCheck::Result::failed);
    ISHIKO_TEST_PASS();
}
