/*
    Copyright (c) 2007-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "TestContextTests.hpp"
#include <Ishiko/Process/CurrentEnvironment.h>

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

    ISHIKO_TEST_FAIL_IF_NEQ(context.getTestDataDirectory(), "");
    ISHIKO_TEST_FAIL_IF_NEQ(context.getReferenceDataDirectory(), "");
    ISHIKO_TEST_FAIL_IF_NEQ(context.getTestOutputDirectory(), "");
    ISHIKO_TEST_PASS();
}

void TestContextTests::ConstructorTest2(Test& test)
{
    TestContext parentContext;
    TestContext context(&parentContext);

    ISHIKO_TEST_FAIL_IF_NEQ(context.getTestDataDirectory(), "");
    ISHIKO_TEST_FAIL_IF_NEQ(context.getReferenceDataDirectory(), "");
    ISHIKO_TEST_FAIL_IF_NEQ(context.getTestOutputDirectory(), "");
    ISHIKO_TEST_PASS();
}

void TestContextTests::ConstructorTest3(Test& test)
{
    TestContext parentContext;
    parentContext.setTestDataDirectory("data");
    parentContext.setReferenceDataDirectory("referenceData");
    parentContext.setTestOutputDirectory("output");

    TestContext context(&parentContext);

    ISHIKO_TEST_FAIL_IF_NEQ(context.getTestDataDirectory(), "data");
    ISHIKO_TEST_FAIL_IF_NEQ(context.getReferenceDataDirectory(), "referenceData");
    ISHIKO_TEST_FAIL_IF_NEQ(context.getTestOutputDirectory(), "output");
    ISHIKO_TEST_PASS();
}

void TestContextTests::GetTestDataDirectoryTest1(Test& test)
{
    TestContext context;

    boost::filesystem::path directory = context.getTestDataDirectory();

    ISHIKO_TEST_FAIL_IF_NEQ(directory, "");
    ISHIKO_TEST_PASS();
}

void TestContextTests::GetTestDataDirectoryTest2(Test& test)
{
    TestContext context;
    context.setTestDataDirectory("data");
    context.setReferenceDataDirectory("reference");
    context.setTestOutputDirectory("output");

    boost::filesystem::path directory = context.getTestDataDirectory();

    ISHIKO_TEST_FAIL_IF_NEQ(directory, "data");
    ISHIKO_TEST_PASS();
}

void TestContextTests::GetTestDataDirectoryTest3(Test& test)
{
    try
    {
        TestContext context;
        context.getTestDataDirectory("dummy");
    }
    catch (const TestException&)
    {
        ISHIKO_TEST_PASS();
    }
}

void TestContextTests::GetTestDataDirectoryTest4(Test& test)
{
    TestContext context;
    context.setTestDataDirectory("id1", "path1");
    if (context.getTestDataDirectory("id1") == "path1")
    {
        return ISHIKO_TEST_PASS();
    }
}

void TestContextTests::GetTestDataDirectoryTest5(Test& test)
{
    CurrentEnvironment::Set("TestEnvironmentGetTestDataDirectoryTest3", "dummy");

    TestContext context;
    context.setTestDataDirectory("id1", "$(TestEnvironmentGetTestDataDirectoryTest3)/path1");
    if (context.getTestDataDirectory("id1") == "dummy/path1")
    {
        ISHIKO_TEST_PASS();
    }
}

void TestContextTests::GetTestDataPathTest1(Test& test)
{
    TestContext context;
    context.setTestDataDirectory("data");

    boost::filesystem::path dataPath = context.getTestDataPath("file");

    ISHIKO_TEST_FAIL_IF_NEQ(dataPath, "data/file");
    ISHIKO_TEST_PASS();
}

void TestContextTests::SetTestDataDirectoryTest1(Test& test)
{
    TestContext parentContext;
    parentContext.setTestDataDirectory("parent");

    TestContext context(&parentContext);
    context.setTestDataDirectory("testData");

    ISHIKO_TEST_FAIL_IF_NEQ(parentContext.getTestDataDirectory(), "parent");
    ISHIKO_TEST_FAIL_IF_NEQ(context.getTestDataDirectory(), "parent/testData");
    ISHIKO_TEST_PASS();
}

void TestContextTests::GetReferenceDataDirectoryTest1(Test& test)
{
    TestContext context;

    boost::filesystem::path directory = context.getReferenceDataDirectory();
    
    ISHIKO_TEST_FAIL_IF_NEQ(directory, "");
    ISHIKO_TEST_PASS();
}

void TestContextTests::GetReferenceDataDirectoryTest2(Test& test)
{
    TestContext context;
    context.setTestDataDirectory("data");
    context.setReferenceDataDirectory("reference");
    context.setTestOutputDirectory("output");

    boost::filesystem::path directory = context.getReferenceDataDirectory();

    ISHIKO_TEST_FAIL_IF_NEQ(directory, "reference");
    ISHIKO_TEST_PASS();
}

void TestContextTests::GetReferenceDataPathTest1(Test& test)
{
    TestContext context;
    context.setReferenceDataDirectory("reference");

    boost::filesystem::path referencePath = context.getReferenceDataPath("file");

    ISHIKO_TEST_FAIL_IF_NEQ(referencePath, "reference/file");
    ISHIKO_TEST_PASS();
}

void TestContextTests::SetReferenceDataDirectoryTest1(Test& test)
{
    TestContext parentContext;
    parentContext.setReferenceDataDirectory("parent");

    TestContext context(&parentContext);
    context.setReferenceDataDirectory("referenceData");

    ISHIKO_TEST_FAIL_IF_NEQ(parentContext.getReferenceDataDirectory(), "parent");
    ISHIKO_TEST_FAIL_IF_NEQ(context.getReferenceDataDirectory(), "parent/referenceData");
    ISHIKO_TEST_PASS();
}

void TestContextTests::GetTestOutputDirectoryTest1(Test& test)
{
    TestContext context;

    boost::filesystem::path directory = context.getTestOutputDirectory();

    ISHIKO_TEST_FAIL_IF_NEQ(directory, "");
    ISHIKO_TEST_PASS();
}

void TestContextTests::GetTestOutputDirectoryTest2(Test& test)
{
    TestContext context;
    context.setTestDataDirectory("data");
    context.setReferenceDataDirectory("reference");
    context.setTestOutputDirectory("output");

    boost::filesystem::path directory = context.getTestOutputDirectory();

    ISHIKO_TEST_FAIL_IF_NEQ(directory, "output");
    ISHIKO_TEST_PASS();
}

void TestContextTests::GetTestOutputPathTest1(Test& test)
{
    TestContext context;
    context.setTestOutputDirectory("output");

    boost::filesystem::path outputPath = context.getTestOutputPath("file");

    ISHIKO_TEST_FAIL_IF_NEQ(outputPath, "output/file");
    ISHIKO_TEST_PASS();
}

void TestContextTests::SetTestOutputDirectoryTest1(Test& test)
{
    TestContext parentContext;
    parentContext.setTestOutputDirectory("parent");

    TestContext context(&parentContext);
    context.setTestOutputDirectory("output");

    ISHIKO_TEST_FAIL_IF_NEQ(parentContext.getTestOutputDirectory(), "parent");
    ISHIKO_TEST_FAIL_IF_NEQ(context.getTestOutputDirectory(), "parent/output");
    ISHIKO_TEST_PASS();
}
