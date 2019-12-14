/*
    Copyright (c) 2007-2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "TestEnvironmentTests.h"
#include "Ishiko/Process/Environment.h"

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
    append<HeapAllocationErrorsTest>("setTestDataDirectory test 1", SetTestDataDirectoryTest1);
    append<HeapAllocationErrorsTest>("setReferenceDataDirectory test 1", SetReferenceDataDirectoryTest1);
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

void TestEnvironmentTests::GetTestDataDirectoryTest1(Test& test)
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

void TestEnvironmentTests::GetTestDataDirectoryTest2(Test& test)
{
    TestEnvironment environment;
    environment.setTestDataDirectory("id1", "path1");
    if (environment.getTestDataDirectory("id1") == "path1")
    {
        return ISHTF_PASS();
    }
}

void TestEnvironmentTests::GetTestDataDirectoryTest3(Test& test)
{
    Ishiko::Process::Environment::set("TestEnvironmentGetTestDataDirectoryTest3", "dummy");

    TestEnvironment environment;
    environment.setTestDataDirectory("id1", "$(TestEnvironmentGetTestDataDirectoryTest3)/path1");
    if (environment.getTestDataDirectory("id1") == "dummy/path1")
    {
        ISHTF_PASS();
    }
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
