/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "JUnitXMLWriterTests.h"
#include "Ishiko/Tests/Core/JUnitXMLWriter.h"

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
