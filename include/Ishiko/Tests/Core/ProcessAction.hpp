/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTS_CORE_PROCESSACTION_HPP_
#define _ISHIKO_CPP_TESTS_CORE_PROCESSACTION_HPP_

#include "TestSetupAction.hpp"
#include "TestTeardownAction.hpp"
#include "Ishiko/Process/ChildProcess.h"
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

    void setup() override;
    void teardown() override;

private:
    std::string m_commandLine;
    EMode m_mode;
    Process::ChildProcess m_processHandle;
};

}

#endif
