/*
    Copyright (c) 2007-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
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
    append<HeapAllocationErrorsTest>("getTestDataDirectory test 2", GetTestDataDirectoryTest2);
    append<HeapAllocationErrorsTest>("getTestDataDirectory test 3", GetTestDataDirectoryTest3);
    append<HeapAllocationErrorsTest>("getTestDataDirectory test 4", GetTestDataDirectoryTest4);
    append<HeapAllocationErrorsTest>("getTestDataPath test 1", GetTestDataPathTest1);
    append<HeapAllocationErrorsTest>("setTestDataDirectory test 1", SetTestDataDirectoryTest1);
    append<HeapAllocationErrorsTest>("getReferenceDataDirectory test 1", GetReferenceDataDirectoryTest1);
    append<HeapAllocationErrorsTest>("setReferenceDataDirectory test 1", SetReferenceDataDirectoryTest1);
    append<HeapAllocationErrorsTest>("getTestOutputDirectory test 1", GetTestOutputDirectoryTest1);
    append<HeapAllocationErrorsTest>("setTestOutputDirectory test 1", SetTestOutputDirectoryTest1);
}

void TestEnvironmentTests::ConstructorTest1(Test& test)
{
    TestEnvironment environment;

    ISHTF_FAIL_IF_NEQ(environment.getTestDataDirectory(), "");
    ISHTF_FAIL_IF_NEQ(environment.getReferenceDataDirectory(), "");
    ISHTF_FAIL_IF_NEQ(environment.getTestOutputDirectory(), "");
    ISHTF_PASS();
}

void TestEnvironmentTests::ConstructorTest2(Test& test)
{
    TestEnvironment parentEnvironment;
    TestEnvironment environment(&parentEnvironment);

    ISHTF_FAIL_IF_NEQ(environment.getTestDataDirectory(), "");
    ISHTF_FAIL_IF_NEQ(environment.getReferenceDataDirectory(), "");
    ISHTF_FAIL_IF_NEQ(environment.getTestOutputDirectory(), "");
    ISHTF_PASS();
}

void TestEnvironmentTests::ConstructorTest3(Test& test)
{
    TestEnvironment parentEnvironment;
    parentEnvironment.setTestDataDirectory("data");
    parentEnvironment.setReferenceDataDirectory("referenceData");
    parentEnvironment.setTestOutputDirectory("output");

    TestEnvironment environment(&parentEnvironment);

    ISHTF_FAIL_IF_NEQ(environment.getTestDataDirectory(), "data");
    ISHTF_FAIL_IF_NEQ(environment.getReferenceDataDirectory(), "referenceData");
    ISHTF_FAIL_IF_NEQ(environment.getTestOutputDirectory(), "output");
    ISHTF_PASS();
}

void TestEnvironmentTests::GetTestDataDirectoryTest2(Test& test)
{
    try
    {
        TestEnvironment environment;
        environment.getTestDataDirectory("dummy");
    }
    catch (const TestException&)
    {
        ISHTF_PASS();
    }
}

void TestEnvironmentTests::GetTestDataDirectoryTest3(Test& test)
{
    TestEnvironment environment;
    environment.setTestDataDirectory("id1", "path1");
    if (environment.getTestDataDirectory("id1") == "path1")
    {
        return ISHTF_PASS();
    }
}

void TestEnvironmentTests::GetTestDataDirectoryTest4(Test& test)
{
    Ishiko::Process::CurrentEnvironment::Set("TestEnvironmentGetTestDataDirectoryTest3", "dummy");

    TestEnvironment environment;
    environment.setTestDataDirectory("id1", "$(TestEnvironmentGetTestDataDirectoryTest3)/path1");
    if (environment.getTestDataDirectory("id1") == "dummy/path1")
    {
        ISHTF_PASS();
    }
}

void TestEnvironmentTests::GetTestDataPathTest1(Test& test)
{
    TestEnvironment environment;
    environment.setTestDataDirectory("data");

    boost::filesystem::path dataPath = environment.getTestDataPath("file");

    ISHTF_FAIL_IF_NEQ(dataPath, "data/file");
    ISHTF_PASS();
}

void TestEnvironmentTests::SetTestDataDirectoryTest1(Test& test)
{
    TestEnvironment parentEnvironment;
    parentEnvironment.setTestDataDirectory("parent");

    TestEnvironment environment(&parentEnvironment);
    environment.setTestDataDirectory("testData");

    ISHTF_FAIL_IF_NEQ(parentEnvironment.getTestDataDirectory(), "parent");
    ISHTF_FAIL_IF_NEQ(environment.getTestDataDirectory(), "parent/testData");
    ISHTF_PASS();
}

void TestEnvironmentTests::GetReferenceDataDirectoryTest1(Test& test)
{
    TestEnvironment environment;

    boost::filesystem::path directory = environment.getReferenceDataDirectory();
    
    ISHTF_FAIL_IF_NEQ(directory, "");
    ISHTF_PASS();
}

void TestEnvironmentTests::SetReferenceDataDirectoryTest1(Test& test)
{
    TestEnvironment parentEnvironment;
    parentEnvironment.setReferenceDataDirectory("parent");

    TestEnvironment environment(&parentEnvironment);
    environment.setReferenceDataDirectory("referenceData");

    ISHTF_FAIL_IF_NEQ(parentEnvironment.getReferenceDataDirectory(), "parent");
    ISHTF_FAIL_IF_NEQ(environment.getReferenceDataDirectory(), "parent/referenceData");
    ISHTF_PASS();
}

void TestEnvironmentTests::GetTestOutputDirectoryTest1(Test& test)
{
    TestEnvironment environment;

    boost::filesystem::path directory = environment.getTestOutputDirectory();

    ISHTF_FAIL_IF_NEQ(directory, "");
    ISHTF_PASS();
}

void TestEnvironmentTests::SetTestOutputDirectoryTest1(Test& test)
{
    TestEnvironment parentEnvironment;
    parentEnvironment.setTestOutputDirectory("parent");

    TestEnvironment environment(&parentEnvironment);
    environment.setTestOutputDirectory("output");

    ISHTF_FAIL_IF_NEQ(parentEnvironment.getTestOutputDirectory(), "parent");
    ISHTF_FAIL_IF_NEQ(environment.getTestOutputDirectory(), "parent/output");
    ISHTF_PASS();
}
