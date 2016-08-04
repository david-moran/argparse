#include "parser.hh"
#include "exception.hh"

namespace argparse
{

parser::parser(int argc, const char* argv[]) noexcept
    : argc {argc}, argv {argv}, m_command {argv[0]}
{}

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

std::string parser::help() const noexcept
{
    // TODO
    return std::string();    
}

parser::parsed_arguments parser::parse() const
{
    parser::parsed_arguments parsed;
    std::set<std::string> required;
    for (auto argument_pair : m_arguments)
    {
        auto argument = argument_pair.first;
        auto destination = argument_pair.second;
        
        if (argument.required())
            required.insert(destination);
    }

    for (int i = 1; i < argc; i++) 
    {
        std::string token {argv[i]};

        for (auto argument_pair : m_arguments)
        {
            auto argument = argument_pair.first;
            auto destination = argument_pair.second;
            auto found = false;
            
            for (auto name : argument.names())
            {
                if (name == token)
                {
                    found = true;
                    break;
                }
            }

            if (found)
            {
                if (argument.has_value())
                {
                    if (++i >= argc)
                        throw parse_exception("not enough parameters");

                    argument.value(std::string(argv[i]));

                }
                parsed[destination] = argument;

                // Required parameter found, remove it from required set
                auto r = required.find(destination);
                if (r != required.cend())
                    required.erase(r);

                break;
            }
        }
    }

    if (required.size() > 0)
    {
        std::stringstream ss;
        ss << "Parameters not set:";

        for (auto r : required)
            ss << " " << r;
        ss << std::endl;

        throw parse_exception(ss.str());
    }

    return parsed;
}

}
