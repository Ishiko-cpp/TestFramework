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

    void EqualityCheckTest1(Ishiko::Test& test)
    {
        ISHIKO_TEST_FAIL_IF_EQ(5, 5);
        ISHIKO_TEST_FAIL_IF_EQ(5, 6);

        ISHIKO_TEST_FAIL_IF_NEQ(5, 5);
        ISHIKO_TEST_FAIL_IF_NEQ(5, 6);

        ISHIKO_TEST_PASS();
    }

    void EqualityCheckTest2(Ishiko::Test& test)
    {
        ISHIKO_TEST_FAIL_IF_EQ(std::string{"table"}, std::string{"table"});
        ISHIKO_TEST_FAIL_IF_EQ(std::string{"table"}, std::string{"chair"});

        ISHIKO_TEST_FAIL_IF_NEQ(std::string{"table"}, std::string{"table"});
        ISHIKO_TEST_FAIL_IF_NEQ(std::string{"table"}, std::string{"chair"});

        ISHIKO_TEST_PASS();
    }

    void StringEqualityCheckTest(Ishiko::Test& test)
    {
        ISHIKO_TEST_FAIL_IF_STR_EQ("table", "table");
        ISHIKO_TEST_FAIL_IF_STR_EQ("table", "chair");

        ISHIKO_TEST_FAIL_IF_STR_NEQ("table", "table");
        ISHIKO_TEST_FAIL_IF_STR_NEQ("table", "chair");

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
        the_tests.append<Ishiko::Test>("EqualityCheckTest1", EqualityCheckTest1);
        the_tests.append<Ishiko::Test>("EqualityCheckTest2", EqualityCheckTest2);
        the_tests.append<Ishiko::Test>("StringEqualityCheckTest", StringEqualityCheckTest);

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
