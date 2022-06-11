/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "TestCheck.hpp"

using namespace Ishiko;

TestCheck::TestCheck()
    : m_result(Result::failed)
{
}

TestCheck::Result TestCheck::result() const noexcept
{
    return m_result;
}
