#ifndef BASIC_ERROR_SYS_MAKE_CODE_VALUE_H_
#define BASIC_ERROR_SYS_MAKE_CODE_VALUE_H_

#include "../../../defn/type/sys/code/Value.h"

namespace basic
{
namespace error
{
namespace sys
{
namespace make
{
namespace code
{

template<typename TCodeEnum>
inline error::defn::type::sys::code::Value 
Value(const TCodeEnum & code) noexcept
{
    return static_cast<error::defn::type::sys::code::Value>(code);
}

} //!code

} //!make

} //!sys

} //!error

} //!basic


#endif //BASIC_ERROR_SYS_MAKE_CODE_VALUE_H_
