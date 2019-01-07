#ifndef BASIC_ERROR_SYSTEM_INTF_CODE_H_
#define BASIC_ERROR_SYSTEM_INTF_CODE_H_

#include "Code.defn.h"
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

#endif //!BASIC_ERROR_SYSTEM_INTF_CODE_H_
