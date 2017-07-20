/*
    Copyright (c) 2017 Xavier Leclercq

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

#include "SQLiteDatabaseDumpComparisonTestTests.h"
#include "Ishiko/TestFramework/SQLiteTests/SQLiteDatabaseDumpComparisonTest.h"

void AddSQLiteDatabaseDumpComparisonTestTests(Ishiko::TestFramework::TestHarness& theTestHarness)
{
    Ishiko::TestFramework::TestSequence& comparisonTestSequence =
        theTestHarness.appendTestSequence("SQLiteDatabaseDumpComparisonTest tests");

    new Ishiko::TestFramework::HeapAllocationErrorsTest("Creation test 1",
        SQLiteDatabaseDumpComparisonTestCreationTest1, comparisonTestSequence);
    new Ishiko::TestFramework::HeapAllocationErrorsTest("Creation test 2",
        SQLiteDatabaseDumpComparisonTestCreationTest2, comparisonTestSequence);

    new Ishiko::TestFramework::HeapAllocationErrorsTest("run success test 1",
        SQLiteDatabaseDumpComparisonTestRunSuccessTest1, comparisonTestSequence);

    new Ishiko::TestFramework::HeapAllocationErrorsTest("run failure test 1",
        SQLiteDatabaseDumpComparisonTestRunFailureTest1, comparisonTestSequence);
}

Ishiko::TestFramework::TestResult::EOutcome SQLiteDatabaseDumpComparisonTestCreationTest1()
{
    Ishiko::TestFramework::SQLiteDatabaseDumpComparisonTest test(
        Ishiko::TestFramework::TestNumber(), "SQLiteDatabaseDumpComparisonTestCreationTest1");
    return Ishiko::TestFramework::TestResult::ePassed;
}

Ishiko::TestFramework::TestResult::EOutcome SQLiteDatabaseDumpComparisonTestCreationTest2Helper(Ishiko::TestFramework::SQLiteDatabaseDumpComparisonTest& test)
{
    return Ishiko::TestFramework::TestResult::ePassed;
}

Ishiko::TestFramework::TestResult::EOutcome SQLiteDatabaseDumpComparisonTestCreationTest2()
{
    Ishiko::TestFramework::SQLiteDatabaseDumpComparisonTest test(
        Ishiko::TestFramework::TestNumber(), "SQLiteDatabaseDumpComparisonTestCreationTest2", 
        SQLiteDatabaseDumpComparisonTestCreationTest2Helper);
    return Ishiko::TestFramework::TestResult::ePassed;
}

Ishiko::TestFramework::TestResult::EOutcome SQLiteDatabaseDumpComparisonTestRunSuccessTest1Helper(Ishiko::TestFramework::SQLiteDatabaseDumpComparisonTest& test)
{
    return Ishiko::TestFramework::TestResult::ePassed;
}

Ishiko::TestFramework::TestResult::EOutcome SQLiteDatabaseDumpComparisonTestRunSuccessTest1()
{
    Ishiko::TestFramework::SQLiteDatabaseDumpComparisonTest test(
        Ishiko::TestFramework::TestNumber(), "SQLiteDatabaseDumpComparisonTestRunSuccessTest1",
        SQLiteDatabaseDumpComparisonTestRunSuccessTest1Helper);

    test.run();

    return test.result().outcome();
}

Ishiko::TestFramework::TestResult::EOutcome SQLiteDatabaseDumpComparisonTestRunFailureTest1Helper(Ishiko::TestFramework::SQLiteDatabaseDumpComparisonTest& test)
{
    return Ishiko::TestFramework::TestResult::eFailed;
}

Ishiko::TestFramework::TestResult::EOutcome SQLiteDatabaseDumpComparisonTestRunFailureTest1()
{
    Ishiko::TestFramework::SQLiteDatabaseDumpComparisonTest test(
        Ishiko::TestFramework::TestNumber(), "SQLiteDatabaseDumpComparisonTestRunFailureTest1",
        SQLiteDatabaseDumpComparisonTestRunSuccessTest1Helper);

    test.run();

    if (test.result().outcome() == Ishiko::TestFramework::TestResult::eFailed)
    {
        return Ishiko::TestFramework::TestResult::ePassed;
    }
    else
    {
        return Ishiko::TestFramework::TestResult::eFailed;
    }
}
