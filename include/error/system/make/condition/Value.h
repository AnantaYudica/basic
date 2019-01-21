#ifndef BASIC_ERROR_SYSTEM_MAKE_CONDITION_VALUE_H_
#define BASIC_ERROR_SYSTEM_MAKE_CONDITION_VALUE_H_

#include "../../../defn/type/system/condition/Value.h"

namespace basic
{
namespace error
{
namespace system
{
namespace make
{
namespace condition
{

template<typename TConditionEnum>
inline error::defn::type::system::condition::Value 
Value(const TConditionEnum & cond) noexcept
{
    return static_cast<const error::defn::type::system::condition::
        Value &>(cond);
}

} //!condition

} //!make

} //!system

} //!error

} //!basic


#endif //BASIC_ERROR_SYSTEM_MAKE_CONDITION_VALUE_H_
