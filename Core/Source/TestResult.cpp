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

#include "TestResult.h"
#include "Test.h"
#include "TestSequence.h"

namespace Ishiko
{
namespace Tests
{

TestResult::TestResult(const Test& test)
    : m_test(test), m_outcome(eUnknown)
{
}

TestResult::~TestResult() throw()
{
}

TestResult::EOutcome TestResult::outcome() const
{
    return m_outcome;
}

bool TestResult::passed() const
{
    return (m_outcome == ePassed);
}

void TestResult::setOutcome(EOutcome outcome)
{
    m_outcome = outcome;
}

void TestResult::getPassRate(size_t& unknown, size_t& passed, size_t& passedButMemoryLeaks, size_t& exception,
    size_t& failed, size_t& total) const
{
    const TestSequence* sequence = dynamic_cast<const TestSequence*>(&m_test);
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
                (*sequence)[i].result().getPassRate(u, p, pbml, e, f, t);
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
        switch (m_outcome) {
            case EOutcome::eUnknown:
                unknown = 1;
                break;

            case EOutcome::ePassed:
                passed = 1;
                break;

            case EOutcome::ePassedButMemoryLeaks:
                passedButMemoryLeaks = 1;
                break;

            case EOutcome::eException:
                exception = 1;
                break;

            case EOutcome::eFailed:
                failed = 1;
                break;
        }
    }
}

}
}
