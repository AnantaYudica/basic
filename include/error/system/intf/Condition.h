#ifndef BASIC_ERROR_SYSTEM_INTF_CONDITION_H_
#define BASIC_ERROR_SYSTEM_INTF_CONDITION_H_

#include "Condition.def.h"
#include "Category.h"

#include <ostream>

bool operator==(const basic::error::system::intf::Condition & a, 
    const basic::error::system::intf::Condition & b) noexcept
{
    return a.Category() == b.Category() &&
        a.Value() == b.Value();
}

bool operator==(const basic::error::system::intf::Condition& a, 
    const basic::error::defn::type::system::condition::Value & b) noexcept
{
    return a.Value() == b;
}

bool operator==(const basic::error::defn::type::system::condition::Value & a, 
    const basic::error::system::intf::Condition & b) noexcept
{
    return b == a;
}

bool operator!=(const basic::error::system::intf::Condition & a, 
    const basic::error::system::intf::Condition & b) noexcept
{
    return !(a == b);
}

bool operator!=(const basic::error::system::intf::Condition & a, 
    const basic::error::defn::type::system::condition::Value & b) noexcept
{
    return !(a == b);
}

bool operator!=(const basic::error::defn::type::system::condition::Value & a, 
    const basic::error::system::intf::Condition & b) noexcept
{
    return !(a == b);
}

bool operator<(const basic::error::system::intf::Condition & a, 
    const basic::error::system::intf::Condition & b) noexcept
{
    return a.Category() == b.Category() &&
        a.Value() < b.Value();
}

bool operator<(const basic::error::system::intf::Condition & a, 
    const basic::error::defn::type::system::condition::Value & b) noexcept
{
    return a.Value() < b;
}

bool operator<(const basic::error::defn::type::system::condition::Value & a, 
    const basic::error::system::intf::Condition & b) noexcept
{
    return a < b.Value();
}

bool operator>(const basic::error::system::intf::Condition & a, 
    const basic::error::system::intf::Condition & b) noexcept
{
    return a.Category() == b.Category() &&
        a.Value() > b.Value();
}

bool operator>(const basic::error::system::intf::Condition & a, 
    const basic::error::defn::type::system::condition::Value & b) noexcept
{
    return a.Value() > b;
}

bool operator>(const basic::error::defn::type::system::condition::Value & a, 
    const basic::error::system::intf::Condition & b) noexcept
{
    return a > b.Value();
}

template<typename TChar, typename TCharTraits>
std::basic_ostream<TChar, TCharTraits> & 
    operator<<(std::basic_ostream<TChar, TCharTraits> & out,
        const basic::error::system::intf::Condition & cond)
{
    cond.Output(out);
    return out;
}

#endif //!BASIC_ERROR_SYSTEM_INTF_CONDITION_H_
