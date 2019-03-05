#ifndef BASIC_ERROR_SYS_MAKE_COND_VALUE_H_
#define BASIC_ERROR_SYS_MAKE_COND_VALUE_H_

#include "../../../defn/type/sys/cond/Value.h"

namespace basic
{
namespace error
{
namespace sys
{
namespace make
{
namespace cond
{

template<typename TConditionEnum>
inline error::defn::type::sys::cond::Value 
Value(const TConditionEnum & cond) noexcept
{
    return static_cast<const error::defn::type::sys::cond::
        Value &>(cond);
}

} //!cond

} //!make

} //!sys

} //!error

} //!basic


#endif //BASIC_ERROR_SYS_MAKE_COND_VALUE_H_
