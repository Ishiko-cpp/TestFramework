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
    virtual ~TestEnvironment() noexcept = default;
    static const TestEnvironment& DefaultTestEnvironment();

    // This function is equivalent to calling getTestDataDirectory("(default)")
    // and exists to avoid the need to give a name to the test data
    // directory unnecessarily.
    virtual const boost::filesystem::path& getTestDataDirectory() const;
    // Sets the default test data directory. The path argument
    // can contain environment variables by using the $(...) notation.
    // This is equivalent to calling setTestDataDirectory("(default)", path)
    // and exists to avoid the need to give a name to the test data
    // directory unnecessarily.
    virtual void setTestDataDirectory(const boost::filesystem::path& path);
    virtual const boost::filesystem::path& getTestDataDirectory(const std::string& id) const;
    // Adds or updates a path in the list of test data directories. The path argument
    // can contain environment variables by using the $(...) notation.
    virtual void setTestDataDirectory(const std::string& id, const boost::filesystem::path& path);

    virtual const boost::filesystem::path& getReferenceDataDirectory() const;
    // Sets the default reference data directory. The path argument
    // can contain environment variables by using the $(...) notation.
    virtual void setReferenceDataDirectory(const boost::filesystem::path& path);

    virtual const boost::filesystem::path& getTestOutputDirectory() const;
    // Sets the default test output directory. The path argument
    // can contain environment variables by using the $(...) notation.
    virtual void setTestOutputDirectory(const boost::filesystem::path& path);

private:
    const TestEnvironment* m_parent;
    std::map<std::string, boost::filesystem::path> m_testDataDirectories;
    boost::optional<boost::filesystem::path> m_referenceDataDirectory;
    boost::optional<boost::filesystem::path> m_testOutputDirectory;
};

}
}

#endif
