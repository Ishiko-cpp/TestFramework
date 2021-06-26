/*
    Copyright (c) 2007-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "JUnitXMLWriterTests.h"
#include "TestEnvironmentTests/TestEnvironmentTests.h"
#include "TestNumberTests.h"
#include "TestTests.h"
#include "TestMacrosFormatterTests.h"
#include "TestMacrosTests.h"
#include "TestSequenceTests.h"
#include "FileComparisonTestTests/FileComparisonTestTests.h"
#include "ConsoleApplicationTestTests/ConsoleApplicationTestTests.h"
#include "HeapAllocationErrorsTestTests/HeapAllocationErrorsTestTests.h"
#include "TestSetupActionsTests/TestSetupActionsTests.h"
#include "TestTeardownActionsTests/TestTeardownActionsTests.h"
#include "TestHarnessTests.h"
#include "Ishiko/TestFramework/TestFrameworkCore.h"
#include <boost/filesystem/operations.hpp>

using namespace Ishiko::Tests;
using namespace boost::filesystem;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("IshikoTestFrameworkCore");

    theTestHarness.environment().setTestDataDirectory("../../TestData");
    theTestHarness.environment().setTestOutputDirectory("../../TestOutput");
    create_directories("../../TestOutput");
    theTestHarness.environment().setReferenceDataDirectory("../../ReferenceData");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<TestEnvironmentTests>();
    theTests.append<TestNumberTests>();
    theTests.append<TestTests>();
    theTests.append<TestMacrosFormatterTests>();
    theTests.append<TestMacrosTests>();
    theTests.append<TestSequenceTests>();
    theTests.append<FileComparisonTestTests>();
    theTests.append<ConsoleApplicationTestTests>();
    theTests.append<HeapAllocationErrorsTestTests>();
    theTests.append<TestSetupActionsTests>();
    theTests.append<TestTeardownActionsTests>();
    theTests.append<JUnitXMLWriterTests>();
    theTests.append<TestHarnessTests>();

    return theTestHarness.run();
}
