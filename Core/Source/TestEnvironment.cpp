/*
    Copyright (c) 2005-2019 Xavier Leclercq

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

#include "TestEnvironment.h"
#include "TestException.h"
#include "Ishiko/Process/Environment.h"

namespace Ishiko
{
namespace Tests
{

TestEnvironment::TestEnvironment()
{
}

TestEnvironment::~TestEnvironment()
{
}

const TestEnvironment& TestEnvironment::defaultTestEnvironment()
{
    static TestEnvironment defaultEnvironment;
    return defaultEnvironment;
}

const boost::filesystem::path& TestEnvironment::getTestDataDirectory() const
{
    return getTestDataDirectory("(default)");
}

const boost::filesystem::path& TestEnvironment::getTestDataDirectory(const std::string& id) const
{
    std::map<std::string, boost::filesystem::path>::const_iterator it = m_testDataDirectories.find(id);
    if (it != m_testDataDirectories.end())
    {
        return it->second;
    }
    else
    {
        throw TestException("getTestDataDirectory: no directory found with id " + id);
    }
}

void TestEnvironment::setTestDataDirectory(const std::string& id, 
                                           const std::string& path)
{
    std::string expandedPath = Process::Environment::expandVariablesInString(
        path, Process::Environment::eDollarAndParentheses);

    m_testDataDirectories[id] = expandedPath;
}

void TestEnvironment::setTestDataDirectory(const std::string& path)
{
    setTestDataDirectory("(default)", path);
}

const boost::filesystem::path& TestEnvironment::getReferenceDataDirectory() const
{
    return m_referenceDataDirectory;
}

void TestEnvironment::setReferenceDataDirectory(const std::string& path)
{
    std::string expandedPath = Process::Environment::expandVariablesInString(
        path, Process::Environment::eDollarAndParentheses);

    m_referenceDataDirectory = expandedPath;
}

const boost::filesystem::path& TestEnvironment::getTestOutputDirectory() const
{
    return m_testOutputDirectory;
}

void TestEnvironment::setTestOutputDirectory(const std::string& path)
{
    std::string expandedPath = Process::Environment::expandVariablesInString(
        path, Process::Environment::eDollarAndParentheses);

    m_testOutputDirectory = expandedPath;
}

}
}
