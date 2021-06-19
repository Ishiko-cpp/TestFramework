/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#include "JUnitXMLFileTests.h"
#include "Ishiko/TestFramework/Core/JUnitXMLFile.h"

using namespace Ishiko::Tests;

JUnitXMLFileTests::JUnitXMLFileTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "JUnitXMLFile tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void JUnitXMLFileTests::ConstructorTest1(Test& test)
{
    JUnitXMLFile junitXMLFile;

    ISHTF_PASS();
}
