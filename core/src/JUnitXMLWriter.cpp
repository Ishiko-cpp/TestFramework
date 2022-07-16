/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "JUnitXMLWriter.hpp"

using namespace Ishiko;

JUnitXMLWriter::JUnitXMLWriter()
    : m_atLeastOneTestSuite(false), m_atLeastOneTestCase(false)
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
    m_xmlWriter.increaseIndentation();
}

void JUnitXMLWriter::writeTestSuitesEnd()
{
    m_xmlWriter.decreaseIndentation();
    if (m_atLeastOneTestSuite)
    {
        m_xmlWriter.writeNewlineAndIndentation();
        m_atLeastOneTestSuite = false;
    }
    m_xmlWriter.writeElementEnd();
}

void JUnitXMLWriter::writeTestSuiteStart(size_t tests)
{
    m_atLeastOneTestSuite = true;
    m_xmlWriter.writeNewlineAndIndentation();
    m_xmlWriter.writeElementStart("testsuite");
    m_xmlWriter.writeAttribute("tests", std::to_string(tests));
    m_xmlWriter.increaseIndentation();
}

void JUnitXMLWriter::writeTestSuiteEnd()
{
    m_xmlWriter.decreaseIndentation();
    if (m_atLeastOneTestCase)
    {
        m_xmlWriter.writeNewlineAndIndentation();
        m_atLeastOneTestCase = false;
    }
    m_xmlWriter.writeElementEnd();
}

void JUnitXMLWriter::writeTestCaseStart(const std::string& classname, const std::string& name)
{
    m_atLeastOneTestCase = true;
    m_xmlWriter.writeElementStart("testcase");
    m_xmlWriter.writeAttribute("classname", classname);
    m_xmlWriter.writeAttribute("name", name);
}

void JUnitXMLWriter::writeTestCaseEnd()
{
    m_xmlWriter.writeElementEnd();
}

void JUnitXMLWriter::writeFailureStart()
{
    m_xmlWriter.writeElementStart("failure");
}

void JUnitXMLWriter::writeFailureEnd()
{
    m_xmlWriter.writeElementEnd();
}

void JUnitXMLWriter::writeSkippedStart()
{
    m_xmlWriter.writeElementStart("skipped");
}

void JUnitXMLWriter::writeSkippedEnd()
{
    m_xmlWriter.writeElementEnd();
}

void JUnitXMLWriter::writeText(const std::string& text)
{
    m_xmlWriter.writeText(text);
}
