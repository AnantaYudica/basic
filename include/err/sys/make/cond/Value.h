#ifndef BASIC_ERR_SYS_MAKE_COND_VALUE_H_
#define BASIC_ERR_SYS_MAKE_COND_VALUE_H_

#include "../../../defn/type/sys/cond/Value.h"

namespace basic
{
namespace err
{
namespace sys
{
namespace make
{
namespace cond
{

template<typename TConditionEnum>
inline err::defn::type::sys::cond::Value 
Value(const TConditionEnum & cond) noexcept
{
    return static_cast<const err::defn::type::sys::cond::
        Value &>(cond);
}

} //!cond

} //!make

} //!sys

} //!err

} //!basic


#endif //BASIC_ERR_SYS_MAKE_COND_VALUE_H_
