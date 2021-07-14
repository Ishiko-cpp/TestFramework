/*
    Copyright (c) 2005-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_CORE_TESTSEQUENCE_H_
#define _ISHIKO_TESTS_CORE_TESTSEQUENCE_H_

#include "Test.h"
#include <vector>

namespace Ishiko
{
namespace Tests
{

class TestSequence : public Test
{
public:
    TestSequence(const TestNumber& number, const std::string& name);
    TestSequence(const TestNumber& number, const std::string& name, const TestEnvironment& environment);

    const Test& operator[](size_t pos) const;

    size_t size() const noexcept;

    void append(std::shared_ptr<Test> test);

    template <class TestClass, typename... Args>
    TestClass& append(Args&&... args);

    void setNumber(const TestNumber& number) override;
    
    void getPassRate(size_t& unknown, size_t& passed, size_t& passedButMemoryLeaks, size_t& exception, size_t& failed,
        size_t& total) const override;

    void traverse(std::function<void(const Test& test)> function) const override;

protected:
    void doRun() override;

private:
    class ItemsObserver : public Observer
    {
    public:
        ItemsObserver(TestSequence& sequence);

        void onLifecycleEvent(const Test& source, EEventType type) override;
        void onCheckFailed(const Test& source, const std::string& message, const char* file, int line) override;
        void onExceptionThrown(const Test& source, std::exception_ptr exception) override;

    private:
        TestSequence& m_sequence;
    };

    std::vector<std::shared_ptr<Test>> m_tests;
    std::shared_ptr<ItemsObserver> m_itemsObserver;
};

template <class TestClass, typename... Args>
TestClass& TestSequence::append(Args&&... args)
{
    // The test number is a dummy that will be replaced immediately by the append function
    std::shared_ptr<TestClass> newTest = std::make_shared<TestClass>(TestNumber(1), std::forward<Args>(args)..., environment());
    append(newTest);
    return *newTest;
}

}
}

#endif
