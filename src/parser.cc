#include "parser.hh"
#include "exception.hh"

namespace argparse
{

parser::parser(int argc, const char* argv[]) noexcept
    : argc {argc}, argv {argv}, m_command {argv[0]}
{ }

parser::parser(int argc, char* argv[]) noexcept
    : parser(argc, const_cast<const char**>(argv))
{}

inline void parser::description(const std::string& description) noexcept
{ m_description = description; }

void parser::add_argument(const std::string& destination,
                          const argument& argument)
{
    if (m_arguments.find(argument) != m_arguments.end())
        throw invalid_argument_exception("Argument already exists");

    m_arguments[argument] = destination;
}

}
