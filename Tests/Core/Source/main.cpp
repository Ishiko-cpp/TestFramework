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

#include "TestEnvironmentTests/TestEnvironmentTests.h"
#include "TestNumberTests.h"
#include "TestTests/TestTests.h"
#include "TestSequenceTests/TestSequenceTests.h"
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
    theTests.append<TestSequenceTests>();
    theTests.append<FileComparisonTestTests>();
    theTests.append<ConsoleApplicationTestTests>();
    theTests.append<HeapAllocationErrorsTestTests>();
    theTests.append<TestSetupActionsTests>();
    theTests.append<TestTeardownActionsTests>();
    theTests.append<TestHarnessTests>();

    return theTestHarness.run();
}
