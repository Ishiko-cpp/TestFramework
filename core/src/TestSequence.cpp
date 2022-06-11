/*
    Copyright (c) 2005-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "TestSequence.hpp"

namespace Ishiko
{

TestSequence::TestSequence(const TestNumber& number, const std::string& name)
    : Test(number, name), m_itemsObserver(std::make_shared<ItemsObserver>(*this))
{
}

TestSequence::TestSequence(const TestNumber& number, const std::string& name, const TestContext& context)
    : Test(number, name, context), m_itemsObserver(std::make_shared<ItemsObserver>(*this))
{
}

const Test& TestSequence::operator[](size_t pos) const
{
    return *(m_tests[pos]);
}

size_t TestSequence::size() const noexcept
{
    return m_tests.size();
}

void TestSequence::append(std::shared_ptr<Test> test)
{
    // We need to update the number of the test
    if (m_tests.size() == 0)
    {
        test->setNumber(number().getDeeperNumber());
    }
    else
    {
        TestNumber newNumber = m_tests.back()->number();
        test->setNumber(++newNumber);
    }

    m_tests.push_back(test);
    test->observers().add(m_itemsObserver);
}

void TestSequence::setNumber(const TestNumber& number)
{
    Test::setNumber(number);
    TestNumber deeperNumber = number.getDeeperNumber();
    for (std::shared_ptr<Test>& test : m_tests)
    {
        test->setNumber(deeperNumber++);
    }
}

void TestSequence::getPassRate(size_t& unknown, size_t& passed, size_t& passedButMemoryLeaks, size_t& exception,
    size_t& failed, size_t& skipped, size_t& total) const
{
    if (m_tests.size() == 0)
    {
        // Special case. If the sequence is empty we consider it to be a single unknown test case. If we didn't do
        // that this case would go unnoticed in the returned values.
        unknown = 1;
        passed = 0;
        passedButMemoryLeaks = 0;
        exception = 0;
        failed = 0;
        total = 1;
    }
    else
    {
        for (size_t i = 0; i < m_tests.size(); ++i)
        {
            size_t u = 0;
            size_t p = 0;
            size_t pbml = 0;
            size_t e = 0;
            size_t f = 0;
            size_t s = 0;
            size_t t = 0;
            m_tests[i]->getPassRate(u, p, pbml, e, f, s, t);
            unknown += u;
            passed += p;
            passedButMemoryLeaks += pbml;
            exception += e;
            failed += f;
            skipped += s;
            total += t;
        }
    }
}

void TestSequence::traverse(std::function<void(const Test& test)> function) const
{
    function(*this);
    for (size_t i = 0; i < m_tests.size(); ++i)
    {
        m_tests[i]->traverse(function);
    }
}

void TestSequence::addToJUnitXMLTestReport(JUnitXMLWriter& writer) const
{
    // We don't usually print sequence test results as the report is supposed to be a flat list of all tests but if the
    // sequence is empty we print it else it would go unnoticed. By design empty test sequences do not really make
    //  sense and should not be present in test suites.
    if (m_tests.empty())
    {
        writer.writeTestCaseStart("unknown", name());
        if (!passed())
        {
            writer.writeTestFailureStart();
            writer.writeTestFailureEnd();
        }
        writer.writeTestCaseEnd();
    }
}

void TestSequence::doRun()
{
    // By default the outcome is unknown
    TestResult result = TestResult::unknown;

    for (size_t i = 0; i < m_tests.size(); ++i)
    {
        Test& test = *m_tests[i];
        
        test.run();

        // Update the result
        TestResult newResult = test.result();
        if (i == 0)
        {
            // The first test determines the initial value of the result
            result = newResult;
        }
        else if (result == TestResult::unknown)
        {
            // If the current sequence outcome is unknown it can only get worse and be set
            // to exception or failed (if the outcome we are adding is exception or 
            // failed)
            if ((newResult == TestResult::failed) || (newResult == TestResult::exception))
            {
                result = newResult;
            }
        }
        else if (result == TestResult::passed)
        {
            // If the current sequence outcome is passed it stays at this state only if the
            // result we are adding is passed or skipped, else it will be 'unknown', 
            // 'passedButMemoryLeaks', 'exception' or 'failed'.
            // depending on the outcome of the result we are adding.
            if (newResult != TestResult::skipped)
            {
                result = newResult;
            }
        }
        else if (result == TestResult::passedButMemoryLeaks)
        {
            // It can only stay at this state if the test is passed or ePassedButMemoryLeaks.
            if ((newResult == TestResult::failed) ||
                (newResult == TestResult::exception) ||
                (newResult == TestResult::unknown))
            {
                result = newResult;
            }
        }
        else if (result == TestResult::exception)
        {
            // It can only get worse. This happens only if the outcome is 'failed'
            if (newResult == TestResult::failed)
            {
                result = newResult;
            }
        }
        else if (result == TestResult::skipped)
        {
            result = newResult;
        }
    }

    setResult(result);
}

TestSequence::ItemsObserver::ItemsObserver(TestSequence& sequence)
    : m_sequence(sequence)
{
}

void TestSequence::ItemsObserver::onLifecycleEvent(const Test& source, EEventType type)
{
    m_sequence.observers().notifyLifecycleEvent(source, type);
}

void TestSequence::ItemsObserver::onCheckFailed(const Test& source, const std::string& message, const char* file,
    int line)
{
    m_sequence.observers().notifyCheckFailed(source, message, file, line);
}

void TestSequence::ItemsObserver::onExceptionThrown(const Test& source, std::exception_ptr exception)
{
    m_sequence.observers().notifyExceptionThrown(source, exception);
}

}
