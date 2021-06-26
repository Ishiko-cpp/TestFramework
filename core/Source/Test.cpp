/*
    Copyright (c) 2006-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#include "Test.h"
#include "TestSequence.h"
#include "DebugHeap.h"
#include <boost/filesystem/operations.hpp>

namespace Ishiko
{
namespace Tests
{

void Test::Observer::onLifecycleEvent(const Test& source, EEventType type)
{
}

void Test::Observer::onCheckFailed(const Test& source, const std::string& message, const char* file, int line)
{
}

void Test::Observer::onExceptionThrown(const Test& source, std::exception_ptr exception)
{
}

void Test::Observers::add(std::shared_ptr<Observer> observer)
{
    auto it = std::find_if(m_observers.begin(), m_observers.end(),
        [&observer](const std::pair<std::weak_ptr<Observer>, size_t>& o)
    {
        return (o.first.lock() == observer);
    }
    );
    if (it != m_observers.end())
    {
        ++it->second;
    }
    else
    {
        m_observers.push_back(std::pair<std::weak_ptr<Observer>, size_t>(observer, 1));
    }
}

void Test::Observers::remove(std::shared_ptr<Observer> observer)
{
    auto it = std::find_if(m_observers.begin(), m_observers.end(),
        [&observer](const std::pair<std::weak_ptr<Observer>, size_t>& o)
    {
        return (o.first.lock() == observer);
    }
    );
    if (it != m_observers.end())
    {
        --it->second;
        if (it->second == 0)
        {
            m_observers.erase(it);
        }
    }
}

void Test::Observers::notifyLifecycleEvent(const Test& source, Observer::EEventType type)
{
    for (std::pair<std::weak_ptr<Observer>, size_t>& o : m_observers)
    {
        std::shared_ptr<Observer> observer = o.first.lock();
        if (observer)
        {
            observer->onLifecycleEvent(source, type);
        }
        else
        {
            removeDeletedObservers();
        }
    }
}

void Test::Observers::notifyCheckFailed(const Test& source, const std::string& message, const char* file, int line)
{
    for (std::pair<std::weak_ptr<Observer>, size_t>& o : m_observers)
    {
        std::shared_ptr<Observer> observer = o.first.lock();
        if (observer)
        {
            observer->onCheckFailed(source, message, file, line);
        }
        else
        {
            removeDeletedObservers();
        }
    }
}

void Test::Observers::notifyExceptionThrown(const Test& source, std::exception_ptr exception)
{
    for (std::pair<std::weak_ptr<Observer>, size_t>& o : m_observers)
    {
        std::shared_ptr<Observer> observer = o.first.lock();
        if (observer)
        {
            observer->onExceptionThrown(source, exception);
        }
        else
        {
            removeDeletedObservers();
        }
    }
}

void Test::Observers::removeDeletedObservers()
{
    auto it = std::remove_if(m_observers.begin(), m_observers.end(),
        [](const std::pair<std::weak_ptr<Observer>, size_t>& o)
    {
        return o.first.expired();
    }
    );
    m_observers.erase(it, m_observers.end());
}

Test::Test(const TestNumber& number, const std::string& name)
    : m_number(number), m_name(name), m_result(TestResult::eUnknown),
    m_environment(&TestEnvironment::DefaultTestEnvironment()), m_memoryLeakCheck(true), m_runFct(0)
{
}

Test::Test(const TestNumber& number, const std::string& name, const TestEnvironment& environment)
    : m_number(number), m_name(name), m_result(TestResult::eUnknown), m_environment(&environment),
    m_memoryLeakCheck(true), m_runFct(0)
{
}

Test::Test(const TestNumber& number, const std::string& name, TestResult result)
    : m_number(number), m_name(name), m_result(result), m_environment(&TestEnvironment::DefaultTestEnvironment()),
    m_memoryLeakCheck(true), m_runFct(0)
{
}

Test::Test(const TestNumber& number, const std::string& name, TestResult result, const TestEnvironment& environment)
    : m_number(number), m_name(name), m_result(result), m_environment(&environment), m_memoryLeakCheck(true),
    m_runFct(0)
{
}

Test::Test(const TestNumber& number, const std::string& name, std::function<void(Test& test)> runFct)
    : m_number(number), m_name(name), m_result(TestResult::eUnknown),
    m_environment(&TestEnvironment::DefaultTestEnvironment()), m_memoryLeakCheck(true), m_runFct(runFct)
{
}

Test::Test(const TestNumber& number, const std::string& name, std::function<void(Test& test)> runFct,
    const TestEnvironment& environment)
    : m_number(number), m_name(name), m_result(TestResult::eUnknown), m_environment(&environment),
    m_memoryLeakCheck(true), m_runFct(runFct)
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

TestResult Test::result() const
{
    return m_result;
}

void Test::setResult(TestResult result)
{
    m_result = result;
}

bool Test::passed() const
{
    return (m_result == TestResult::ePassed);
}

void Test::getPassRate(size_t& unknown, size_t& passed, size_t& passedButMemoryLeaks, size_t& exception,
    size_t& failed, size_t& total) const
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

void Test::abort(const char* file, int line)
{
    fail(file, line);
    throw AbortException();
}

void Test::abortIf(bool condition, const char* file, int line)
{
    if (condition)
    {
        fail(file, line);
        throw AbortException();
    }
}

void Test::fail(const char* file, int line)
{
    fail("", file, line);
}

void Test::fail(const std::string& message, const char* file, int line)
{
    m_result = TestResult::eFailed;
    m_observers.notifyCheckFailed(*this, message, file, line);
}

void Test::failIf(bool condition, const char* file, int line)
{
    if (condition)
    {
        fail(file, line);
    }
}

void Test::pass()
{
    if (m_result == TestResult::eUnknown)
    {
        m_result = TestResult::ePassed;
    }
}

const TestEnvironment& Test::environment() const
{
    return m_environment;
}

TestEnvironment& Test::environment()
{
    return m_environment;
}

void Test::run()
{
    notify(Observer::eTestStart);

    setup();

    DebugHeap::HeapState heapStateBefore;

    try
    {
        doRun();
        if (m_result == TestResult::eUnknown)
        {
            // The function didn't fail but at no point did it mark the test as passed either so we consider this a
            // failure.
            fail("Test completed without being marked passed or failed", __FILE__, __LINE__);
        }
    }
    catch (const AbortException&)
    {
        // abort() was called, the exception is only used as a way to interrupt the test.
    }
    catch (...)
    {
        m_observers.notifyExceptionThrown(*this, std::current_exception());
        m_result = TestResult::eException;
    }

    DebugHeap::HeapState heapStateAfter;

    if (m_memoryLeakCheck && (heapStateBefore.allocatedSize() != heapStateAfter.allocatedSize())
        && (m_result == TestResult::ePassed))
    {
        m_result = TestResult::ePassedButMemoryLeaks;
    }

    teardown();

    notify(Observer::eTestEnd);
}

void Test::addSetupAction(std::shared_ptr<TestSetupAction> action)
{
    m_setupActions.push_back(action);
}

void Test::addTeardownAction(std::shared_ptr<TestTeardownAction> action)
{
    m_teardownActions.push_back(action);
}

void Test::traverse(std::function<void(const Test& test)> function) const
{
    function(*this);
}

Test::Observers& Test::observers()
{
    return m_observers;
}

void Test::setup()
{
    boost::filesystem::path outputDirectory = m_environment.getTestOutputDirectory();
    if (outputDirectory != "")
    {
        boost::filesystem::create_directories(outputDirectory);
    }

    for (size_t i = 0; i < m_setupActions.size(); ++i)
    {
        m_setupActions[i]->setup();
    }
}

void Test::doRun()
{
    if (m_runFct)
    {
        m_runFct(*this);
    }
}

void Test::teardown()
{
    for (size_t i = 0; i < m_teardownActions.size(); ++i)
    {
        m_teardownActions[i]->teardown();
    }
}

void Test::notify(Observer::EEventType type)
{
    m_observers.notifyLifecycleEvent(*this, type);
}

}
}
