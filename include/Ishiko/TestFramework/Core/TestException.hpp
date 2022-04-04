/*
    Copyright (c) 2015-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTEXCEPTION_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTEXCEPTION_HPP_

#include <stdexcept>

namespace Ishiko
{

class TestException : public std::runtime_error
{
public:
    TestException(const std::string& message);
};

}

#endif
