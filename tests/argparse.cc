#include <string>

#include <gtest/gtest.h>
#include <set>

#include "exception.hh"
#include "argument.hh"
#include "parser.hh"

using namespace argparse;

/////////////////////
///// Test exceptions
/////////////////////
TEST (argparse_exception, what) { 
    argparse_exception e("msg1");
    ASSERT_EQ(std::string(e.what()), std::string("msg1"));
}

TEST (parse_exception, what) { 
    parse_exception e("msg1");
    ASSERT_EQ(std::string(e.what()), std::string("msg1"));
}

TEST (invalid_argument_exception, what) { 
    invalid_argument_exception e("msg1");
    ASSERT_EQ(std::string(e.what()), std::string("msg1"));
}

TEST (required_argument_exception, what) { 
    required_argument_exception e("msg1");
    ASSERT_EQ(std::string(e.what()), std::string("msg1"));
}


/////////////////////
///// Arguments
/////////////////////
TEST (argument, default_value) {
    argument arg1 {"--foo", "-f" };

    // No default value set, you could change
    // has_value wathever you want
    arg1.has_value(false);
    arg1.has_value(true);
    arg1.has_value(false);
    try
    {
        // has_value() was set false, set a default value is an error
        arg1.default_value("bar");
        FAIL();
    }
    catch (const invalid_argument_exception& ex)
    {
    }
    catch (...)
    {
        FAIL();
    }
}

TEST (argument, has_value) {
    argument arg1 {"--foo", "-f" };

    arg1.default_value("bar");
    arg1.has_value(true);
    arg1.default_value("deadbeef");
    try
    {
        // Default value is set, you can remove
        arg1.has_value(false);
        FAIL();
    }
    catch (const invalid_argument_exception& ex)
    {
    }
    catch (...)
    {
        FAIL();
    }
}

TEST (argument, equals) {
    argument arg1 {"--foo", "-f" };
    argument arg2 {"--bar", "-f" };
    argument arg3 {"--bar", "-b" };
    
    ASSERT_EQ(arg1, arg2);
    ASSERT_EQ(arg2, arg1);

    ASSERT_EQ(arg2, arg3);
    ASSERT_EQ(arg3, arg2);
}

TEST (argument, not_equals) {
    argument arg1 {"--foo", "-f" };
    argument arg2 {"--bar", "-b" };

    ASSERT_NE(arg1, arg2);
    ASSERT_NE(arg2, arg1);
}

TEST (argument, set) {
    argument arg1 {"--foo", "-f" };
    argument arg2 {"--bar", "-f" };
    argument arg3 {"--bar", "-b" };
    argument arg4 {"--arg", "-a" };

    std::set<argument> arguments;

    arguments.insert(arg1);
    ASSERT_EQ(arguments.size(), 1);

    arguments.insert(arg2);
    ASSERT_EQ(arguments.size(), 1);

    arguments.insert(arg3);
    ASSERT_EQ(arguments.size(), 2);

    arguments.insert(arg4);
    ASSERT_EQ(arguments.size(), 3);
}

TEST (argument, as) {
    argument arg1 {"--foo", "-f" };
    argument arg2 {"--bar", "-b" };
    argument arg3 {"--arg", "-a" };
    argument arg4 {"--dead", "-d" };

    arg1.value("100");
    arg2.value("12.3456");
    arg3.value("text");

    ASSERT_EQ(arg1.as<int>(), 100);
    ASSERT_EQ(arg2.as<float>(), 12.3456F);
    ASSERT_EQ(arg2.as<double>(), static_cast<double>(12.3456));
    ASSERT_EQ(arg3.as<std::string>(), "text");

    try
    {
        arg4.as<int>();
        FAIL();
    }
    catch(const required_argument_exception& ex)
    {
    }
    catch(...)
    {
        FAIL();
    }
}

/////////////////////
///// Arguments
/////////////////////
TEST (parser, parser) {
    const char* argv[] = {
        "/usr/local/bin/command",
        "--foo", "bar",
    };
    int argc = sizeof(*argv);

    parser p(argc, argv);
    p.add_argument("test", argument{"--foo", "-f"}
        .description("this is a test").default_value("10"));

    p.add_argument("test", argument{"--arg", "-a"}
        .required(true).has_value(true));

    try
    {
        p.add_argument("test", {"--bar", "-f"});
        FAIL();
    }
    catch(const invalid_argument_exception& ex)
    {
    }
    catch(...)
    {
        FAIL();
    }
}

TEST (parser, add_argument) {
    const char* argv[] = {
        "/usr/local/bin/command",
        "--foo", "bar",
        "--dead", "beef",
        "--other"
    };
    int argc = sizeof(*argv);
    parser(argc, argv);
}

TEST (parser, parse) {
    const char* argv[] = {
        "/usr/local/bin/command",
        "--foo", "bar",
        "--required", "arg",
        "--max", "1000",
        "-d"
    };
    int argc = sizeof(*argv);
    parser p(argc, argv);

    p.add_argument("foo", argument{"--foo", "-f"}
        .required(true).has_value(true));

    p.add_argument("required", argument{"--required"}
        .required(true).has_value(true));

    p.add_argument("max", argument{"--max", "-m"}
        .required(true).has_value(true));

    p.add_argument("daemon", argument{"--daemon", "-d"}
        .required(true));

    auto parsed = p.parse();

    ASSERT_EQ(parsed["foo"].as<std::string>(), std::string("bar"));
    ASSERT_EQ(parsed["required"].as<std::string>(), std::string("arg"));
    ASSERT_EQ(parsed["max"].as<int>(), 1000);
    ASSERT_FALSE(parsed.find("daemon") == parsed.cend());
    ASSERT_TRUE(parsed.find("notexists") == parsed.cend());
}

/////////////////////
///// Main
/////////////////////
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

