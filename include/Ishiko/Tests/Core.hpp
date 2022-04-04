/*
    Copyright (c) 2005-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTS_CORE_HPP_
#define _ISHIKO_CPP_TESTS_CORE_HPP_

#include "Core/ConsoleApplicationTest.hpp"
#include "Core/HeapAllocationErrorsTest.hpp"
#include "Core/FileComparisonTest.hpp"
#include "Core/FileComparisonTestCheck.hpp"
#include "Core/JUnitXMLWriter.hpp"
#include "Core/Test.hpp"
#include "Core/TestApplicationReturnCodes.hpp"
#include "Core/TestCheck.hpp"
#include "Core/TestException.hpp"
#include "Core/TestHarness.hpp"
#include "Core/TestMacros.hpp"
#include "Core/TestMacrosFormatter.hpp"
#include "Core/TestProgressObserver.hpp"
#include "Core/TestResult.hpp"
#include "Core/TestSequence.hpp"
#include "Core/DirectoriesTeardownAction.hpp"
#include "Core/FilesTeardownAction.hpp"
#include "Core/ProcessAction.hpp"

#ifdef _DEBUG
#pragma comment(lib, "IshikoTestsCore-d.lib")
#else
#pragma comment(lib, "IshikoTestsCore.lib")
#endif

#endif
