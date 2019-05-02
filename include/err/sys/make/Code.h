#ifndef BASIC_ERR_SYS_MAKE_CODE_H_
#define BASIC_ERR_SYS_MAKE_CODE_H_

#include "../../defn/type/sys/code/Value.h"

namespace basic
{
namespace err
{
namespace sys
{
namespace make
{

template<typename T>
struct Code
{
    Code() = delete;
    static err::defn::type::sys::code::Value Value(const T & code) noexcept
    {
        return static_cast<err::defn::type::sys::code::Value>(code);
    }
};

} //!make

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_MAKE_CODE_H_
