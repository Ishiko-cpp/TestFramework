/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_JUNITXMLWRITER_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_JUNITXMLWRITER_HPP_

#include <boost/filesystem.hpp>
#include <Ishiko/XML.hpp>

namespace Ishiko
{

class JUnitXMLWriter
{
public:
    JUnitXMLWriter();
    void create(const boost::filesystem::path& path, Error& error);
    void close();

    void writeTestSuitesStart();
    void writeTestSuitesEnd();

private:
    XMLWriter m_xmlWriter;
};

}

#endif
