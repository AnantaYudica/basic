#ifndef BASIC_ERROR_SYSTEM_CATEGORY_DEFAULTCONDITION_H_
#define BASIC_ERROR_SYSTEM_CATEGORY_DEFAULTCONDITION_H_

#include "has/mmbr/func/DefaultCondition.h"
#include "defn/type/condition/set/Value.h"


#include <type_traits>

namespace basic
{
namespace error
{
namespace system
{
namespace category
{

template<typename TCategoryTrait, typename TCode>
typename std::enable_if<has::mmbr::func::DefaultCondition<TCategoryTrait,
    typename defn::type::condition::set::Value<TCategoryTrait>::Type, 
    TCode>::Value, typename defn::type::condition::set::
    Value<TCategoryTrait>::Type>::type  
DefaultCondition(const TCategoryTrait& category_trait, const TCode& code) 
    noexcept
{
    return category_trait.DefaultCondition(code);
}

template<typename TCategoryTrait, typename TCode>
typename std::enable_if<!has::mmbr::func::DefaultCondition<TCategoryTrait,
    typename defn::type::condition::set::Value<TCategoryTrait>::Type, 
    TCode>::Value, typename defn::type::condition::set::
    Value<TCategoryTrait>::Type>::type  
DefaultCondition(const TCategoryTrait& category_trait, const TCode& code) 
    noexcept
{
    return code.Value();
}

} //!category

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_CATEGORY_DEFAULTCONDITION_H_
