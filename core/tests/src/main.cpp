/*
    Copyright (c) 2007-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "FileComparisonTestCheckTests.hpp"
#include "JUnitXMLWriterTests.h"
#include "TestContextTests.hpp"
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
#include <Ishiko/Tests/Core.hpp>

using namespace Ishiko;
using namespace boost::filesystem;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("IshikoTestFrameworkCore");

    theTestHarness.context().setTestDataDirectory("../../data");
    theTestHarness.context().setTestOutputDirectory("../../output");
    theTestHarness.context().setReferenceDataDirectory("../../reference");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<TestContextTests>();
    theTests.append<TestNumberTests>();
    theTests.append<TestTests>();
    theTests.append<FileComparisonTestCheckTests>();
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
