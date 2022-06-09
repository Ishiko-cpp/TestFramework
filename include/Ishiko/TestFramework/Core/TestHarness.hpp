/*
    Copyright (c) 2006-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTHARNESS_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTHARNESS_HPP_

#include "TestConfiguration.hpp"
#include "TestContext.hpp"
#include "TestSequence.hpp"
#include "TopTestSequence.hpp"
#include "TestApplicationReturnCodes.hpp"
#include <boost/optional.hpp>
#include <Ishiko/Configuration.hpp>
#include <string>

namespace Ishiko
{

class TestHarness
{
public:
    class CommandLineSpecification : public Ishiko::CommandLineSpecification
    {
    public:
        CommandLineSpecification();
    };

    class Configuration
    {
    public:
        Configuration(const Ishiko::Configuration& configuration);

        const boost::optional<std::string>& junitXMLTestReport() const;

    private:
        boost::optional<std::string> m_junitXMLTestReport;
    };

	explicit TestHarness(const std::string& title);
    TestHarness(const std::string& title, const Configuration& configuration);
	virtual ~TestHarness() noexcept = default;

	int run();

    TestContext& context();

	TestSequence& tests();

private:
    void prepareOutputDirectory();
	int runTests();
    void printDetailedResults();
    void printSummary();
    void writeJUnitXMLTestReport(const std::string& path);

private:
    boost::optional<std::string> m_junitXMLTestReport;
    TestContext m_context;
    TopTestSequence m_topSequence;
    bool m_timestampOutputDirectory;
};

}

#endif
