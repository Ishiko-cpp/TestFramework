/*
    Copyright (c) 2007-2023 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "TestContextTests.hpp"
#include <Ishiko/Process.hpp>

using namespace Ishiko;

TestContextTests::TestContextTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "TestContext tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("Constructor test 3", ConstructorTest3);
    append<HeapAllocationErrorsTest>("getTestDataDirectory test 1", GetTestDataDirectoryTest1);
    append<HeapAllocationErrorsTest>("getTestDataDirectory test 2", GetTestDataDirectoryTest2);
    append<HeapAllocationErrorsTest>("getTestDataDirectory test 3", GetTestDataDirectoryTest3);
    append<HeapAllocationErrorsTest>("getTestDataDirectory test 4", GetTestDataDirectoryTest4);
    append<HeapAllocationErrorsTest>("getTestDataDirectory test 5", GetTestDataDirectoryTest5);
    append<HeapAllocationErrorsTest>("getTestDataPath test 1", GetTestDataPathTest1);
    append<HeapAllocationErrorsTest>("setTestDataDirectory test 1", SetTestDataDirectoryTest1);
    append<HeapAllocationErrorsTest>("getReferenceDataDirectory test 1", GetReferenceDataDirectoryTest1);
    append<HeapAllocationErrorsTest>("getReferenceDataDirectory test 2", GetReferenceDataDirectoryTest2);
    append<HeapAllocationErrorsTest>("getReferenceDataPath test 1", GetReferenceDataPathTest1);
    append<HeapAllocationErrorsTest>("setReferenceDataDirectory test 1", SetReferenceDataDirectoryTest1);
    append<HeapAllocationErrorsTest>("getTestOutputDirectory test 1", GetTestOutputDirectoryTest1);
    append<HeapAllocationErrorsTest>("getTestOutputDirectory test 2", GetTestOutputDirectoryTest2);
    append<HeapAllocationErrorsTest>("getTestOutputPath test 1", GetTestOutputPathTest1);
    append<HeapAllocationErrorsTest>("setTestOutputDirectory test 1", SetTestOutputDirectoryTest1);
}

void TestContextTests::ConstructorTest1(Test& test)
{
    TestContext context;

    ISHIKO_TEST_FAIL_IF_NEQ(context.getDataDirectory(), "");
    ISHIKO_TEST_FAIL_IF_NEQ(context.getReferenceDirectory(), "");
    ISHIKO_TEST_FAIL_IF_NEQ(context.getOutputDirectory(), "");
    ISHIKO_TEST_PASS();
}

void TestContextTests::ConstructorTest2(Test& test)
{
    TestContext parentContext;
    TestContext context(&parentContext);

    ISHIKO_TEST_FAIL_IF_NEQ(context.getDataDirectory(), "");
    ISHIKO_TEST_FAIL_IF_NEQ(context.getReferenceDirectory(), "");
    ISHIKO_TEST_FAIL_IF_NEQ(context.getOutputDirectory(), "");
    ISHIKO_TEST_PASS();
}

void TestContextTests::ConstructorTest3(Test& test)
{
    TestContext parentContext;
    parentContext.setDataDirectory("data");
    parentContext.setReferenceDirectory("referenceData");
    parentContext.setOutputDirectory("output");

    TestContext context(&parentContext);

    ISHIKO_TEST_FAIL_IF_NEQ(context.getDataDirectory(), "data");
    ISHIKO_TEST_FAIL_IF_NEQ(context.getReferenceDirectory(), "referenceData");
    ISHIKO_TEST_FAIL_IF_NEQ(context.getOutputDirectory(), "output");
    ISHIKO_TEST_PASS();
}

void TestContextTests::GetTestDataDirectoryTest1(Test& test)
{
    TestContext context;

    boost::filesystem::path directory = context.getDataDirectory();

    ISHIKO_TEST_FAIL_IF_NEQ(directory, "");
    ISHIKO_TEST_PASS();
}

void TestContextTests::GetTestDataDirectoryTest2(Test& test)
{
    TestContext context;
    context.setDataDirectory("data");
    context.setReferenceDirectory("reference");
    context.setOutputDirectory("output");

    boost::filesystem::path directory = context.getDataDirectory();

    ISHIKO_TEST_FAIL_IF_NEQ(directory, "data");
    ISHIKO_TEST_PASS();
}

void TestContextTests::GetTestDataDirectoryTest3(Test& test)
{
    try
    {
        TestContext context;
        context.getDataDirectory("dummy");
    }
    catch (const TestException&)
    {
        ISHIKO_TEST_PASS();
    }
}

void TestContextTests::GetTestDataDirectoryTest4(Test& test)
{
    TestContext context;
    context.setDataDirectory("id1", "path1");
    if (context.getDataDirectory("id1") == "path1")
    {
        return ISHIKO_TEST_PASS();
    }
}

void TestContextTests::GetTestDataDirectoryTest5(Test& test)
{
    CurrentEnvironment::Set("TestEnvironmentGetTestDataDirectoryTest3", "dummy");

    TestContext context;
    context.setDataDirectory("id1", "${TestEnvironmentGetTestDataDirectoryTest3}/path1");
    if (context.getDataDirectory("id1") == "dummy/path1")
    {
        ISHIKO_TEST_PASS();
    }
}

void TestContextTests::GetTestDataPathTest1(Test& test)
{
    TestContext context;
    context.setDataDirectory("data");

    boost::filesystem::path dataPath = context.getDataPath("file");

    ISHIKO_TEST_FAIL_IF_NEQ(dataPath, "data/file");
    ISHIKO_TEST_PASS();
}

void TestContextTests::SetTestDataDirectoryTest1(Test& test)
{
    TestContext parentContext;
    parentContext.setDataDirectory("parent");

    TestContext context(&parentContext);
    context.setDataDirectory("testData");

    ISHIKO_TEST_FAIL_IF_NEQ(parentContext.getDataDirectory(), "parent");
    ISHIKO_TEST_FAIL_IF_NEQ(context.getDataDirectory(), "parent/testData");
    ISHIKO_TEST_PASS();
}

void TestContextTests::GetReferenceDataDirectoryTest1(Test& test)
{
    TestContext context;

    boost::filesystem::path directory = context.getReferenceDirectory();
    
    ISHIKO_TEST_FAIL_IF_NEQ(directory, "");
    ISHIKO_TEST_PASS();
}

void TestContextTests::GetReferenceDataDirectoryTest2(Test& test)
{
    TestContext context;
    context.setDataDirectory("data");
    context.setReferenceDirectory("reference");
    context.setOutputDirectory("output");

    boost::filesystem::path directory = context.getReferenceDirectory();

    ISHIKO_TEST_FAIL_IF_NEQ(directory, "reference");
    ISHIKO_TEST_PASS();
}

void TestContextTests::GetReferenceDataPathTest1(Test& test)
{
    TestContext context;
    context.setReferenceDirectory("reference");

    boost::filesystem::path referencePath = context.getReferencePath("file", false);

    ISHIKO_TEST_FAIL_IF_NEQ(referencePath, "reference/file");
    ISHIKO_TEST_PASS();
}

void TestContextTests::SetReferenceDataDirectoryTest1(Test& test)
{
    TestContext parentContext;
    parentContext.setReferenceDirectory("parent");

    TestContext context(&parentContext);
    context.setReferenceDirectory("referenceData");

    ISHIKO_TEST_FAIL_IF_NEQ(parentContext.getReferenceDirectory(), "parent");
    ISHIKO_TEST_FAIL_IF_NEQ(context.getReferenceDirectory(), "parent/referenceData");
    ISHIKO_TEST_PASS();
}

void TestContextTests::GetTestOutputDirectoryTest1(Test& test)
{
    TestContext context;

    boost::filesystem::path directory = context.getOutputDirectory();

    ISHIKO_TEST_FAIL_IF_NEQ(directory, "");
    ISHIKO_TEST_PASS();
}

void TestContextTests::GetTestOutputDirectoryTest2(Test& test)
{
    TestContext context;
    context.setDataDirectory("data");
    context.setReferenceDirectory("reference");
    context.setOutputDirectory("output");

    boost::filesystem::path directory = context.getOutputDirectory();

    ISHIKO_TEST_FAIL_IF_NEQ(directory, "output");
    ISHIKO_TEST_PASS();
}

void TestContextTests::GetTestOutputPathTest1(Test& test)
{
    TestContext context;
    context.setOutputDirectory("output");

    boost::filesystem::path outputPath = context.getOutputPath("file");

    ISHIKO_TEST_FAIL_IF_NEQ(outputPath, "output/file");
    ISHIKO_TEST_PASS();
}

void TestContextTests::SetTestOutputDirectoryTest1(Test& test)
{
    TestContext parentContext;
    parentContext.setOutputDirectory("parent");

    TestContext context(&parentContext);
    context.setOutputDirectory("output");

    ISHIKO_TEST_FAIL_IF_NEQ(parentContext.getOutputDirectory(), "parent");
    ISHIKO_TEST_FAIL_IF_NEQ(context.getOutputDirectory(), "parent/output");
    ISHIKO_TEST_PASS();
}
