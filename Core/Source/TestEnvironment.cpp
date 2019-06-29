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
    : m_parent(nullptr), m_referenceDataDirectory(boost::filesystem::path()),
    m_testOutputDirectory(boost::filesystem::path())
{
    m_testDataDirectories["(default)"] = boost::filesystem::path();
}

TestEnvironment::TestEnvironment(const TestEnvironment* parent)
    : m_parent(parent)
{
}

const TestEnvironment& TestEnvironment::DefaultTestEnvironment()
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
    else if (m_parent)
    {
        return m_parent->getTestDataDirectory(id);
    }
    else
    {
        throw TestException("getTestDataDirectory: no directory found with id " + id);
    }
}

void TestEnvironment::setTestDataDirectory(const std::string& id, 
                                           const boost::filesystem::path& path)
{
    std::string expandedPath = Process::Environment::expandVariablesInString(
        path.string(), Process::Environment::eDollarAndParentheses);

    m_testDataDirectories[id] = expandedPath;
}

void TestEnvironment::setTestDataDirectory(const boost::filesystem::path& path)
{
    setTestDataDirectory("(default)", path);
}

const boost::filesystem::path& TestEnvironment::getReferenceDataDirectory() const
{
    if (!m_referenceDataDirectory && m_parent)
    {
        return m_parent->getReferenceDataDirectory();
    }
    else
    {
        return *m_referenceDataDirectory;
    }
}

void TestEnvironment::setReferenceDataDirectory(const boost::filesystem::path& path)
{
    std::string expandedPath = Process::Environment::expandVariablesInString(
        path.string(), Process::Environment::eDollarAndParentheses);

    m_referenceDataDirectory = expandedPath;
}

const boost::filesystem::path& TestEnvironment::getTestOutputDirectory() const
{
    if (!m_testOutputDirectory && m_parent)
    {
        return m_parent->getTestOutputDirectory();
    }
    else
    {
        return *m_testOutputDirectory;
    }
}

void TestEnvironment::setTestOutputDirectory(const boost::filesystem::path& path)
{
    std::string expandedPath = Process::Environment::expandVariablesInString(
        path.string(), Process::Environment::eDollarAndParentheses);

    m_testOutputDirectory = expandedPath;
}

}
}
