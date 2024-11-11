// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_PROCESSACTION_HPP
#define GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_PROCESSACTION_HPP

#include "TestSetupAction.hpp"
#include "TestTeardownAction.hpp"
#include "Ishiko/Process/ChildProcess.hpp"
#include <string>
#include <memory>

namespace Ishiko
{

class ProcessAction : public TestSetupAction, public TestTeardownAction
{
public:
    typedef std::shared_ptr<ProcessAction> shared_ptr;

    enum EMode
    {
        eWaitForExit,
        eTerminate
    };

    ProcessAction(const std::string& commandLine, EMode mode);
    ~ProcessAction() override;

    void setup(const Test& test) override;
    void teardown() override;

private:
    std::string m_commandLine;
    EMode m_mode;
    ChildProcess m_processHandle;
};

}

#endif
