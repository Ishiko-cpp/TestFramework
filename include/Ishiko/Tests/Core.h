/*
    Copyright (c) 2005-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_CORE_H_
#define _ISHIKO_TESTS_CORE_H_

#include "Core/ConsoleApplicationTest.h"
#include "Core/HeapAllocationErrorsTest.h"
#include "Core/FileComparisonTest.h"
#include "Core/JUnitXMLWriter.h"
#include "Core/TestException.h"
#include "Core/TestHarness.h"
#include "Core/TestMacros.h"
#include "Core/TestMacrosFormatter.h"
#include "Core/TestProgressObserver.h"
#include "Core/DirectoriesTeardownAction.h"
#include "Core/FilesTeardownAction.h"
#include "Core/ProcessAction.h"

#ifdef _DEBUG
#pragma comment(lib, "IshikoTestsCore-d.lib")
#else
#pragma comment(lib, "IshikoTestsCore.lib")
#endif

#endif
