/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTCHECK_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTCHECK_HPP_

namespace Ishiko
{

class TestCheck
{
public:
    enum class Result
    {
        passed,
        failed
    };

    virtual Result run() = 0;
};

}

#endif
