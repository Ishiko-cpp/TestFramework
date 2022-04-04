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
    append<HeapAllocationErrorsTest>("CreateFromContext test 1", CreateFromContextTest1);
    append<HeapAllocationErrorsTest>("run test 1", RunTest1);
    append<HeapAllocationErrorsTest>("run test 2", RunTest2);
}

void FileComparisonTestCheckTests::ConstructorTest1(Test& test)
{
    FileComparisonTestCheck fileComparisonCheck("outputFilePath", "referenceFilePath");

    ISHIKO_TEST_FAIL_IF_NEQ(fileComparisonCheck.outputFilePath(), "outputFilePath");
    ISHIKO_TEST_FAIL_IF_NEQ(fileComparisonCheck.referenceFilePath(), "referenceFilePath");
    ISHIKO_TEST_PASS();
}

void FileComparisonTestCheckTests::CreateFromContextTest1(Test& test)
{
    TestContext context;
    context.setTestOutputDirectory("output");
    context.setReferenceDataDirectory("reference");
    FileComparisonTestCheck fileComparisonCheck =
        FileComparisonTestCheck::CreateFromContext(context, "outputFilePath", "referenceFilePath");

    ISHIKO_TEST_FAIL_IF_NEQ(fileComparisonCheck.outputFilePath(), "output/outputFilePath");
    ISHIKO_TEST_FAIL_IF_NEQ(fileComparisonCheck.referenceFilePath(), "reference/referenceFilePath");
    ISHIKO_TEST_PASS();
}

void FileComparisonTestCheckTests::RunTest1(Test& test)
{
    path outputFilePath = test.context().getTestDataPath("ComparisonTestFiles/Hello.txt");
    path referenceFilePath = test.context().getTestDataPath("ComparisonTestFiles/NotHello.txt");

    FileComparisonTestCheck fileComparisonCheck(outputFilePath, referenceFilePath);

    TestCheck::Result result = fileComparisonCheck.run();

    ISHIKO_TEST_FAIL_IF_NEQ(result, TestCheck::Result::failed);
    ISHIKO_TEST_PASS();
}

void FileComparisonTestCheckTests::RunTest2(Test& test)
{
    path outputFilePath = test.context().getTestDataPath("ComparisonTestFiles/Hello.txt");
    path referenceFilePath = test.context().getTestDataPath("ComparisonTestFiles/Hello2.txt");

    FileComparisonTestCheck fileComparisonCheck(outputFilePath, referenceFilePath);

    TestCheck::Result result = fileComparisonCheck.run();

    ISHIKO_TEST_FAIL_IF_NEQ(result, TestCheck::Result::passed);
    ISHIKO_TEST_PASS();
}
