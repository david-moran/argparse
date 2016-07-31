#ifndef __ARGUMENT_HH__
#define __ARGUMENT_HH__

#include <functional>
#include <string>
#include <vector>

#include "exception.hh"

namespace argparse
{

class argument
{
public:
    using names = std::vector<std::string>;
    
private:
    names m_names;

    std::string m_default_value     {};
    bool m_has_default_flag         {false};

    bool m_has_value                {false};
    bool m_has_value_flag           {false};

public:
    argument(std::initializer_list<std::string> names) noexcept;

    void default_value(const std::string& v);
    void has_value(bool v);

    const std::string& default_value() const noexcept;
    bool has_value() const noexcept;
};

}

#endif // __ARGUMENT_HH__
