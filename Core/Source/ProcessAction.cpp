/*
	Copyright (c) 2016 Xavier Leclercq

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

#include "ProcessAction.h"
#include "TestException.h"

namespace Ishiko
{
namespace TestFramework
{

ProcessAction::ProcessAction(const std::string& commandLine, 
                             EMode mode)
    : m_commandLine(commandLine), m_processHandle(INVALID_HANDLE_VALUE),
    m_mode(mode)
{
}

ProcessAction::~ProcessAction()
{
    if (m_processHandle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_processHandle);
    }
}

void ProcessAction::setup()
{
    STARTUPINFOA startupInfo;
    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);

    PROCESS_INFORMATION processInfo;
    ZeroMemory(&processInfo, sizeof(processInfo));

    if (!CreateProcessA(NULL, const_cast<char*>(m_commandLine.c_str()),
        NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo))
    {
        throw TestException("ProcessAction::setup failed to execute: " + m_commandLine);
    }

    m_processHandle = processInfo.hProcess;

    CloseHandle(processInfo.hThread);
}

void ProcessAction::teardown()
{
    if (m_mode == eTerminate)
    {
        TerminateProcess(m_processHandle, 0);
    }

    WaitForSingleObject(m_processHandle, INFINITE);

    CloseHandle(m_processHandle);
    m_processHandle = INVALID_HANDLE_VALUE;
}

}
}
