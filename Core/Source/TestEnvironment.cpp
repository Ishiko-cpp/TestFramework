/*
    Copyright (c) 2005-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#include "TestEnvironment.h"
#include "TestException.h"
#include <Ishiko/Process/CurrentEnvironment.h>

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

boost::filesystem::path TestEnvironment::getTestDataDirectory() const
{
    return getTestDataDirectory("(default)");
}

boost::filesystem::path TestEnvironment::getTestDataDirectory(const std::string& id) const
{
    boost::filesystem::path result;
    std::map<std::string, boost::filesystem::path>::const_iterator it = m_testDataDirectories.find(id);
    if (m_parent)
    {
        if (it != m_testDataDirectories.end())
        {
            result = (m_parent->getTestDataDirectory(id) / it->second);
        }
        else
        {
            result = m_parent->getTestDataDirectory(id);
        }
    }
    else
    {
        if (it != m_testDataDirectories.end())
        {
            return it->second;
        }
        else
        {
            throw TestException("getTestDataDirectory: no directory found with id " + id);
        }
    }
    return result;
}

void TestEnvironment::setTestDataDirectory(const std::string& id, 
                                           const boost::filesystem::path& path)
{
    std::string expandedPath = Process::CurrentEnvironment::ExpandVariablesInString(path.string(),
        Process::CurrentEnvironment::eDollarAndParentheses);

    m_testDataDirectories[id] = expandedPath;
}

void TestEnvironment::setTestDataDirectory(const boost::filesystem::path& path)
{
    setTestDataDirectory("(default)", path);
}

boost::filesystem::path TestEnvironment::getReferenceDataDirectory() const
{
    boost::filesystem::path result;
    if (m_parent)
    {
        if (m_referenceDataDirectory)
        {
            result = (m_parent->getReferenceDataDirectory() / *m_referenceDataDirectory);
        }
        else
        {
            result = m_parent->getReferenceDataDirectory();
        }
    }
    else if (m_referenceDataDirectory)
    {
        result = *m_referenceDataDirectory;
    }
    return result;
}

void TestEnvironment::setReferenceDataDirectory(const boost::filesystem::path& path)
{
    std::string expandedPath = Process::CurrentEnvironment::ExpandVariablesInString(path.string(),
        Process::CurrentEnvironment::eDollarAndParentheses);

    m_referenceDataDirectory = expandedPath;
}

boost::filesystem::path TestEnvironment::getTestOutputDirectory() const
{
    boost::filesystem::path result;
    if (m_parent)
    {
        if (m_testOutputDirectory)
        {
            result = (m_parent->getTestOutputDirectory() / *m_testOutputDirectory);
        }
        else
        {
            result = m_parent->getTestOutputDirectory();
        }
    }
    else if (m_testOutputDirectory)
    {
        result = *m_testOutputDirectory;
    }
    return result;
}

void TestEnvironment::setTestOutputDirectory(const boost::filesystem::path& path)
{
    std::string expandedPath = Process::CurrentEnvironment::ExpandVariablesInString(path.string(),
        Process::CurrentEnvironment::eDollarAndParentheses);

    m_testOutputDirectory = expandedPath;
}

}
}
