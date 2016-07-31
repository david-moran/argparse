#ifndef __ARGUMENT_HH__
#define __ARGUMENT_HH__

#include <functional>
#include <string>
#include <sstream>
#include <set>

#include "exception.hh"

namespace argparse
{

class argument
{
public:
    using names_set = std::set<std::string>;
    
private:
    names_set m_names;

    std::string m_value             {};
    bool m_value_flag               {false};

    std::string m_default_value     {};
    bool m_has_default_flag         {false};

    bool m_has_value                {false};
    bool m_has_value_flag           {false};

public:
    argument(std::initializer_list<std::string> names);

    argument& value(const std::string& value) noexcept;
    argument& default_value(const std::string& v);
    argument& has_value(bool v);

    const std::string& default_value() const noexcept;
    bool has_value() const noexcept;

    const names_set& names() const noexcept;

    template <typename T>
    T as() const;

    bool operator==(const argument& other) const noexcept;
    bool operator!=(const argument& other) const noexcept;
    bool operator<(const argument& other) const noexcept;
};

template <typename T>
T argument::as() const
{
    std::string value;

    if (!m_value_flag)
    {
        if (!m_has_default_flag)
            throw required_argument_exception("argument does not exists");

        value = m_default_value;
    }
    else
    {
        value = m_value;
    }

    T t;
    std::stringstream ss;

    ss << value;
    ss >> t;

    return t;
}

}

#endif // __ARGUMENT_HH__
