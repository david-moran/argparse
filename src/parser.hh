#ifndef __PARSER_HH__
#define __PARSER_HH__

#include <map>
#include <string>
#include <set>

#include "argument.hh"

namespace argparse
{

class parser
{
public:
    using arguments = std::map<argument, std::string>;
    using parsed_arguments = std::map<std::string, argument>;

private:
    int argc;
    const char** argv;

    std::string m_command;
    std::string m_description;

    arguments m_arguments;

public:
    parser(int argc, const char* argv[]) noexcept;
    parser(int argc, char* argv[]) noexcept;

    void description(const std::string& description) noexcept;

    void add_argument(const std::string& destination,
                      const argument& argument);
//
//    const std::string& help() const noexcept;
//
//    parsed_arguments parse() const;
};

}

#endif // __PARSER_HH__
