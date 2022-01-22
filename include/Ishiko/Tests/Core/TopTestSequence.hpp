/*
    Copyright (c) 2015-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTS_CORE_TOPTESTSEQUENCE_HPP_
#define _ISHIKO_CPP_TESTS_CORE_TOPTESTSEQUENCE_HPP_

#include "TestSequence.hpp"

namespace Ishiko
{
namespace Tests
{

class TopTestSequence : public TestSequence
{
public:
    explicit TopTestSequence(const std::string& name);
    TopTestSequence(const std::string& name, const TestContext& context);

protected:
    void notify(Observer::EEventType type) override;
};

}
}

#endif
