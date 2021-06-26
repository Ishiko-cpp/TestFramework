/*
    Copyright (c) 2005-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTFRAMEWORK_CORE_TEST_H_
#define _ISHIKO_TESTFRAMEWORK_CORE_TEST_H_

#include "TestNumber.h"
#include "TestResult.h"
#include "TestEnvironment.h"
#include "TestSetupAction.h"
#include "TestTeardownAction.h"
#include <functional>
#include <string>
#include <vector>
#include <memory>

namespace Ishiko
{
namespace Tests
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
    Test(const TestNumber& number, const std::string& name, const TestEnvironment& environment);
    Test(const TestNumber& number, const std::string& name, TestResult result);
    Test(const TestNumber& number, const std::string& name, TestResult result, const TestEnvironment& environment);
    Test(const TestNumber& number, const std::string& name, std::function<void(Test& test)> runFct);
    Test(const TestNumber& number, const std::string& name, std::function<void(Test& test)> runFct,
        const TestEnvironment& environment);
    virtual ~Test() noexcept = default;

    const TestNumber& number() const;
    virtual void setNumber(const TestNumber& number);
    const std::string& name() const;

    TestResult result() const;
    void setResult(TestResult result);
    bool passed() const;
    virtual void getPassRate(size_t& unknown, size_t& passed, size_t& passedButMemoryLeaks, size_t& exception,
        size_t& failed, size_t& total) const;
    void abort(const char* file, int line);
    void abortIf(bool condition, const char* file, int line);
    void fail(const char* file, int line);
    void fail(const std::string& message, const char* file, int line);
    void failIf(bool condition, const char* file, int line);
    void pass();

    const TestEnvironment& environment() const;
    TestEnvironment& environment();

    virtual void run();

    virtual void addSetupAction(std::shared_ptr<TestSetupAction> action);
    virtual void addTeardownAction(std::shared_ptr<TestTeardownAction> action);

    virtual void traverse(std::function<void(const Test& test)> function) const;

    Observers& observers();

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
    TestEnvironment m_environment;
    bool m_memoryLeakCheck;
    std::vector<std::shared_ptr<TestSetupAction>> m_setupActions;
    std::vector<std::shared_ptr<TestTeardownAction>> m_teardownActions;
    Observers m_observers;
    std::function<void(Test& test)> m_runFct;
};

}
}

#endif
