/*
    Copyright (c) 2015-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_CORE_TOPTESTSEQUENCE_H_
#define _ISHIKO_TESTS_CORE_TOPTESTSEQUENCE_H_

#include "TestSequence.h"

namespace Ishiko
{
namespace Tests
{

class TopTestSequence : public TestSequence
{
public:
    explicit TopTestSequence(const std::string& name);
    TopTestSequence(const std::string& name, 
        const TestEnvironment& environment);

protected:
    void notify(Observer::EEventType type) override;
};

}
}

#endif
