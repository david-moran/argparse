#ifndef __ARGPARSE_HH__
#define __ARGPARSE_HH__

#include <exception>
#include <map>
#include <string>
#include <vector>

class argparse_exception : public std::exception
{ };

class parse_exception : public argparse_exception
{
public:
    using argparse_exception::argparse_exception;
};

class invalid_argument_exception : public argparse_exception
{
public:
    using argparse_exception::argparse_exception;
};

class argument
{
public:
    using names = std::vector<std::string>;

private:
    names m_names           {};
    std::string m_default   {};
    std::string m_help      {};
    bool m_required         {false};
    bool m_has_arg          {true};

    std::string m_value     {};
    bool m_is_present       {false};

public:
    argument(const names& names,
             const std::string& default = {},
             const std::string& help = {},
             bool required = false,
             bool has_arg = true) noexcept;

    argument(const std::string& name,
             const std::string& default = {},
             const std::string& help = {},
             bool required = false,
             bool has_arg = true) noexcept;

    template <typename T>
    const T& value_as() const noexcept;

    const std::string& value() const noexcept;
    
    bool is_present() const noexcept;

    friend class argparse;
};

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

#endif // __ARGPARSE_HH__
