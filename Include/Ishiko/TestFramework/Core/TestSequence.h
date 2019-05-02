/*
    Copyright (c) 2005-2019 Xavier Leclercq

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

#ifndef _ISHIKO_TESTFRAMEWORK_CORE_TESTSEQUENCE_H_
#define _ISHIKO_TESTFRAMEWORK_CORE_TESTSEQUENCE_H_

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

        void onEvent(const Test& source, EEventType type) override;

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
