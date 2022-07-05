/*
    Copyright (c) 2006-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "Test.hpp"
#include "TestSequence.hpp"
#include "DebugHeap.hpp"
#include <boost/filesystem/operations.hpp>
#include <boost/range/algorithm.hpp>

using namespace Ishiko;

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
    auto it = boost::range::find_if(m_observers,
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
    auto it = boost::range::find_if(m_observers,
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
    : m_number(number), m_name(name), m_result(TestResult::unknown),
    m_context(&TestContext::DefaultTestContext()), m_memoryLeakCheck(true), m_runFct(0)
{
}

Test::Test(const TestNumber& number, const std::string& name, const TestContext& context)
    : m_number(number), m_name(name), m_result(TestResult::unknown), m_context(&context),
    m_memoryLeakCheck(true), m_runFct(0)
{
}

Test::Test(const TestNumber& number, const std::string& name, TestResult result)
    : m_number(number), m_name(name), m_result(result), m_context(&TestContext::DefaultTestContext()),
    m_memoryLeakCheck(true), m_runFct(0)
{
}

Test::Test(const TestNumber& number, const std::string& name, TestResult result, const TestContext& context)
    : m_number(number), m_name(name), m_result(result), m_context(&context), m_memoryLeakCheck(true), m_runFct(0)
{
}

Test::Test(const TestNumber& number, const std::string& name, std::function<void(Test& test)> runFct)
    : m_number(number), m_name(name), m_result(TestResult::unknown),
    m_context(&TestContext::DefaultTestContext()), m_memoryLeakCheck(true), m_runFct(runFct)
{
}

Test::Test(const TestNumber& number, const std::string& name, std::function<void(Test& test)> runFct,
    const TestContext& context)
    : m_number(number), m_name(name), m_result(TestResult::unknown), m_context(&context), m_memoryLeakCheck(true),
    m_runFct(runFct)
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
    return (m_result == TestResult::passed);
}

bool Test::skipped() const
{
    return (m_result == TestResult::skipped);
}

void Test::getPassRate(size_t& unknown, size_t& passed, size_t& passedButMemoryLeaks, size_t& exception,
    size_t& failed, size_t& skipped, size_t& total) const
{
    unknown = 0;
    passed = 0;
    passedButMemoryLeaks = 0;
    exception = 0;
    failed = 0;
    skipped = 0;
    total = 1;
    switch (m_result)
    {
        case TestResult::unknown:
            unknown = 1;
            break;

        case TestResult::passed:
            passed = 1;
            break;

        case TestResult::passedButMemoryLeaks:
            passedButMemoryLeaks = 1;
            break;

        case TestResult::exception:
            exception = 1;
            break;

        case TestResult::failed:
            failed = 1;
            break;

        case TestResult::skipped:
            skipped = 1;
            break;
    }
}

void Test::abort(const char* file, int line)
{
    fail(file, line);
    throw AbortException();
}

void Test::abort(const std::string& message, const char* file, int line)
{
    fail(message, file, line);
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
    m_result = TestResult::failed;
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
    if (m_result == TestResult::unknown)
    {
        m_result = TestResult::passed;
    }
}

void Test::skip()
{
    if (m_result == TestResult::unknown)
    {
        m_result = TestResult::skipped;
    }
    throw AbortException();
}

void Test::appendCheck(std::shared_ptr<TestCheck> check)
{
    m_checks.push_back(check);
}

const TestContext& Test::context() const
{
    return m_context;
}

TestContext& Test::context()
{
    return m_context;
}

void Test::run()
{
    m_executionStartTime = SystemTime::Now();
    notify(Observer::eTestStart);

    setup();

    DebugHeap::HeapState heapStateBefore;

    try
    {
        doRun();
        if (m_result == TestResult::unknown)
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
        m_result = TestResult::exception;
    }

    DebugHeap::HeapState heapStateAfter;

    if (m_memoryLeakCheck && (heapStateBefore.allocatedSize() != heapStateAfter.allocatedSize())
        && (m_result == TestResult::passed))
    {
        m_result = TestResult::passedButMemoryLeaks;
    }

    teardown();

    m_executionEndTime = SystemTime::Now();
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

void Test::addToJUnitXMLTestReport(JUnitXMLWriter& writer) const
{
    writer.writeTestCaseStart("unknown", m_name);
    switch (m_result)
    {
    case TestResult::passed:
        // Do nothing
        break;

    case TestResult::failed:
        {
            // TODO: this assume we enforce consistency between test failure and check->result(). Need to enforce that
            // in Test::run().
            bool atLeastOneTestCheckFailed = false;
            for (const std::shared_ptr<TestCheck>& check : m_checks)
            {
                if (check->result() != TestCheck::Result::passed)
                {
                    writer.writeFailureStart();
                    check->addToJUnitXMLTestReport(writer);
                    writer.writeFailureEnd();

                    atLeastOneTestCheckFailed = true;
                }
            }
            // If the failure is not due to one the checks, we still want to make sure we mark the test as failed.
            if (!atLeastOneTestCheckFailed)
            {
                writer.writeFailureStart();
                writer.writeFailureEnd();
            }
        }
        break;

    case TestResult::skipped:
        writer.writeSkippedStart();
        writer.writeSkippedEnd();
        break;

    default:
        writer.writeFailureStart();
        writer.writeFailureEnd();
    }
    writer.writeTestCaseEnd();
}

void Test::setup()
{
    boost::filesystem::path outputDirectory = m_context.getOutputDirectory();
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
