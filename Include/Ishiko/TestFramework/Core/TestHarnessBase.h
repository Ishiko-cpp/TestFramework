/*
	Copyright (c) 2006-2015 Xavier Leclercq

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

	return eConfigurationProblem;
}

template<class TestConfigurationClass, class TopSequenceClass>
TestEnvironment& TestHarnessBase<TestConfigurationClass, TopSequenceClass>::environment()
{
	return m_environment;
}

template<class TestConfigurationClass, class TopSequenceClass>
TestSequence& TestHarnessBase<TestConfigurationClass, TopSequenceClass>::appendTestSequence(const std::string& name)
{
	// m_topSequence takes ownership
	return *(new TestSequence(name, m_topSequence));
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

        size_t passed = 0;
        size_t failed = 0;
        size_t total = 0;
        m_topSequence.result().getPassRate(passed, failed, total);
		if (!m_topSequence.passed())
		{
			std::cout << "Test Suite FAILED!!!" << " (" 
                << passed << " passed, "
                << failed << " failed, "
                << total << " total)" << std::endl;
			return eTestFailure;
		}
		else
		{
			std::cout << "Test Suite passed" << " ("
                << passed << " passed, "
                << failed << " failed, "
                << total << " total)" << std::endl;
			return eOk;
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
