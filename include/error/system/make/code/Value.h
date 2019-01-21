#ifndef BASIC_ERROR_SYSTEM_MAKE_CODE_VALUE_H_
#define BASIC_ERROR_SYSTEM_MAKE_CODE_VALUE_H_

#include "../../../defn/type/system/code/Value.h"

namespace basic
{
namespace error
{
namespace system
{
namespace make
{
namespace code
{

template<typename TCodeEnum>
inline error::defn::type::system::code::Value 
Value(const TCodeEnum & code) noexcept
{
    return static_cast<error::defn::type::system::code::Value>(code);
}

} //!code

} //!make

} //!system

} //!error

} //!basic


#endif //BASIC_ERROR_SYSTEM_MAKE_CODE_VALUE_H_
