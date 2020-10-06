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

#include "SQLiteDatabaseDumpComparisonTest.h"
#include "Ishiko/SQLite/sqlite3.h"

namespace Ishiko
{
namespace TestFramework
{

SQLiteDatabaseDumpComparisonTest::SQLiteDatabaseDumpComparisonTest(const TestNumber& number, 
                                                                   const std::string& name)
    : Test(number, name), m_runFct(0), m_comparisonTest(TestNumber(), "Comparison")
{
}

SQLiteDatabaseDumpComparisonTest::SQLiteDatabaseDumpComparisonTest(const TestNumber& number,
                                                                   const std::string& name,
                                                                   TestResult::EOutcome (*runFct)(SQLiteDatabaseDumpComparisonTest& test))
    : Test(number, name), m_runFct(runFct), m_comparisonTest(TestNumber(), "Comparison")
{
}

SQLiteDatabaseDumpComparisonTest::~SQLiteDatabaseDumpComparisonTest()
{
}

const boost::filesystem::path& SQLiteDatabaseDumpComparisonTest::databaseFilePath() const
{
    return m_databaseFilePath;
}

void SQLiteDatabaseDumpComparisonTest::setDatabaseFilePath(const boost::filesystem::path& path)
{
    m_databaseFilePath = path;
}

TestResult::EOutcome SQLiteDatabaseDumpComparisonTest::doRun(TestObserver::ptr& observer)
{
    TestResult::EOutcome result = TestResult::eFailed;

    if (m_runFct)
    {
        result = m_runFct(*this);
    }
    else
    {
        result = TestResult::ePassed;
    }

    if (result == TestResult::ePassed)
    {
        result = TestResult::eFailed;

        if (!m_databaseFilePath.empty())
        {
            dumpDatabse(m_databaseFilePath);

            m_comparisonTest.run();
            result = m_comparisonTest.result().outcome();
        }
    }

    return result;
}

void SQLiteDatabaseDumpComparisonTest::dumpDatabse(const boost::filesystem::path& databasePath)
{
    sqlite3* db = 0;
    sqlite3_open(databasePath.string().c_str(), &db);

    char* sql = "SELECT name FROM sqlite_master WHERE type='table';";
    sqlite3_exec(db, sql, 0, 0, 0);

    sqlite3_close(db);
}

}
}
