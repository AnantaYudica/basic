#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEGORY_DEFAULTCONDITION_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEGORY_DEFAULTCONDITION_H_

#include "has/mmbr/func/DefaultCondition.h"
#include "../../Condition.h"

#include <type_traits>
#include <utility>

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

template<typename TCategoryTrait, typename TCode>
typename std::enable_if<has::mmbr::func::DefaultCondition<TCategoryTrait,
    system::Condition, TCode>::Value, system::Condition>::type  
DefaultCondition(const TCategoryTrait & category_trait, const TCode & code) 
    noexcept
{
    return std::move(category_trait.template 
        DefaultCondition<system::Condition>(code));
}

template<typename TCategoryTrait, typename TCode>
typename std::enable_if<!has::mmbr::func::DefaultCondition<TCategoryTrait,
    system::Condition, TCode>::Value, system::Condition>::type  
DefaultCondition(const TCategoryTrait & category_trait, const TCode & code) 
    noexcept
{
    return {code};
}

} //!category

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEGORY_DEFAULTCONDITION_H_
