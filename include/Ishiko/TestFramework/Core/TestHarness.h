/*
    Copyright (c) 2006-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTFRAMEWORK_CORE_TESTHARNESS_H_
#define _ISHIKO_TESTFRAMEWORK_CORE_TESTHARNESS_H_

#include "TestConfiguration.h"
#include "TestEnvironment.h"
#include "TestSequence.h"
#include "TopTestSequence.h"
#include "TestApplicationReturnCodes.h"
#include <string>

namespace Ishiko
{
namespace Tests
{

class TestHarness
{
public:
	explicit TestHarness(const std::string& title);
	virtual ~TestHarness() noexcept = default;

	int run();

	TestEnvironment& environment();

	TestSequence& tests();

private:
    void prepareOutputDirectory();
	int runTests();
    void printDetailedResults();
    void printSummary();

private:
	TestEnvironment m_environment;
    TopTestSequence m_topSequence;
    bool m_timestampOutputDirectory;
};

}
}

#endif
