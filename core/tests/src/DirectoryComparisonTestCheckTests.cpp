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
    append<HeapAllocationErrorsTest>("run test 2", RunTest2);
    append<HeapAllocationErrorsTest>("run test 3", RunTest3);
    append<HeapAllocationErrorsTest>("run test 4", RunTest4);
    append<HeapAllocationErrorsTest>("run test 5", RunTest5);
    append<HeapAllocationErrorsTest>("run test 6", RunTest6);
    append<HeapAllocationErrorsTest>("run test 7", RunTest7);
    append<HeapAllocationErrorsTest>("run test 8", RunTest8);
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

void DirectoryComparisonTestCheckTests::RunTest2(Test& test)
{
    boost::filesystem::path outputDirectoryPath = test.context().getDataPath("ComparisonTestDirectories/Dir1");
    boost::filesystem::path referenceDirectoryPath = test.context().getDataPath("ComparisonTestDirectories/Dir3");

    DirectoryComparisonTestCheck directoryComparisonCheck(outputDirectoryPath, referenceDirectoryPath);

    Test checkTest(TestNumber(1), "DirectoryComparisonTestCheckTests_RunTest2");
    directoryComparisonCheck.run(checkTest, __FILE__, __LINE__);
    checkTest.pass();

    ISHIKO_TEST_FAIL_IF_NEQ(directoryComparisonCheck.result(), TestCheck::Result::passed);
    ISHIKO_TEST_FAIL_IF_NEQ(checkTest.result(), TestResult::passed);
    ISHIKO_TEST_PASS();
}

void DirectoryComparisonTestCheckTests::RunTest3(Test& test)
{
    boost::filesystem::path outputDirectoryPath = test.context().getDataPath("ComparisonTestDirectories/Dir1");
    boost::filesystem::path referenceDirectoryPath = test.context().getDataPath("ComparisonTestDirectories/Dir4");

    DirectoryComparisonTestCheck directoryComparisonCheck(outputDirectoryPath, referenceDirectoryPath);

    Test checkTest(TestNumber(1), "DirectoryComparisonTestCheckTests_RunTest3");
    directoryComparisonCheck.run(checkTest, __FILE__, __LINE__);
    checkTest.pass();

    ISHIKO_TEST_FAIL_IF_NEQ(directoryComparisonCheck.result(), TestCheck::Result::failed);
    ISHIKO_TEST_FAIL_IF_NEQ(checkTest.result(), TestResult::failed);
    ISHIKO_TEST_PASS();
}

void DirectoryComparisonTestCheckTests::RunTest4(Test& test)
{
    boost::filesystem::path outputDirectoryPath = test.context().getDataPath("ComparisonTestDirectories/Dir4");
    boost::filesystem::path referenceDirectoryPath = test.context().getDataPath("ComparisonTestDirectories/Dir1");

    DirectoryComparisonTestCheck directoryComparisonCheck(outputDirectoryPath, referenceDirectoryPath);

    Test checkTest(TestNumber(1), "DirectoryComparisonTestCheckTests_RunTest4");
    directoryComparisonCheck.run(checkTest, __FILE__, __LINE__);
    checkTest.pass();

    ISHIKO_TEST_FAIL_IF_NEQ(directoryComparisonCheck.result(), TestCheck::Result::failed);
    ISHIKO_TEST_FAIL_IF_NEQ(checkTest.result(), TestResult::failed);
    ISHIKO_TEST_PASS();
}

void DirectoryComparisonTestCheckTests::RunTest5(Test& test)
{
    boost::filesystem::path outputDirectoryPath = test.context().getDataPath("ComparisonTestDirectories/Dir5");
    boost::filesystem::path referenceDirectoryPath = test.context().getDataPath("ComparisonTestDirectories/Dir6");

    DirectoryComparisonTestCheck directoryComparisonCheck(outputDirectoryPath, referenceDirectoryPath);

    Test checkTest(TestNumber(1), "DirectoryComparisonTestCheckTests_RunTest5");
    directoryComparisonCheck.run(checkTest, __FILE__, __LINE__);
    checkTest.pass();

    ISHIKO_TEST_FAIL_IF_NEQ(directoryComparisonCheck.result(), TestCheck::Result::failed);
    ISHIKO_TEST_FAIL_IF_NEQ(checkTest.result(), TestResult::failed);
    ISHIKO_TEST_PASS();
}

void DirectoryComparisonTestCheckTests::RunTest6(Test& test)
{
    boost::filesystem::path outputDirectoryPath = test.context().getDataPath("ComparisonTestDirectories/Dir5");
    boost::filesystem::path referenceDirectoryPath = test.context().getDataPath("ComparisonTestDirectories/Dir7");

    DirectoryComparisonTestCheck directoryComparisonCheck(outputDirectoryPath, referenceDirectoryPath);

    Test checkTest(TestNumber(1), "DirectoryComparisonTestCheckTests_RunTest6");
    directoryComparisonCheck.run(checkTest, __FILE__, __LINE__);
    checkTest.pass();

    ISHIKO_TEST_FAIL_IF_NEQ(directoryComparisonCheck.result(), TestCheck::Result::passed);
    ISHIKO_TEST_FAIL_IF_NEQ(checkTest.result(), TestResult::passed);
    ISHIKO_TEST_PASS();
}

void DirectoryComparisonTestCheckTests::RunTest7(Test& test)
{
    boost::filesystem::path outputDirectoryPath = test.context().getDataPath("ComparisonTestDirectories/Dir1");
    boost::filesystem::path referenceDirectoryPath = test.context().getDataPath("DoesNotExist");

    DirectoryComparisonTestCheck directoryComparisonCheck(outputDirectoryPath, referenceDirectoryPath);

    Test checkTest(TestNumber(1), "DirectoryComparisonTestCheckTests_RunTest7");
    directoryComparisonCheck.run(checkTest, __FILE__, __LINE__);

    ISHIKO_TEST_FAIL_IF_NEQ(directoryComparisonCheck.result(), TestCheck::Result::failed);
    ISHIKO_TEST_FAIL_IF_NEQ(checkTest.result(), TestResult::failed);
    ISHIKO_TEST_PASS();
}

void DirectoryComparisonTestCheckTests::RunTest8(Test& test)
{
    boost::filesystem::path outputDirectoryPath = test.context().getDataPath("DoesNotExist");
    boost::filesystem::path referenceDirectoryPath = test.context().getDataPath("ComparisonTestDirectories/Dir1");

    DirectoryComparisonTestCheck directoryComparisonCheck(outputDirectoryPath, referenceDirectoryPath);

    Test checkTest(TestNumber(1), "DirectoryComparisonTestCheckTests_RunTest8");
    directoryComparisonCheck.run(checkTest, __FILE__, __LINE__);

    ISHIKO_TEST_FAIL_IF_NEQ(directoryComparisonCheck.result(), TestCheck::Result::failed);
    ISHIKO_TEST_FAIL_IF_NEQ(checkTest.result(), TestResult::failed);
    ISHIKO_TEST_PASS();
}
