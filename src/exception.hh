#ifndef __EXCEPTION_HH__
#define __EXCEPTION_HH__

#include <exception>
#include <string>

namespace argparse
{

class argparse_exception : public std::exception
{
private:
    std::string m_message;

public:
    argparse_exception(const std::string& message) noexcept;

    virtual const char* what() const noexcept override;
};

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

class required_argument_exception : public argparse_exception
{
public:
    using argparse_exception::argparse_exception;
};

}

#endif // __EXCEPTION_HH__
