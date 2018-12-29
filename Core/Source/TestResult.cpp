/*
	Copyright (c) 2005-2017 Xavier Leclercq

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
namespace TestFramework
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

void TestResult::getPassRate(size_t& passed, size_t& failed, size_t& total) const
{
    const TestSequence* sequence = dynamic_cast<const TestSequence*>(&m_test);
    if (sequence)
    {
        for (size_t i = 0; i < sequence->size(); ++i)
        {
            size_t p = 0;
            size_t f = 0;
            size_t t = 0;
            (*sequence)[i].result().getPassRate(p, f, t);
            passed += p;
            failed += f;
            total += t;
        }
    }
    else
    {
        passed = 0;
        failed = 0;
        total = 1;
        switch (m_outcome) {
            case EOutcome::ePassed:
                passed = 1;
                break;

            case EOutcome::eFailed:
                failed = 1;
                break;
        }
    }
}

}
}
