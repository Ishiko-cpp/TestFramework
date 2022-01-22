/*
    Copyright (c) 2005-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "TestNumber.hpp"

namespace Ishiko
{
namespace Tests
{

TestNumber::TestNumber()
{
}

TestNumber::TestNumber(int major)
{
    m_number.push_back(major);
}

TestNumber::TestNumber(int major, int minor)
{
    m_number.push_back(major);
    m_number.push_back(minor);
}

size_t TestNumber::depth() const
{
    return m_number.size();
}

int TestNumber::part(size_t i) const
{
    return m_number[i];
}

bool TestNumber::operator ==(const TestNumber& other) const
{
    return (m_number == other.m_number);
}

bool TestNumber::operator !=(const TestNumber& other) const
{
    return (m_number != other.m_number);
}

TestNumber& TestNumber::operator ++()
{
    if (!m_number.empty())
    {
        ++m_number.back();
    }
    return *this;
}

TestNumber TestNumber::operator ++(int)
{
    TestNumber result(*this);
    if (!m_number.empty())
    {
        ++m_number.back();
    }
    return result;
}

TestNumber TestNumber::getDeeperNumber() const
{
    TestNumber result = *this;
    result.m_number.push_back(1);
    return result;
}

}
}
