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
