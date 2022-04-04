/*
    Copyright (c) 2005-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTAPPLICATIONERRORCODES_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTAPPLICATIONERRORCODES_HPP_

namespace Ishiko
{

enum ETestApplicationReturnCodes
{
    eOK = 0,
    eConfigurationProblem = -1,
    eException = -3,
    eTestFailure = -4
};

}

#endif
