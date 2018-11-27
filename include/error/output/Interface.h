#ifndef BASIC_ERROR_OUTPUT_INTERFACE_H_
#define BASIC_ERROR_OUTPUT_INTERFACE_H_

#include "../defn/type/Output.h"

namespace basic
{
namespace error
{
namespace output
{

class Interface
{
public:
    typedef defn::type::Output ValueType;
protected:
    constexpr Interface() noexcept;
public:
    Interface(const Interface& cpy) noexcept = default;
    Interface(Interface&& mov) noexcept = default;
public:
    Interface& operator=(const Interface&) = delete;
    Interface& operator=(Interface&&) = delete;
public:
    virtual ValueType& Output(ValueType&) const noexcept = 0;
};

constexpr Interface::Interface() noexcept
{}

} //!output

} //!error

} //!basic

#endif //!BASIC_ERROR_OUTPUT_INTERFACE_H_
