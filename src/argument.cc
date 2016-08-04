#include "argument.hh"

namespace argparse
{

argument::argument(std::initializer_list<std::string> names)
    : m_names(names)
{
    if (m_names.empty())
        throw invalid_argument_exception("No names given for this argument");
}

argument& argument::value(const std::string& value_) noexcept
{
    m_value_flag = true;
    m_value = value_;

    return *this;
}

argument& argument::default_value(const std::string& v)
{
    if (m_has_value_flag && has_value() == false)
        throw invalid_argument_exception("has_value() was set to false");

    m_has_default_flag = true;
    m_default_value = v;
    has_value(true);

    return *this;
}

argument& argument::has_value(bool v)
{
    if (m_has_default_flag && v == false)
        throw invalid_argument_exception("default_value() was set");

    m_has_value_flag = true;
    m_has_value = v;

    return *this;
}

argument& argument::required(bool r) noexcept
{
    m_required = r;
    return *this;
}

argument& argument::description(const std::string& d) noexcept
{
    m_description = d;
    return *this;
}

const std::string& argument::default_value() const noexcept
{ return m_default_value; }

bool argument::has_value() const noexcept
{ return m_has_value; }

bool argument::required() const noexcept
{ return m_required; }

const std::string& argument::description() const noexcept
{ return m_description; }

const argument::names_set& argument::names() const noexcept
{ return m_names; }

bool argument::operator==(const argument& other) const noexcept
{
    for (auto n : m_names)
        if (other.m_names.find(n) != other.m_names.cend())
            return true;

    return false;
}

bool argument::operator!=(const argument& other) const noexcept
{
    return !(*this == other);
}

bool argument::operator<(const argument& other) const noexcept
{
    if (*this == other)
        return false;

    return *m_names.cbegin() < *other.m_names.cbegin();
}

}
