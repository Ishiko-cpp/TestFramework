/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "ConsoleApplicationTestTests.h"
#include <boost/filesystem.hpp>

using namespace Ishiko::Tests;
using namespace boost::filesystem;

ConsoleApplicationTestTests::ConsoleApplicationTestTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "ConsoleApplicationTest tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("run success test 1", RunSuccessTest1);
    append<HeapAllocationErrorsTest>("run success test 2", RunSuccessTest2);
    append<HeapAllocationErrorsTest>("run failure test 1", RunFailureTest1);
    append<HeapAllocationErrorsTest>("run success test 3", RunSuccessTest3);
    append<HeapAllocationErrorsTest>("run failure test 2", RunFailureTest2);
}

void ConsoleApplicationTestTests::CreationTest1(Test& test)
{
#ifdef __linux__
    path executablePath(test.context().getTestDataDirectory() / "bin/WriteFileTestHelper");
#else
    path executablePath(test.context().getTestDataDirectory() / "bin/WriteFileTestHelper.exe");
#endif

    ConsoleApplicationTest applicationTest(TestNumber(), "ConsoleApplicationTestCreationTest1",
        executablePath.string().c_str(), 0);

    ISHIKO_PASS();
}

void ConsoleApplicationTestTests::RunSuccessTest1(Test& test)
{
#ifdef __linux__
    path executablePath(test.context().getTestDataDirectory() / "bin/ExitCodeTestHelper");
#else
    path executablePath(test.context().getTestDataDirectory() / "bin/ExitCodeTestHelper.exe");
#endif

    ConsoleApplicationTest applicationTest(TestNumber(), "ConsoleApplicationTestRunSuccessTest1",
        executablePath.string(), 0);
    applicationTest.run();

    ISHIKO_FAIL_IF_NOT(applicationTest.passed());
    ISHIKO_PASS();
}

void ConsoleApplicationTestTests::RunSuccessTest2(Test& test)
{
#ifdef __linux__
    path executablePath(test.context().getTestDataDirectory() / "bin/ExitCodeTestHelper");
#else
    path executablePath(test.context().getTestDataDirectory() / "bin/ExitCodeTestHelper.exe");
#endif

    std::string commandLine = executablePath.string() + " 3";
    ConsoleApplicationTest applicationTest(TestNumber(), "ConsoleApplicationTestRunSuccessTest2", commandLine, 3);
    applicationTest.run();

    ISHIKO_FAIL_IF_NOT(applicationTest.passed());
    ISHIKO_PASS();
}

void ConsoleApplicationTestTests::RunFailureTest1(Test& test)
{
#ifdef __linux__
    path executablePath(test.context().getTestDataDirectory() / "bin/ExitCodeTestHelper");
#else
    path executablePath(test.context().getTestDataDirectory() / "bin/ExitCodeTestHelper.exe");
#endif

    ConsoleApplicationTest applicationTest(TestNumber(), "ConsoleApplicationTestRunFailureTest1",
        executablePath.string(), 3);
    applicationTest.run();

    ISHIKO_FAIL_IF(applicationTest.passed());
    ISHIKO_PASS();
}

void ConsoleApplicationTestTests::RunSuccessTest3(Test& test)
{
    create_directories(test.context().getTestOutputDirectory() / "ConsoleApplicationTestTests");

#ifdef __linux__
    path executablePath(test.context().getTestDataDirectory() / "bin/StandardOutputTestHelper");
#else
    path executablePath(test.context().getTestDataDirectory() / "bin/StandardOutputTestHelper.exe");
#endif
    path outputPath(
        test.context().getTestOutputPath("ConsoleApplicationTestTests/ConsoleApplicationTestRunSuccessTest3.txt"));
    path referencePath(test.context().getReferenceDataDirectory()
        / "ConsoleApplicationTestTests/ConsoleApplicationTestRunSuccessTest3.txt");

    ConsoleApplicationTest applicationTest(TestNumber(), "ConsoleApplicationTestRunSuccessTest3",
        executablePath.string().c_str(), 0);
    applicationTest.setStandardOutputFilePath(outputPath);
    applicationTest.setStandardOutputReferenceFilePath(referencePath);
    applicationTest.run();

    ISHIKO_FAIL_IF_NOT(applicationTest.passed());
    ISHIKO_PASS();
}

void ConsoleApplicationTestTests::RunFailureTest2(Test& test)
{
    path executablePath(test.context().getTestDataDirectory() / "bin/StandardOutputTestHelper.exe");
    path outputPath(
        test.context().getTestOutputPath("ConsoleApplicationTestTests/ConsoleApplicationTestRunFailureTest2.txt"));
    path referencePath(
        test.context().getReferenceDataPath("ConsoleApplicationTestTests/ConsoleApplicationTestRunFailureTest2.txt"));

    ConsoleApplicationTest applicationTest(TestNumber(), "ConsoleApplicationTestRunFailureTest2",
        executablePath.string().c_str(), 0);
    applicationTest.setStandardOutputFilePath(outputPath);
    applicationTest.setStandardOutputReferenceFilePath(referencePath);
    applicationTest.run();

    ISHIKO_FAIL_IF(applicationTest.passed());
    ISHIKO_PASS();
}
