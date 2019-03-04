#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEG_TOCONDITIONVALUE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEG_TOCONDITIONVALUE_H_

#include "has/mmbr/func/ToConditionValue.h"
#include "../../../defn/type/system/condition/Value.h"

#include <type_traits>

namespace basic
{
namespace error
{
namespace system
{
namespace tmpl
{
namespace categ
{

template<typename TCategoryTrait, typename TConditionEnum>
inline typename std::enable_if<has::mmbr::func::
    ToConditionValue<TCategoryTrait, TConditionEnum>::Value, 
    error::defn::type::system::condition::Value>::type 
ToConditionValue(const TCategoryTrait & categ_trait, 
    const TConditionEnum & cond) noexcept
{
    return categ_trait.ToConditionValue(cond);
}

template<typename TCategoryTrait, typename TConditionEnum>
inline typename std::enable_if<!has::mmbr::func::
    ToConditionValue<TCategoryTrait, TConditionEnum>::Value, 
    error::defn::type::system::condition::Value>::type 
ToConditionValue(const TCategoryTrait & categ_trait, 
    const TConditionEnum & cond) noexcept
{
    return static_cast<error::defn::type::system::condition::Value>(cond);
}

} //!categ

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEG_TOCONDITIONVALUE_H_
