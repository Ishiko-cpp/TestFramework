/*
    Copyright (c) 2023 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include <Ishiko/TestFramework.hpp>

namespace
{
    void AlwaysPassTest(Ishiko::Test& test)
    {
        ISHIKO_TEST_PASS();
    }

    void AlwaysFailTest(Ishiko::Test& test)
    {
        ISHIKO_TEST_FAIL();
    }

    void ConditionCheckTest(Ishiko::Test& test)
    {
        ISHIKO_TEST_FAIL_IF(5 == 5);
        ISHIKO_TEST_FAIL_IF(5 == 6);

        ISHIKO_TEST_FAIL_IF_NOT(5 == 5);
        ISHIKO_TEST_FAIL_IF_NOT(5 == 6);

        ISHIKO_TEST_PASS();
    }

    void EqualityCheckTest(Ishiko::Test& test)
    {
        ISHIKO_TEST_FAIL_IF_EQ(5, 5);
        ISHIKO_TEST_FAIL_IF_EQ(5, 6);

        ISHIKO_TEST_FAIL_IF_NEQ(5, 5);
        ISHIKO_TEST_FAIL_IF_NEQ(5, 6);

        ISHIKO_TEST_PASS();
    }
}

int main(int argc, char* argv[])
{
    try
    {
        Ishiko::TestHarness::CommandLineSpecification command_line_spec;
        command_line_spec.setDefaultValue("context.data", "../../data");
        command_line_spec.setDefaultValue("context.output", "../../output");
        command_line_spec.setDefaultValue("context.reference", "../../reference");

        Ishiko::Configuration configuration = command_line_spec.createDefaultConfiguration();
        Ishiko::CommandLineParser::parse(command_line_spec, argc, argv, configuration);

        Ishiko::TestHarness the_test_harness("Ishiko/C++ TestFramework Basic Checks Example", configuration);

        Ishiko::TestSequence& the_tests = the_test_harness.tests();
        the_tests.append<Ishiko::Test>("AlwaysPassTest", AlwaysPassTest);
        the_tests.append<Ishiko::Test>("AlwaysFailTest", AlwaysFailTest);
        the_tests.append<Ishiko::Test>("ConditionCheckTest", ConditionCheckTest);
        the_tests.append<Ishiko::Test>("EqualityCheckTest", EqualityCheckTest);

        return the_test_harness.run();
    }
    catch (const std::exception& e)
    {
        return Ishiko::TestApplicationReturnCode::exception;
    }
    catch (...)
    {
        return Ishiko::TestApplicationReturnCode::exception;
    }
}
