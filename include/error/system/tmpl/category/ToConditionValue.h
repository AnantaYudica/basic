#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEGORY_TOCONDITIONVALUE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEGORY_TOCONDITIONVALUE_H_

#include "has/mmbr/func/ToConditionValue.h"
#include "../../defn/type/system/condition/Value.h"

#include <type_traits>

namespace basic
{
namespace error
{
namespace system
{
namespace tmpl
{
namespace category
{

template<typename TCategoryTrait, typename TConditionEnum>
inline typename std::enable_if<has::mmbr::func::
    ToConditionValue<TCategoryTrait, TConditionEnum>::Value, 
    error::defn::type::system::condition::Value>::type 
DefaultConditionValue(const TCategoryTrait & category_trait, 
    const TConditionEnum & cond) noexcept
{
    return category_trait.ToConditionValue(cond);
}

template<typename TCategoryTrait, typename TConditionEnum>
inline typename std::enable_if<!has::mmbr::func::
    ToConditionValue<TCategoryTrait, TConditionEnum>::Value, 
    error::defn::type::system::condition::Value>::type 
DefaultConditionValue(const TCategoryTrait & category_trait, 
    const TConditionEnum & cond) noexcept
{
    return static_cast<error::defn::type::system::condition::Value>(cond);
}

} //!category

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEGORY_TOCONDITIONVALUE_H_
