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
#include "DebugHeap.h"

namespace Ishiko
{
namespace Tests
{

Test::Test(const TestNumber& number, const std::string& name)
    : m_number(number), m_name(name), m_result(*this), m_environment(TestEnvironment::defaultTestEnvironment()),
    m_memoryLeakCheck(true)
{
}

Test::Test(const TestNumber& number, const std::string& name, const TestEnvironment& environment)
    : m_number(number), m_name(name), m_result(*this), m_environment(environment), m_memoryLeakCheck(true)
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
    return m_result.passed();
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

    TestResult::EOutcome outcome = TestResult::eFailed;
    try
    {
        outcome = doRun(observer);
    }
    catch (...)
    {
        outcome = TestResult::eException;
    }

    DebugHeap::HeapState heapStateAfter;

    if (m_memoryLeakCheck && (heapStateBefore.allocatedSize() != heapStateAfter.allocatedSize())
        && (outcome == TestResult::ePassed))
    {
        m_result.setOutcome(TestResult::ePassedButMemoryLeaks);
    }
    else
    {
        m_result.setOutcome(outcome);
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
