#ifndef BASIC_ERR_SYS_MAKE_CODE_VALUE_H_
#define BASIC_ERR_SYS_MAKE_CODE_VALUE_H_

#include "../../../defn/type/sys/code/Value.h"

namespace basic
{
namespace err
{
namespace sys
{
namespace make
{
namespace code
{

template<typename TCodeEnum>
inline err::defn::type::sys::code::Value 
Value(const TCodeEnum & code) noexcept
{
    return static_cast<err::defn::type::sys::code::Value>(code);
}

} //!code

} //!make

} //!sys

} //!err

} //!basic


#endif //BASIC_ERR_SYS_MAKE_CODE_VALUE_H_
