/*
    Copyright (c) 2005-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_TESTFRAMEWORK_CORE_TESTENVIRONMENT_H_
#define _ISHIKO_TESTFRAMEWORK_CORE_TESTENVIRONMENT_H_

#include <boost/filesystem/path.hpp>
#include <boost/optional.hpp>
#include <map>

namespace Ishiko
{
namespace Tests
{

class TestEnvironment
{
public:
    TestEnvironment();
    TestEnvironment(const TestEnvironment* parent);
    ~TestEnvironment() noexcept = default;
    static const TestEnvironment& DefaultTestEnvironment();

    // This function is equivalent to calling getTestDataDirectory("(default)")
    // and exists to avoid the need to give a name to the test data
    // directory unnecessarily.
    boost::filesystem::path getTestDataDirectory() const;
    boost::filesystem::path getTestDataDirectory(const std::string& id) const;
    boost::filesystem::path getTestDataPath(const boost::filesystem::path& path) const;
    // Sets the default test data directory. The path argument
    // can contain environment variables by using the $(...) notation.
    // This is equivalent to calling setTestDataDirectory("(default)", path)
    // and exists to avoid the need to give a name to the test data
    // directory unnecessarily.
    void setTestDataDirectory(const boost::filesystem::path& path);
    // Adds or updates a path in the list of test data directories. The path argument
    // can contain environment variables by using the $(...) notation.
    void setTestDataDirectory(const std::string& id, const boost::filesystem::path& path);

    boost::filesystem::path getReferenceDataDirectory() const;
    boost::filesystem::path getReferenceDataDirectory(const std::string& id) const;
    boost::filesystem::path getReferenceDataPath(const boost::filesystem::path& path) const;
    // Sets the default reference data directory. The path argument
    // can contain environment variables by using the $(...) notation.
    void setReferenceDataDirectory(const boost::filesystem::path& path);
    void setReferenceDataDirectory(const std::string& id, const boost::filesystem::path& path);

    boost::filesystem::path getTestOutputDirectory() const;
    boost::filesystem::path getTestOutputDirectory(const std::string& id) const;
    boost::filesystem::path getTestOutputPath(const boost::filesystem::path& path) const;
    // Sets the default test output directory. The path argument
    // can contain environment variables by using the $(...) notation.
    void setTestOutputDirectory(const boost::filesystem::path& path);
    void setTestOutputDirectory(const std::string& id, const boost::filesystem::path& path);

private:
    const TestEnvironment* m_parent;
    std::map<std::string, boost::filesystem::path> m_testDataDirectories;
    std::map<std::string, boost::filesystem::path> m_referenceDataDirectories;
    std::map<std::string, boost::filesystem::path> m_testOutputDirectories;
};

}
}

#endif
