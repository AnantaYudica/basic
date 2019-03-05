#ifndef BASIC_ERROR_SYS_MAKE_CONDITION_VALUE_H_
#define BASIC_ERROR_SYS_MAKE_CONDITION_VALUE_H_

#include "../../../defn/type/sys/condition/Value.h"

namespace basic
{
namespace error
{
namespace sys
{
namespace make
{
namespace condition
{

template<typename TConditionEnum>
inline error::defn::type::sys::condition::Value 
Value(const TConditionEnum & cond) noexcept
{
    return static_cast<const error::defn::type::sys::condition::
        Value &>(cond);
}

} //!condition

} //!make

} //!sys

} //!error

} //!basic


#endif //BASIC_ERROR_SYS_MAKE_CONDITION_VALUE_H_
