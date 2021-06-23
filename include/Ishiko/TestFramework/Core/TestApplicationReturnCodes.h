/*
    Copyright (c) 2005-2019 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_TESTFRAMEWORK_CORE_TESTAPPLICATIONERRORCODES_H_
#define _ISHIKO_TESTFRAMEWORK_CORE_TESTAPPLICATIONERRORCODES_H_

namespace Ishiko
{
namespace Tests
{

enum ETestApplicationReturnCodes
{
    eOK = 0,
    eConfigurationProblem = -1,
    eException = -3,
    eTestFailure = -4
};

}
}

#endif
