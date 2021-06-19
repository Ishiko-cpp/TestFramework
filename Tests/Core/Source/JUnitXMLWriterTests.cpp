/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#include "JUnitXMLWriterTests.h"
#include "Ishiko/TestFramework/Core/JUnitXMLFile.h"

using namespace Ishiko::Tests;

JUnitXMLWriterTests::JUnitXMLWriterTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "JUnitXMLWriter tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void JUnitXMLWriterTests::ConstructorTest1(Test& test)
{
    JUnitXMLWriter junitXMLFile;

    ISHTF_PASS();
}
