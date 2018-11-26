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
    Interface() noexcept;
public:
    Interface& operator=(const Interface&) = delete;
    Interface& operator=(Interface&&) = delete;
public:
    virtual ValueType& Output(ValueType&) const noexcept = 0;
};

Interface::Interface() noexcept
{}

} //!output

} //!error

} //!basic

#endif //!BASIC_ERROR_OUTPUT_INTERFACE_H_
