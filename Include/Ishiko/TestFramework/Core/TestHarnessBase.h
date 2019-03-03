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

#ifndef _ISHIKO_TESTFRAMEWORK_CORE_TESTHARNESSBASE_H_
#define _ISHIKO_TESTFRAMEWORK_CORE_TESTHARNESSBASE_H_

#include "TestApplicationReturnCodes.h"
#include "TestSequence.h"
#include "TestProgressObserver.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <memory>

namespace Ishiko
{
namespace TestFramework
{

template<class TestConfigurationClass, class TopSequenceClass>
class TestHarnessBase
{
public:
	explicit TestHarnessBase(const std::string& title);
	virtual ~TestHarnessBase();

	int run();

	TestEnvironment& environment();

	TestSequence& appendTestSequence(const std::string& name);

protected:
	int runTests();

private:
	TestEnvironment m_environment;
	TopSequenceClass m_topSequence;
};

template<class TestConfigurationClass, class TopSequenceClass>
TestHarnessBase<TestConfigurationClass, TopSequenceClass>::TestHarnessBase(const std::string& title)
	: m_environment(TestEnvironment::defaultTestEnvironment()), m_topSequence(title, m_environment)
{
}

template<class TestConfigurationClass, class TopSequenceClass>
TestHarnessBase<TestConfigurationClass, TopSequenceClass>::~TestHarnessBase()
{
}

template<class TestConfigurationClass, class TopSequenceClass>
int TestHarnessBase<TestConfigurationClass, TopSequenceClass>::run()
{
	std::cout << "Test Suite: " << m_topSequence.name() << std::endl;

	// Run the tests
	int result = runTests();

	return result;
}

template<class TestConfigurationClass, class TopSequenceClass>
TestEnvironment& TestHarnessBase<TestConfigurationClass, TopSequenceClass>::environment()
{
	return m_environment;
}

template<class TestConfigurationClass, class TopSequenceClass>
TestSequence& TestHarnessBase<TestConfigurationClass, TopSequenceClass>::appendTestSequence(const std::string& name)
{
    return m_topSequence.append<TestSequence>(name);
}

template<class TestConfigurationClass, class TopSequenceClass>
int TestHarnessBase<TestConfigurationClass, TopSequenceClass>::runTests()
{
	try
	{
		TestProgressObserver::ptr progressObserver = std::make_shared<TestProgressObserver>();
		std::cout << std::endl;
		m_topSequence.run(progressObserver);
		std::cout << std::endl;

        size_t unknown = 0;
        size_t passed = 0;
        size_t passedButMemoryLeaks = 0;
        size_t exception = 0;
        size_t failed = 0;
        size_t total = 0;
        m_topSequence.result().getPassRate(unknown, passed, passedButMemoryLeaks, exception, failed, total);
		if (!m_topSequence.passed())
		{
            std::cout << "Pass rate: " << std::fixed << std::setprecision(2) << (100 * (double)passed / (double)total)
                << "% (" << unknown << " unknown, "
                << passed << " passed, "
                << passedButMemoryLeaks << " passed but with memory leaks, "
                << exception << " threw exceptions, "
                << failed << " failed, "
                << total << " total)" << std::endl;
            std::cout << std::endl;
            std::cout << "Test Suite FAILED!!!" << std::endl;

			return eTestFailure;
		}
		else
		{
            std::cout << "Pass rate: " << std::fixed << std::setprecision(2) << (100 * (double)passed / (double)total)
                << "% (" << unknown << " unknown, "
                << passed << " passed, "
                << passedButMemoryLeaks << " passed but with memory leaks, "
                << exception << " threw exceptions, "
                << failed << " failed, "
                << total << " total)" << std::endl;

            std::cout << std::endl;
            std::cout << "Test Suite passed" << std::endl;

			return eOK;
		}
	}
	catch (...)
	{
		return eException;
	}
}

}
}

#endif
