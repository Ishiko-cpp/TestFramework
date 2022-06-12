/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "FileComparisonTestCheckTests.hpp"

using namespace Ishiko;

FileComparisonTestCheckTests::FileComparisonTestCheckTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "FileComparisonTestCheck tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("CreateFromContext test 1", CreateFromContextTest1);
    append<HeapAllocationErrorsTest>("run test 1", RunTest1);
    append<HeapAllocationErrorsTest>("run test 2", RunTest2);
    append<HeapAllocationErrorsTest>("Persistent storage test 1", PersistentStorageTest1);
    append<HeapAllocationErrorsTest>("addToJUnitXMLTestReport test 1", AddToJUnitXMLTestReportTest1);
}

void FileComparisonTestCheckTests::ConstructorTest1(Test& test)
{
    FileComparisonTestCheck fileComparisonCheck("outputFilePath", "referenceFilePath");

    ISHIKO_TEST_FAIL_IF_NEQ(fileComparisonCheck.result(), TestCheck::Result::failed);
    ISHIKO_TEST_FAIL_IF_NEQ(fileComparisonCheck.outputFilePath(), "outputFilePath");
    ISHIKO_TEST_FAIL_IF_NEQ(fileComparisonCheck.referenceFilePath(), "referenceFilePath");
    ISHIKO_TEST_PASS();
}

void FileComparisonTestCheckTests::CreateFromContextTest1(Test& test)
{
    TestContext context;
    context.setOutputDirectory("output");
    context.setReferenceDirectory("reference");
    FileComparisonTestCheck fileComparisonCheck =
        FileComparisonTestCheck::CreateFromContext(context, "outputFilePath", "referenceFilePath");

    ISHIKO_TEST_FAIL_IF_NEQ(fileComparisonCheck.result(), TestCheck::Result::failed);
    ISHIKO_TEST_FAIL_IF_NEQ(fileComparisonCheck.outputFilePath(), "output/outputFilePath");
    ISHIKO_TEST_FAIL_IF_NEQ(fileComparisonCheck.referenceFilePath(), "reference/referenceFilePath");
    ISHIKO_TEST_PASS();
}

void FileComparisonTestCheckTests::RunTest1(Test& test)
{
    boost::filesystem::path outputFilePath = test.context().getDataPath("ComparisonTestFiles/Hello.txt");
    boost::filesystem::path referenceFilePath = test.context().getDataPath("ComparisonTestFiles/NotHello.txt");

    FileComparisonTestCheck fileComparisonCheck(outputFilePath, referenceFilePath);

    Test checkTest(TestNumber(1), "FileComparisonTestCheckTests_RunTest1");
    fileComparisonCheck.run(checkTest, __FILE__, __LINE__);

    ISHIKO_TEST_FAIL_IF_NEQ(fileComparisonCheck.result(), TestCheck::Result::failed);
    ISHIKO_TEST_FAIL_IF_NEQ(checkTest.result(), TestResult::failed);
    ISHIKO_TEST_PASS();
}

void FileComparisonTestCheckTests::RunTest2(Test& test)
{
    boost::filesystem::path outputFilePath = test.context().getDataPath("ComparisonTestFiles/Hello.txt");
    boost::filesystem::path referenceFilePath = test.context().getDataPath("ComparisonTestFiles/Hello2.txt");

    FileComparisonTestCheck fileComparisonCheck(outputFilePath, referenceFilePath);

    Test checkTest(TestNumber(1), "FileComparisonTestCheckTests_RunTest2");
    fileComparisonCheck.run(checkTest, __FILE__, __LINE__);
    checkTest.pass();

    ISHIKO_TEST_FAIL_IF_NEQ(fileComparisonCheck.result(), TestCheck::Result::passed);
    ISHIKO_TEST_FAIL_IF_NEQ(checkTest.result(), TestResult::passed);
    ISHIKO_TEST_PASS();
}

void FileComparisonTestCheckTests::PersistentStorageTest1(Test& test)
{
    boost::filesystem::path outputFilePath = test.context().getDataPath("ComparisonTestFiles/Hello.txt");
    boost::filesystem::path referenceFilePath = test.context().getDataPath("ComparisonTestFiles/NotHello.txt");
    boost::filesystem::path simulatedPersistentStorage = test.context().getOutputDirectory();

    FileComparisonTestCheck fileComparisonCheck(outputFilePath, referenceFilePath);

    TestContext checkTestContext;
    checkTestContext.setOutputDirectory("persistent-storage", simulatedPersistentStorage.string());
    Test checkTest(TestNumber(1), "FileComparisonTestCheckTests_PersistentStorageTest1", checkTestContext);
    fileComparisonCheck.run(checkTest, __FILE__, __LINE__);

    ISHIKO_TEST_FAIL_IF_NEQ(fileComparisonCheck.result(), TestCheck::Result::failed);
    ISHIKO_TEST_FAIL_IF_NEQ(checkTest.result(), TestResult::failed);
    // TODO: should be a directory compare
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("FileComparisonTestCheckTests_PersistentStorageTest1/Hello.txt");
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("FileComparisonTestCheckTests_PersistentStorageTest1/NotHello.txt");
    ISHIKO_TEST_PASS();
}

void FileComparisonTestCheckTests::AddToJUnitXMLTestReportTest1(Test& test)
{
    // In general we don't care about making the paths portable between Windows and POSIX but here they will end up in
    // the output and reference file and we want to avoid having to create 2 reference files.
    boost::filesystem::path outputFilePath =
        test.context().getDataPath("ComparisonTestFiles/Hello.txt").generic_string();
    boost::filesystem::path referenceFilePath =
        test.context().getDataPath("ComparisonTestFiles/NotHello.txt").generic_string();

    FileComparisonTestCheck fileComparisonCheck(outputFilePath, referenceFilePath);

    Test checkTest(TestNumber(1), "FileComparisonTestCheckTests_RunTest1");
    fileComparisonCheck.run(checkTest, __FILE__, __LINE__);

    ISHIKO_TEST_FAIL_IF_NEQ(fileComparisonCheck.result(), TestCheck::Result::failed);
    ISHIKO_TEST_FAIL_IF_NEQ(checkTest.result(), TestResult::failed);

    boost::filesystem::path xmlOutputPath =
        test.context().getOutputPath("FileComparisonTestCheckTests_AddToJUnitXMLTestReportTest1.xml");

    JUnitXMLWriter junitXMLWriter;

    Error error;
    junitXMLWriter.create(xmlOutputPath, error);

    ISHIKO_TEST_FAIL_IF(error);

    // Note that this won't produce a valid JUnit XML file because the TestCheck::addToJUnitXMLTestReport function only
    // writes the failure message. The Test class is responsible for writing the rest.
    fileComparisonCheck.addToJUnitXMLTestReport(junitXMLWriter);

    junitXMLWriter.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("FileComparisonTestCheckTests_AddToJUnitXMLTestReportTest1.xml");
    ISHIKO_TEST_PASS();
}
