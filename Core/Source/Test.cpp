/*
    Copyright (c) 2006-2019 Xavier Leclercq

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

#include "Test.h"
#include "TestSequence.h"
#include "DebugHeap.h"

namespace Ishiko
{
namespace Tests
{

Test::Test(const TestNumber& number, const std::string& name)
    : m_number(number), m_name(name), m_result(TestResult::eUnknown),
    m_environment(TestEnvironment::defaultTestEnvironment()), m_memoryLeakCheck(true)
{
}

Test::Test(const TestNumber& number, const std::string& name, const TestEnvironment& environment)
    : m_number(number), m_name(name), m_result(TestResult::eUnknown), m_environment(environment),
    m_memoryLeakCheck(true)
{
}

const TestNumber& Test::number() const
{
    return m_number;
}

void Test::setNumber(const TestNumber& number)
{
    m_number = number;
}

const std::string& Test::name() const
{
    return m_name;
}

const TestResult& Test::result() const
{
    return m_result;
}

bool Test::passed() const
{
    return (m_result == TestResult::ePassed);
}

void Test::getPassRate(size_t& unknown, size_t& passed, size_t& passedButMemoryLeaks, size_t& exception,
    size_t& failed, size_t& total) const
{
    const TestSequence* sequence = dynamic_cast<const TestSequence*>(this);
    if (sequence)
    {
        if (sequence->size() == 0)
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
            for (size_t i = 0; i < sequence->size(); ++i)
            {
                size_t u = 0;
                size_t p = 0;
                size_t pbml = 0;
                size_t e = 0;
                size_t f = 0;
                size_t t = 0;
                (*sequence)[i].getPassRate(u, p, pbml, e, f, t);
                unknown += u;
                passed += p;
                passedButMemoryLeaks += pbml;
                exception += e;
                failed += f;
                total += t;
            }
        }
    }
    else
    {
        unknown = 0;
        passed = 0;
        passedButMemoryLeaks = 0;
        exception = 0;
        failed = 0;
        total = 1;
        switch (m_result)
        {
            case TestResult::eUnknown:
                unknown = 1;
                break;

            case TestResult::ePassed:
                passed = 1;
                break;

            case TestResult::ePassedButMemoryLeaks:
                passedButMemoryLeaks = 1;
                break;

            case TestResult::eException:
                exception = 1;
                break;

            case TestResult::eFailed:
                failed = 1;
                break;
        }
    }
}
void Test::fail(const char* file, int line)
{
    m_result = TestResult::eFailed;
}

void Test::run()
{
    TestObserver::ptr observer = std::make_shared<TestObserver>();
    run(observer);
}

void Test::run(TestObserver::ptr& observer)
{
    notify(TestObserver::eTestStart, observer);

    setup();

    DebugHeap::HeapState heapStateBefore;

    TestResult result = TestResult::eFailed;
    try
    {
        result = doRun(observer);
    }
    catch (...)
    {
        result = TestResult::eException;
    }

    DebugHeap::HeapState heapStateAfter;

    if (m_memoryLeakCheck && (heapStateBefore.allocatedSize() != heapStateAfter.allocatedSize())
        && (result == TestResult::ePassed))
    {
        m_result = TestResult::ePassedButMemoryLeaks;
    }
    else
    {
        m_result = result;
    }

    teardown();

    notify(TestObserver::eTestEnd, observer);
}

void Test::addSetupAction(std::shared_ptr<TestSetupAction> action)
{
    m_setupActions.push_back(action);
}

void Test::addTeardownAction(std::shared_ptr<TestTeardownAction> action)
{
    m_teardownActions.push_back(action);
}

void Test::setup()
{
    for (size_t i = 0; i < m_setupActions.size(); ++i)
    {
        m_setupActions[i]->setup();
    }
}

void Test::teardown()
{
    for (size_t i = 0; i < m_teardownActions.size(); ++i)
    {
        m_teardownActions[i]->teardown();
    }
}

void Test::notify(TestObserver::EEventType type,
                  TestObserver::ptr& observer)
{
    if (observer)
    {
        observer->notify(type, *this);
    }
}

const TestEnvironment& Test::environment() const
{
    return m_environment;
}

}
}
