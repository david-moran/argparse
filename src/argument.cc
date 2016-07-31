#include "argument.hh"

namespace argparse
{

argument::argument(std::initializer_list<std::string> names) noexcept
    : m_names(names)
{ }

void argument::default_value(const std::string& v)
{
    if (m_has_value_flag && has_value() == false)
        throw invalid_argument_exception("has_value() was set to false");

    m_has_default_flag = true;
    m_default_value = v;
    has_value(true);
}

void argument::has_value(bool v)
{
    if (m_has_default_flag && v == false)
        throw invalid_argument_exception("default_value() was set");

    m_has_value_flag = true;
    m_has_value = v;
}

const std::string& argument::default_value() const noexcept
{ return m_default_value; }

bool argument::has_value() const noexcept
{ return m_has_value; }

}
