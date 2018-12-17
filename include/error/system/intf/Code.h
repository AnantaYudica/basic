#ifndef BASIC_ERROR_SYSTEM_INTF_CODE_H_
#define BASIC_ERROR_SYSTEM_INTF_CODE_H_

#include "Code.def.h"
#include "Category.h"

#include <ostream>

bool operator==(const basic::error::system::intf::Code & a, 
    const basic::error::system::intf::Code & b) noexcept
{
    return a.Category() == b.Category() &&
        a.Value() == b.Value();
}

bool operator==(const basic::error::system::intf::Code& a, 
    const basic::error::defn::type::system::code::Value & b) noexcept
{
    return a.Value() == b;
}

bool operator==(const basic::error::defn::type::system::code::Value & a, 
    const basic::error::system::intf::Code & b) noexcept
{
    return b == a;
}

bool operator!=(const basic::error::system::intf::Code & a, 
    const basic::error::system::intf::Code & b) noexcept
{
    return !(a == b);
}

bool operator!=(const basic::error::system::intf::Code & a, 
    const basic::error::defn::type::system::code::Value & b) noexcept
{
    return !(a == b);
}

bool operator!=(const basic::error::defn::type::system::code::Value & a, 
    const basic::error::system::intf::Code & b) noexcept
{
    return !(a == b);
}

bool operator<(const basic::error::system::intf::Code & a, 
    const basic::error::system::intf::Code & b) noexcept
{
    return a.Category() == b.Category() &&
        a.Value() < b.Value();
}

bool operator<(const basic::error::system::intf::Code & a, 
    const basic::error::defn::type::system::code::Value & b) noexcept
{
    return a.Value() < b;
}

bool operator<(const basic::error::defn::type::system::code::Value & a, 
    const basic::error::system::intf::Code & b) noexcept
{
    return a < b.Value();
}

bool operator>(const basic::error::system::intf::Code & a, 
    const basic::error::system::intf::Code & b) noexcept
{
    return a.Category() == b.Category() &&
        a.Value() > b.Value();
}

bool operator>(const basic::error::system::intf::Code & a, 
    const basic::error::defn::type::system::code::Value & b) noexcept
{
    return a.Value() > b;
}

bool operator>(const basic::error::defn::type::system::code::Value & a, 
    const basic::error::system::intf::Code & b) noexcept
{
    return a > b.Value();
}

template<typename TChar, typename TCharTraits>
std::basic_ostream<TChar, TCharTraits> & 
    operator<<(std::basic_ostream<TChar, TCharTraits> & out,
        const basic::error::system::intf::Code & code)
{
    code.Output(out);
    return out;
}

#endif //!BASIC_ERROR_SYSTEM_INTF_CODE_H_
