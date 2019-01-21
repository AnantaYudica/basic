#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEGORY_DEFAULTCONDITION_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEGORY_DEFAULTCONDITION_H_

#include "../Category.defn.h"

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
    system::Condition, TCode, tmpl::Category<TCategoryTrait>>::Value, 
    system::Condition>::type  
DefaultCondition(const TCategoryTrait & category_trait, const TCode & code,
    const tmpl::Category<TCategoryTrait> & category_instance) noexcept
{
    return std::move(category_trait.template 
        DefaultCondition<system::Condition>(code, category_instance));
}

template<typename TCategoryTrait, typename TCode>
typename std::enable_if<!has::mmbr::func::DefaultCondition<TCategoryTrait,
    system::Condition, TCode, tmpl::Category<TCategoryTrait>>::Value, 
    system::Condition>::type  
DefaultCondition(const TCategoryTrait & category_trait, const TCode & code,
    const tmpl::Category<TCategoryTrait> & category_instance) noexcept
{
    return {code, category_instance};
}

} //!category

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEGORY_DEFAULTCONDITION_H_
