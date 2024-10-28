// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_TEST_HPP
#define GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_TEST_HPP

#include "JUnitXMLWriter.hpp"
#include "TestCheck.hpp"
#include "TestContext.hpp"
#include "TestNumber.hpp"
#include "TestResult.hpp"
#include "TestSetupAction.hpp"
#include "TestTeardownAction.hpp"
#include <Ishiko/Time.hpp>
#include <functional>
#include <string>
#include <vector>
#include <memory>

namespace Ishiko
{

/// This class represents a test.

/// It is the abstract base class for the various test classes.
class Test
{
public:
    class Observer
    {
    public:
        enum EEventType
        {
            eTestStart,
            eTestEnd
        };

        virtual ~Observer() noexcept = default;

        virtual void onLifecycleEvent(const Test& source, EEventType type);
        virtual void onCheckFailed(const Test& source, const std::string& message, const char* file, int line);
        virtual void onExceptionThrown(const Test& source, std::exception_ptr exception);
    };

    class Observers final
    {
    public:
        void add(std::shared_ptr<Observer> observer);
        void remove(std::shared_ptr<Observer> observer);

        void notifyLifecycleEvent(const Test& source, Observer::EEventType type);
        void notifyCheckFailed(const Test& source, const std::string& message, const char* file, int line);
        void notifyExceptionThrown(const Test& source, std::exception_ptr exception);

    private:
        void removeDeletedObservers();

    private:
        std::vector<std::pair<std::weak_ptr<Observer>, size_t>> m_observers;
    };

    /// Constructor.
    /// @param number The number of the test.
    /// @param name The name of the test.
    Test(const TestNumber& number, const std::string& name);
    Test(const TestNumber& number, const std::string& name, const TestContext& context);
    Test(const TestNumber& number, const std::string& name, TestResult result);
    Test(const TestNumber& number, const std::string& name, TestResult result, const TestContext&  context);
    Test(const TestNumber& number, const std::string& name, std::function<void(Test& test)> runFct);
    Test(const TestNumber& number, const std::string& name, std::function<void(Test& test)> runFct,
        const TestContext& context);
    virtual ~Test() noexcept = default;

    const TestNumber& number() const;
    virtual void setNumber(const TestNumber& number);
    const std::string& name() const;

    TestResult result() const;
    void setResult(TestResult result);
    bool passed() const;
    bool skipped() const;
    virtual void getPassRate(size_t& unknown, size_t& passed, size_t& passedButMemoryLeaks, size_t& exception,
        size_t& failed, size_t& skipped, size_t& total) const;
    void abort(const char* file, int line);
    void abort(const std::string& message, const char* file, int line);
    void abortIf(bool condition, const char* file, int line);
    void fail(const char* file, int line);
    void fail(const std::string& message, const char* file, int line);
    void failIf(bool condition, const char* file, int line);
    void pass();
    void skip();

    void appendCheck(std::shared_ptr<TestCheck> check);

    const TestContext& context() const;
    TestContext& context();

    virtual void run();

    virtual void addSetupAction(std::shared_ptr<TestSetupAction> action);
    virtual void addTeardownAction(std::shared_ptr<TestTeardownAction> action);

    virtual void traverse(std::function<void(const Test& test)> function) const;

    Observers& observers();

    virtual void addToJUnitXMLTestReport(JUnitXMLWriter& writer) const;

protected:
    virtual void setup();
    virtual void doRun();
    virtual void teardown();
    virtual void notify(Observer::EEventType type);
    
private:
    class AbortException
    {
    };

    TestNumber m_number;
    std::string m_name;
    TestResult m_result;
    TestContext m_context;
    std::vector<std::shared_ptr<TestCheck>> m_checks;
    bool m_memoryLeakCheck;
    SystemTime m_executionStartTime;
    SystemTime m_executionEndTime;
    std::vector<std::shared_ptr<TestSetupAction>> m_setupActions;
    std::vector<std::shared_ptr<TestTeardownAction>> m_teardownActions;
    Observers m_observers;
    std::function<void(Test& test)> m_runFct;
};

}

#endif
