/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "JUnitXMLWriterTests.h"
#include <Ishiko/TestFramework/Core/JUnitXMLWriter.hpp>

using namespace Ishiko;

JUnitXMLWriterTests::JUnitXMLWriterTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "JUnitXMLWriter tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("create test 1", CreateTest1);
    append<HeapAllocationErrorsTest>("writeTestSuitesStart test 1", WriteTestSuitesStartTest1);
    append<HeapAllocationErrorsTest>("writeTestSuiteStart test 1", WriteTestSuiteStartTest1);
}

void JUnitXMLWriterTests::ConstructorTest1(Test& test)
{
    JUnitXMLWriter junitXMLWriter;

    ISHIKO_TEST_PASS();
}

void JUnitXMLWriterTests::CreateTest1(Test& test)
{
    boost::filesystem::path outputPath = test.context().getTestOutputPath("JUnitXMLWriterTests_CreateTest1.xml");

    JUnitXMLWriter junitXMLWriter;

    Error error;
    junitXMLWriter.create(outputPath, error);

    ISHIKO_TEST_FAIL_IF(error);

    junitXMLWriter.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("JUnitXMLWriterTests_CreateTest1.xml", "JUnitXMLWriterTests_CreateTest1.xml");
    ISHIKO_TEST_PASS();
}

void JUnitXMLWriterTests::WriteTestSuitesStartTest1(Test& test)
{
    boost::filesystem::path outputPath =
        test.context().getTestOutputPath("JUnitXMLWriterTests_WriteTestSuitesStartTest1.xml");

    JUnitXMLWriter junitXMLWriter;

    Error error;
    junitXMLWriter.create(outputPath, error);

    ISHIKO_TEST_FAIL_IF(error);

    junitXMLWriter.writeTestSuitesStart();
    junitXMLWriter.writeTestSuitesEnd();

    junitXMLWriter.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("JUnitXMLWriterTests_WriteTestSuitesStartTest1.xml",
        "JUnitXMLWriterTests_WriteTestSuitesStartTest1.xml");
    ISHIKO_TEST_PASS();
}

void JUnitXMLWriterTests::WriteTestSuiteStartTest1(Test& test)
{
    boost::filesystem::path outputPath =
        test.context().getTestOutputPath("JUnitXMLWriterTests_WriteTestSuiteStartTest1.xml");

    JUnitXMLWriter junitXMLWriter;

    Error error;
    junitXMLWriter.create(outputPath, error);

    ISHIKO_TEST_FAIL_IF(error);

    junitXMLWriter.writeTestSuitesStart();
    junitXMLWriter.writeTestSuiteStart(0);
    junitXMLWriter.writeTestSuiteEnd();
    junitXMLWriter.writeTestSuitesEnd();

    junitXMLWriter.close();

    ISHIKO_TEST_FAIL_IF_FILES_NEQ("JUnitXMLWriterTests_WriteTestSuiteStartTest1.xml",
        "JUnitXMLWriterTests_WriteTestSuiteStartTest1.xml");
    ISHIKO_TEST_PASS();
}
