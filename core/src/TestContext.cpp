/*
    Copyright (c) 2005-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "TestContext.hpp"
#include "TestException.hpp"
#include <Ishiko/Process/CurrentEnvironment.h>

namespace Ishiko
{

TestContext::TestContext()
    : m_parent(nullptr)
{
    m_testDataDirectories["(default)"] = boost::filesystem::path();
    m_referenceDataDirectories["(default)"] = boost::filesystem::path();
    m_testOutputDirectories["(default)"] = boost::filesystem::path();
}

TestContext::TestContext(const TestContext* parent)
    : m_parent(parent)
{
}

const TestContext& TestContext::DefaultTestContext()
{
    static TestContext defaultContext;
    return defaultContext;
}

boost::filesystem::path TestContext::getTestDataDirectory() const
{
    return getTestDataDirectory("(default)");
}

boost::filesystem::path TestContext::getTestDataDirectory(const std::string& id) const
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


boost::filesystem::path TestContext::getTestDataPath(const boost::filesystem::path& path) const
{
    return getTestDataDirectory() / path;
}

void TestContext::setTestDataDirectory(const boost::filesystem::path& path)
{
    setTestDataDirectory("(default)", path);
}

void TestContext::setTestDataDirectory(const std::string& id,
    const boost::filesystem::path& path)
{
    std::string expandedPath = CurrentEnvironment::ExpandVariablesInString(path.string(),
        CurrentEnvironment::eDollarAndParentheses);

    m_testDataDirectories[id] = expandedPath;
}

boost::filesystem::path TestContext::getReferenceDataDirectory() const
{
    return getReferenceDataDirectory("(default)");
}

boost::filesystem::path TestContext::getReferenceDataDirectory(const std::string& id) const
{
    boost::filesystem::path result;
    std::map<std::string, boost::filesystem::path>::const_iterator it = m_referenceDataDirectories.find(id);
    if (m_parent)
    {
        if (it != m_referenceDataDirectories.end())
        {
            result = (m_parent->getReferenceDataDirectory(id) / it->second);
        }
        else
        {
            result = m_parent->getReferenceDataDirectory(id);
        }
    }
    else
    {
        if (it != m_referenceDataDirectories.end())
        {
            return it->second;
        }
        else
        {
            throw TestException("getReferenceDataDirectory: no directory found with id " + id);
        }
    }
    return result;
}

boost::filesystem::path TestContext::getReferenceDataPath(const boost::filesystem::path& path) const
{
    return getReferenceDataDirectory() / path;
}

void TestContext::setReferenceDataDirectory(const boost::filesystem::path& path)
{
    setReferenceDataDirectory("(default)", path);
}

void TestContext::setReferenceDataDirectory(const std::string& id, const boost::filesystem::path& path)
{
    std::string expandedPath = CurrentEnvironment::ExpandVariablesInString(path.string(),
        CurrentEnvironment::eDollarAndParentheses);

    m_referenceDataDirectories[id] = expandedPath;
}

boost::filesystem::path TestContext::getTestOutputDirectory() const
{
    return getTestOutputDirectory("(default)");
}

boost::filesystem::path TestContext::getTestOutputDirectory(const std::string& id) const
{
    boost::filesystem::path result;
    std::map<std::string, boost::filesystem::path>::const_iterator it = m_testOutputDirectories.find(id);
    if (m_parent)
    {
        if (it != m_testOutputDirectories.end())
        {
            result = (m_parent->getTestOutputDirectory(id) / it->second);
        }
        else
        {
            result = m_parent->getTestOutputDirectory(id);
        }
    }
    else
    {
        if (it != m_testOutputDirectories.end())
        {
            return it->second;
        }
        else
        {
            throw TestException("getTestOutputDirectory: no directory found with id " + id);
        }
    }
    return result;
}

boost::filesystem::path TestContext::getTestOutputPath(const boost::filesystem::path& path) const
{
    return getTestOutputDirectory() / path;
}

void TestContext::setTestOutputDirectory(const boost::filesystem::path& path)
{
    setTestOutputDirectory("(default)", path);
}

void TestContext::setTestOutputDirectory(const std::string& id, const boost::filesystem::path& path)
{
    std::string expandedPath = CurrentEnvironment::ExpandVariablesInString(path.string(),
        CurrentEnvironment::eDollarAndParentheses);

    m_testOutputDirectories[id] = expandedPath;
}

}
