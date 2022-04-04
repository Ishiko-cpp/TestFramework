/*
    Copyright (c) 2006-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTS_CORE_TESTHARNESS_HPP_
#define _ISHIKO_CPP_TESTS_CORE_TESTHARNESS_HPP_

#include "TestConfiguration.hpp"
#include "TestContext.hpp"
#include "TestSequence.hpp"
#include "TopTestSequence.hpp"
#include "TestApplicationReturnCodes.hpp"
#include <string>

namespace Ishiko
{

class TestHarness
{
public:
	explicit TestHarness(const std::string& title);
	virtual ~TestHarness() noexcept = default;

	int run();

    TestContext& context();

	TestSequence& tests();

private:
    void prepareOutputDirectory();
	int runTests();
    void printDetailedResults();
    void printSummary();

private:
    TestContext m_context;
    TopTestSequence m_topSequence;
    bool m_timestampOutputDirectory;
};

}

#endif
