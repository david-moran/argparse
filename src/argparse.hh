#ifndef __ARGPARSE_HH__
#define __ARGPARSE_HH__

#include <map>
#include <string>

#include "exception.hh"

namespace argparse
{

class argparse
{
public:
    using parsed_arguments = std::map<std::string, argument>;

private:
    int argc;
    const char* argv[];

    std::string m_description;

public:
    argparse(int argc, const char* argv[]);

    void description(const std::string& description) noexcept;

    void add_argument(const std::string& destination,
                      const argument& argument);

    const std::string& help() const noexcept;

    parsed_arguments parse() const;
};

}

#endif // __ARGPARSE_HH__
