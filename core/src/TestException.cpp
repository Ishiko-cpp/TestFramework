/*
    Copyright (c) 2015-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "TestException.hpp"

namespace Ishiko
{
namespace Tests
{

TestException::TestException(const std::string& message)
    : std::runtime_error(message)
{
}

}
}
