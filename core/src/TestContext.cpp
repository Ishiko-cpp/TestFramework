/*
    Copyright (c) 2005-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "TestContext.hpp"
#include "TestException.hpp"
#include "TestFrameworkErrorCategory.hpp"
#include <Ishiko/Process.hpp>

namespace Ishiko
{

TestContext::TestContext()
    : m_parent(nullptr)
{
    m_dataDirectories["(default)"] = boost::filesystem::path();
    m_referenceDirectories["(default)"] = boost::filesystem::path();
    m_outputDirectories["(default)"] = boost::filesystem::path();
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

boost::filesystem::path TestContext::getDataDirectory() const
{
    return getDataDirectory("(default)");
}

boost::filesystem::path TestContext::getDataDirectory(const std::string& id) const
{
    boost::filesystem::path result;
    std::map<std::string, boost::filesystem::path>::const_iterator it = m_dataDirectories.find(id);
    if (m_parent)
    {
        if (it != m_dataDirectories.end())
        {
            result = (m_parent->getDataDirectory(id) / it->second);
        }
        else
        {
            result = m_parent->getDataDirectory(id);
        }
    }
    else
    {
        if (it != m_dataDirectories.end())
        {
            return it->second;
        }
        else
        {
            throw TestException("getDataDirectory: no directory found with id " + id);
        }
    }
    return result;
}


boost::filesystem::path TestContext::getDataPath(const boost::filesystem::path& path) const
{
    return getDataDirectory() / path;
}

void TestContext::setDataDirectory(const boost::filesystem::path& path)
{
    setDataDirectory("(default)", path);
}

void TestContext::setDataDirectory(const std::string& id,
    const boost::filesystem::path& path)
{
    std::string expandedPath = CurrentEnvironment::ExpandVariablesInString(path.string(),
        CurrentEnvironment::SubstitutionFormat::DollarAndCurlyBrackets);

    m_dataDirectories[id] = expandedPath;
}

boost::filesystem::path TestContext::getReferenceDirectory() const
{
    return getReferenceDirectory("(default)");
}

boost::filesystem::path TestContext::getReferenceDirectory(const std::string& id) const
{
    boost::filesystem::path result;
    std::map<std::string, boost::filesystem::path>::const_iterator it = m_referenceDirectories.find(id);
    if (m_parent)
    {
        if (it != m_referenceDirectories.end())
        {
            result = (m_parent->getReferenceDirectory(id) / it->second);
        }
        else
        {
            result = m_parent->getReferenceDirectory(id);
        }
    }
    else
    {
        if (it != m_referenceDirectories.end())
        {
            return it->second;
        }
        else
        {
            throw TestException("getReferenceDirectory: no directory found with id " + id);
        }
    }
    return result;
}

boost::filesystem::path TestContext::getReferencePath(const boost::filesystem::path& path) const
{
    return getReferenceDirectory() / path;
}

void TestContext::setReferenceDirectory(const boost::filesystem::path& path)
{
    setReferenceDirectory("(default)", path);
}

void TestContext::setReferenceDirectory(const std::string& id, const boost::filesystem::path& path)
{
    std::string expandedPath = CurrentEnvironment::ExpandVariablesInString(path.string(),
        CurrentEnvironment::SubstitutionFormat::DollarAndCurlyBrackets);

    m_referenceDirectories[id] = expandedPath;
}

boost::filesystem::path TestContext::getOutputDirectory() const
{
    return getOutputDirectory("(default)");
}

boost::filesystem::path TestContext::getOutputDirectory(const std::string& id) const
{
    boost::filesystem::path result;
    std::map<std::string, boost::filesystem::path>::const_iterator it = m_outputDirectories.find(id);
    if (m_parent)
    {
        if (it != m_outputDirectories.end())
        {
            result = (m_parent->getOutputDirectory(id) / it->second);
        }
        else
        {
            result = m_parent->getOutputDirectory(id);
        }
    }
    else
    {
        if (it != m_outputDirectories.end())
        {
            return it->second;
        }
        else
        {
            throw TestException("getOutputDirectory: no directory found with id " + id);
        }
    }
    return result;
}

boost::filesystem::path TestContext::getOutputDirectory(const std::string& id, Error& error) const
{
    boost::filesystem::path result;
    std::map<std::string, boost::filesystem::path>::const_iterator it = m_outputDirectories.find(id);
    if (m_parent)
    {
        if (it != m_outputDirectories.end())
        {
            result = (m_parent->getOutputDirectory(id) / it->second);
        }
        else
        {
            result = m_parent->getOutputDirectory(id, error);
        }
    }
    else
    {
        if (it != m_outputDirectories.end())
        {
            return it->second;
        }
        else
        {
            Fail(error, TestFrameworkErrorCategory::Value::generic);
        }
    }
    return result;
}

boost::filesystem::path TestContext::getOutputPath(const boost::filesystem::path& path) const
{
    return getOutputDirectory() / path;
}

void TestContext::setOutputDirectory(const boost::filesystem::path& path)
{
    setOutputDirectory("(default)", path);
}

void TestContext::setOutputDirectory(const std::string& id, const boost::filesystem::path& path)
{
    std::string expandedPath = CurrentEnvironment::ExpandVariablesInString(path.string(),
        CurrentEnvironment::SubstitutionFormat::DollarAndCurlyBrackets);

    m_outputDirectories[id] = expandedPath;
}

}
