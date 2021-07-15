/*
    Copyright (c) 2015-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_CORE_TESTEXCEPTION_H_
#define _ISHIKO_TESTS_CORE_TESTEXCEPTION_H_

#include <stdexcept>

namespace Ishiko
{
namespace Tests
{

class TestException : public std::runtime_error
{
public:
    TestException(const std::string& message);
};

}
}

#endif
