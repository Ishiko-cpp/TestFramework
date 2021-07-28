/*
    Copyright (c) 2007-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "TestEnvironmentTests.h"
#include <Ishiko/Process/CurrentEnvironment.h>

using namespace Ishiko::Tests;

TestEnvironmentTests::TestEnvironmentTests(const TestNumber& number,
    const TestEnvironment& environment)
    : TestSequence(number, "TestEnvironment tests", environment)
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

void TestEnvironmentTests::ConstructorTest1(Test& test)
{
    TestEnvironment environment;

    ISHIKO_FAIL_IF_NEQ(environment.getTestDataDirectory(), "");
    ISHIKO_FAIL_IF_NEQ(environment.getReferenceDataDirectory(), "");
    ISHIKO_FAIL_IF_NEQ(environment.getTestOutputDirectory(), "");
    ISHIKO_PASS();
}

void TestEnvironmentTests::ConstructorTest2(Test& test)
{
    TestEnvironment parentEnvironment;
    TestEnvironment environment(&parentEnvironment);

    ISHIKO_FAIL_IF_NEQ(environment.getTestDataDirectory(), "");
    ISHIKO_FAIL_IF_NEQ(environment.getReferenceDataDirectory(), "");
    ISHIKO_FAIL_IF_NEQ(environment.getTestOutputDirectory(), "");
    ISHIKO_PASS();
}

void TestEnvironmentTests::ConstructorTest3(Test& test)
{
    TestEnvironment parentEnvironment;
    parentEnvironment.setTestDataDirectory("data");
    parentEnvironment.setReferenceDataDirectory("referenceData");
    parentEnvironment.setTestOutputDirectory("output");

    TestEnvironment environment(&parentEnvironment);

    ISHIKO_FAIL_IF_NEQ(environment.getTestDataDirectory(), "data");
    ISHIKO_FAIL_IF_NEQ(environment.getReferenceDataDirectory(), "referenceData");
    ISHIKO_FAIL_IF_NEQ(environment.getTestOutputDirectory(), "output");
    ISHIKO_PASS();
}

void TestEnvironmentTests::GetTestDataDirectoryTest1(Test& test)
{
    TestEnvironment environment;

    boost::filesystem::path directory = environment.getTestDataDirectory();

    ISHIKO_FAIL_IF_NEQ(directory, "");
    ISHIKO_PASS();
}

void TestEnvironmentTests::GetTestDataDirectoryTest2(Test& test)
{
    TestEnvironment environment;
    environment.setTestDataDirectory("data");
    environment.setReferenceDataDirectory("reference");
    environment.setTestOutputDirectory("output");

    boost::filesystem::path directory = environment.getTestDataDirectory();

    ISHIKO_FAIL_IF_NEQ(directory, "data");
    ISHIKO_PASS();
}

void TestEnvironmentTests::GetTestDataDirectoryTest3(Test& test)
{
    try
    {
        TestEnvironment environment;
        environment.getTestDataDirectory("dummy");
    }
    catch (const TestException&)
    {
        ISHIKO_PASS();
    }
}

void TestEnvironmentTests::GetTestDataDirectoryTest4(Test& test)
{
    TestEnvironment environment;
    environment.setTestDataDirectory("id1", "path1");
    if (environment.getTestDataDirectory("id1") == "path1")
    {
        return ISHIKO_PASS();
    }
}

void TestEnvironmentTests::GetTestDataDirectoryTest5(Test& test)
{
    Ishiko::Process::CurrentEnvironment::Set("TestEnvironmentGetTestDataDirectoryTest3", "dummy");

    TestEnvironment environment;
    environment.setTestDataDirectory("id1", "$(TestEnvironmentGetTestDataDirectoryTest3)/path1");
    if (environment.getTestDataDirectory("id1") == "dummy/path1")
    {
        ISHIKO_PASS();
    }
}

void TestEnvironmentTests::GetTestDataPathTest1(Test& test)
{
    TestEnvironment environment;
    environment.setTestDataDirectory("data");

    boost::filesystem::path dataPath = environment.getTestDataPath("file");

    ISHIKO_FAIL_IF_NEQ(dataPath, "data/file");
    ISHIKO_PASS();
}

void TestEnvironmentTests::SetTestDataDirectoryTest1(Test& test)
{
    TestEnvironment parentEnvironment;
    parentEnvironment.setTestDataDirectory("parent");

    TestEnvironment environment(&parentEnvironment);
    environment.setTestDataDirectory("testData");

    ISHIKO_FAIL_IF_NEQ(parentEnvironment.getTestDataDirectory(), "parent");
    ISHIKO_FAIL_IF_NEQ(environment.getTestDataDirectory(), "parent/testData");
    ISHIKO_PASS();
}

void TestEnvironmentTests::GetReferenceDataDirectoryTest1(Test& test)
{
    TestEnvironment environment;

    boost::filesystem::path directory = environment.getReferenceDataDirectory();
    
    ISHIKO_FAIL_IF_NEQ(directory, "");
    ISHIKO_PASS();
}

void TestEnvironmentTests::GetReferenceDataDirectoryTest2(Test& test)
{
    TestEnvironment environment;
    environment.setTestDataDirectory("data");
    environment.setReferenceDataDirectory("reference");
    environment.setTestOutputDirectory("output");

    boost::filesystem::path directory = environment.getReferenceDataDirectory();

    ISHIKO_FAIL_IF_NEQ(directory, "reference");
    ISHIKO_PASS();
}

void TestEnvironmentTests::GetReferenceDataPathTest1(Test& test)
{
    TestEnvironment environment;
    environment.setReferenceDataDirectory("reference");

    boost::filesystem::path referencePath = environment.getReferenceDataPath("file");

    ISHIKO_FAIL_IF_NEQ(referencePath, "reference/file");
    ISHIKO_PASS();
}

void TestEnvironmentTests::SetReferenceDataDirectoryTest1(Test& test)
{
    TestEnvironment parentEnvironment;
    parentEnvironment.setReferenceDataDirectory("parent");

    TestEnvironment environment(&parentEnvironment);
    environment.setReferenceDataDirectory("referenceData");

    ISHIKO_FAIL_IF_NEQ(parentEnvironment.getReferenceDataDirectory(), "parent");
    ISHIKO_FAIL_IF_NEQ(environment.getReferenceDataDirectory(), "parent/referenceData");
    ISHIKO_PASS();
}

void TestEnvironmentTests::GetTestOutputDirectoryTest1(Test& test)
{
    TestEnvironment environment;

    boost::filesystem::path directory = environment.getTestOutputDirectory();

    ISHIKO_FAIL_IF_NEQ(directory, "");
    ISHIKO_PASS();
}

void TestEnvironmentTests::GetTestOutputDirectoryTest2(Test& test)
{
    TestEnvironment environment;
    environment.setTestDataDirectory("data");
    environment.setReferenceDataDirectory("reference");
    environment.setTestOutputDirectory("output");

    boost::filesystem::path directory = environment.getTestOutputDirectory();

    ISHIKO_FAIL_IF_NEQ(directory, "output");
    ISHIKO_PASS();
}

void TestEnvironmentTests::GetTestOutputPathTest1(Test& test)
{
    TestEnvironment environment;
    environment.setTestOutputDirectory("output");

    boost::filesystem::path outputPath = environment.getTestOutputPath("file");

    ISHIKO_FAIL_IF_NEQ(outputPath, "output/file");
    ISHIKO_PASS();
}

void TestEnvironmentTests::SetTestOutputDirectoryTest1(Test& test)
{
    TestEnvironment parentEnvironment;
    parentEnvironment.setTestOutputDirectory("parent");

    TestEnvironment environment(&parentEnvironment);
    environment.setTestOutputDirectory("output");

    ISHIKO_FAIL_IF_NEQ(parentEnvironment.getTestOutputDirectory(), "parent");
    ISHIKO_FAIL_IF_NEQ(environment.getTestOutputDirectory(), "parent/output");
    ISHIKO_PASS();
}
