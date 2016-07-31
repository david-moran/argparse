#include "exception.hh"

namespace argparse
{

argparse_exception::argparse_exception(const std::string& message) noexcept
    : m_message {message}
{ }

const char* argparse_exception::what() const noexcept
{ return m_message.c_str(); }

}
