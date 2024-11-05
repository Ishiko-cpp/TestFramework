// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_CONSOLEAPPLICATIONTEST_HPP
#define GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_CONSOLEAPPLICATIONTEST_HPP

#include "FileComparisonTestCheck.hpp"
#include "Test.hpp"
#include <boost/filesystem.hpp>
#include <string>

namespace Ishiko
{
    class ConsoleApplicationTest : public Test
    {
    public:
        ConsoleApplicationTest(const TestNumber& number, const std::string& name, const std::string& commandLine,
            int expectedExitCode);
        ConsoleApplicationTest(const TestNumber& number, const std::string& name, const std::string& commandLine,
            int expectedExitCode, const TestContext& context);
        ConsoleApplicationTest(const TestNumber& number, const std::string& name, const std::string& command_line,
            std::function<void(int exit_code, ConsoleApplicationTest& test)> run_fct, const TestContext& context);

        void setStandardOutputFilePath(const boost::filesystem::path& path);
        void setStandardOutputReferenceFilePath(const boost::filesystem::path& path);

    protected:
        void doRun() override;

    private:
        std::string m_commandLine;
        bool m_checkExitCode;
        int m_expectedExitCode;
        FileComparisonTestCheck m_standardOutputTest;
        std::function<void(int exit_code, ConsoleApplicationTest& test)> m_run_fct;
    };
}

#endif
