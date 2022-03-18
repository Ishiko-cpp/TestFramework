/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "ProcessAction.hpp"
#include "TestException.hpp"
#include <Ishiko/Process.h>

using namespace Ishiko::Process;

namespace Ishiko
{

ProcessAction::ProcessAction(const std::string& commandLine, 
                             EMode mode)
    : m_commandLine(commandLine), m_mode(mode)
{
}

ProcessAction::~ProcessAction()
{
}

void ProcessAction::setup()
{
    Error error(0);
    m_processHandle = ChildProcess::Spawn(m_commandLine, error);
    if (error)
    {
        throw TestException("ProcessAction::setup failed to execute: " + m_commandLine);
    }
}

void ProcessAction::teardown()
{
    if (m_mode == eTerminate)
    {
        m_processHandle.kill(0);
    }

    m_processHandle.waitForExit();
}

}
