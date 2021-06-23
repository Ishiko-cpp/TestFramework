/*
    Copyright (c) 2005-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_TESTFRAMEWORK_TESTFRAMEWORKCORE_H_
#define _ISHIKO_TESTFRAMEWORK_TESTFRAMEWORKCORE_H_

#include "Core/ConsoleApplicationTest.h"
#include "Core/TestException.h"
#include "Core/HeapAllocationErrorsTest.h"
#include "Core/FileComparisonTest.h"
#include "Core/JUnitXMLWriter.h"
#include "Core/TestHarness.h"
#include "Core/DirectoriesTeardownAction.h"
#include "Core/FilesTeardownAction.h"
#include "Core/ProcessAction.h"

#ifdef _DEBUG
#pragma comment(lib, "IshikoTestFrameworkCore-d.lib")
#else
#pragma comment(lib, "IshikoTestFrameworkCore.lib")
#endif

#endif
