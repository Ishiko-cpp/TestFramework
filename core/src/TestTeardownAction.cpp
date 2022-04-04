/*
    Copyright (c) 2015-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "TestTeardownAction.hpp"

namespace Ishiko
{

TestTeardownAction::TestTeardownAction()
{
}

TestTeardownAction::~TestTeardownAction()
{
}

void TestTeardownAction::teardown()
{
    // Default implementation does nothing
}

}
