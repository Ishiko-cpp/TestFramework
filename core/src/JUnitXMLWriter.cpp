/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "JUnitXMLWriter.hpp"

using namespace Ishiko;

JUnitXMLWriter::JUnitXMLWriter()
{
}

void JUnitXMLWriter::create(const boost::filesystem::path& path, Error& error)
{
    m_xmlWriter.create(path, error);
    m_xmlWriter.writeXMLDeclaration();
}

void JUnitXMLWriter::close()
{
    m_xmlWriter.close();
}

void JUnitXMLWriter::writeTestSuitesStart()
{
    m_xmlWriter.writeElementStart("testsuites");
}

void JUnitXMLWriter::writeTestSuitesEnd()
{
    m_xmlWriter.writeElementEnd();
}

void JUnitXMLWriter::writeTestSuiteStart(size_t tests)
{
    m_xmlWriter.writeElementStart("testsuite");
    m_xmlWriter.writeAttribute("tests", std::to_string(tests));
}

void JUnitXMLWriter::writeTestSuiteEnd()
{
    m_xmlWriter.writeElementEnd();
}

void JUnitXMLWriter::writeTestCaseStart(const std::string& classname, const std::string& name)
{
    m_xmlWriter.writeElementStart("testcase");
    m_xmlWriter.writeAttribute("classname", classname);
    m_xmlWriter.writeAttribute("name", name);
}

void JUnitXMLWriter::writeTestCaseEnd()
{
    m_xmlWriter.writeElementEnd();
}

void JUnitXMLWriter::writeTestFailureStart()
{
    m_xmlWriter.writeElementStart("failure");
}

void JUnitXMLWriter::writeTestFailureEnd()
{
    m_xmlWriter.writeElementEnd();
}
