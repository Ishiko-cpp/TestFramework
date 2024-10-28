/*
    Copyright (c) 2015-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "TopTestSequence.hpp"

namespace Ishiko
{

TopTestSequence::TopTestSequence(const std::string& name)
    : TestSequence(TestNumber(), name)
{
}

TopTestSequence::TopTestSequence(const std::string& name,
    const TestContext& context)
    : TestSequence(TestNumber(), name, context)
{
}

void TopTestSequence::notify(Observer::EventType type)
{
    // Do nothing because the top level sequence is a 
    // sequence hidden to the user and used by the test 
    // harness internally only
}

}
