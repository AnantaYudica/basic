#ifndef BASIC_ERR_INTF_OUTPUT_H_
#define BASIC_ERR_INTF_OUTPUT_H_

#include "../defn/type/Output.h"

#include <ostream>

namespace basic
{
namespace err
{
namespace intf
{

class Output
{
public:
    typedef defn::type::Output ValueType;
protected:
    constexpr Output() noexcept = default;
public:
    Output(const Output & cpy) noexcept = default;
    Output(Output && mov) noexcept = default;
public:
    Output & operator=(const Output &) = delete;
    Output & operator=(Output &&) = delete;
public:
    virtual const Output & operator>>(ValueType &) const noexcept = 0;
};

} //!intf

} //!err

} //!basic

template<typename TChar, typename TCharTraits>
std::basic_ostream<TChar, TCharTraits> & 
    operator<<(std::basic_ostream<TChar, TCharTraits> & out,
        const basic::err::intf::Output & obj)
{
    obj >> out;
    return out;
}

#endif //!BASIC_ERR_INTF_OUTPUT_H_
