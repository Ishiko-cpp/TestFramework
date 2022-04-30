/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_LINKOPTIONS_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_LINKOPTIONS_HPP_

#include <Ishiko/Process/linkoptions.h>

#ifdef _DEBUG
#pragma comment(lib, "IshikoTestFrameworkCore-d.lib")
#else
#pragma comment(lib, "IshikoTestFrameworkCore.lib")
#endif

#endif
