/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "DirectoryComparisonTestCheckTests.hpp"

using namespace Ishiko;

DirectoryComparisonTestCheckTests::DirectoryComparisonTestCheckTests(const TestNumber& number,
    const TestContext& context)
    : TestSequence(number, "DirectoryComparisonTestCheck tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("run test 1", RunTest1);
}

void DirectoryComparisonTestCheckTests::ConstructorTest1(Test& test)
{
    DirectoryComparisonTestCheck directoryComparisonCheck;

    ISHIKO_TEST_PASS();
}

void DirectoryComparisonTestCheckTests::RunTest1(Test& test)
{
    boost::filesystem::path outputDirectoryPath = test.context().getDataPath("ComparisonTestDirectories/Dir1");
    boost::filesystem::path referenceDirectoryPath = test.context().getDataPath("ComparisonTestDirectories/Dir2");

    DirectoryComparisonTestCheck directoryComparisonCheck(outputDirectoryPath, referenceDirectoryPath);

    Test checkTest(TestNumber(1), "DirectoryComparisonTestCheckTests_RunTest1");
    directoryComparisonCheck.run(checkTest, __FILE__, __LINE__);

    ISHIKO_TEST_FAIL_IF_NEQ(directoryComparisonCheck.result(), TestCheck::Result::failed);
    ISHIKO_TEST_FAIL_IF_NEQ(checkTest.result(), TestResult::failed);
    ISHIKO_TEST_PASS();
}
