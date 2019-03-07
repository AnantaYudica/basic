#ifndef BASIC_ERR_SYS_TMPL_CATEG_TOCONDITIONVALUE_H_
#define BASIC_ERR_SYS_TMPL_CATEG_TOCONDITIONVALUE_H_

#include "has/mmbr/func/ToConditionValue.h"
#include "../../../defn/type/sys/cond/Value.h"

#include <type_traits>

namespace basic
{
namespace err
{
namespace sys
{
namespace tmpl
{
namespace categ
{

template<typename TCategoryTrait, typename TConditionEnum>
inline typename std::enable_if<has::mmbr::func::
    ToConditionValue<TCategoryTrait, TConditionEnum>::Value, 
    err::defn::type::sys::cond::Value>::type 
ToConditionValue(const TCategoryTrait & categ_trait, 
    const TConditionEnum & cond) noexcept
{
    return categ_trait.ToConditionValue(cond);
}

template<typename TCategoryTrait, typename TConditionEnum>
inline typename std::enable_if<!has::mmbr::func::
    ToConditionValue<TCategoryTrait, TConditionEnum>::Value, 
    err::defn::type::sys::cond::Value>::type 
ToConditionValue(const TCategoryTrait & categ_trait, 
    const TConditionEnum & cond) noexcept
{
    return static_cast<err::defn::type::sys::cond::Value>(cond);
}

} //!categ

} //!tmpl

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_TMPL_CATEG_TOCONDITIONVALUE_H_
