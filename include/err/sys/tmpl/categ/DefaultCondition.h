#ifndef BASIC_ERR_SYS_TMPL_CATEG_DEFAULTCONDITION_H_
#define BASIC_ERR_SYS_TMPL_CATEG_DEFAULTCONDITION_H_

#include "../Category.defn.h"

#include "has/mmbr/func/DefaultCondition.h"
#include "../../Condition.defn.h"
#include "../../Code.defn.h"
#include "../../../defn/type/code/Value.h"

#include <type_traits>
#include <utility>

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

template<typename TCategoryTrait, typename TCode>
typename std::enable_if<has::mmbr::func::DefaultCondition<TCategoryTrait,
    sys::Condition, TCode, tmpl::Category<TCategoryTrait>>::Value, 
    sys::Condition>::type  
DefaultCondition(const TCategoryTrait & categ_trait, const TCode & code,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(categ_trait.template 
        DefaultCondition<sys::Condition>(code, categ_instance));
}

template<typename TCategoryTrait>
typename std::enable_if<
    !has::mmbr::func::DefaultCondition<TCategoryTrait, sys::Condition, 
        err::defn::type::code::Value, tmpl::Category<TCategoryTrait>>::Value &&
    has::mmbr::func::DefaultCondition<TCategoryTrait, sys::Condition, 
        sys::Code, tmpl::Category<TCategoryTrait>>::Value, 
    sys::Condition>::type  
DefaultCondition(const TCategoryTrait & categ_trait, 
    const err::defn::type::code::Value & code,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(categ_trait.template DefaultCondition<
        sys::Condition>(sys::Code{code, categ_instance}, categ_instance));
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::func::DefaultCondition<TCategoryTrait, sys::Condition, 
        err::defn::type::code::Value, tmpl::Category<TCategoryTrait>>::Value &&
    !has::mmbr::func::DefaultCondition<TCategoryTrait, sys::Condition, 
        sys::Code, tmpl::Category<TCategoryTrait>>::Value, 
    sys::Condition>::type  
DefaultCondition(const TCategoryTrait & categ_trait, const sys::Code & code,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(categ_trait.template DefaultCondition<
        sys::Condition>(code.Value(), categ_instance));
}

template<typename TCategoryTrait>
typename std::enable_if<
    !has::mmbr::func::DefaultCondition<TCategoryTrait, sys::Condition, 
        err::defn::type::code::Value, tmpl::Category<TCategoryTrait>>::Value &&
    !has::mmbr::func::DefaultCondition<TCategoryTrait, sys::Condition, 
        sys::Code, tmpl::Category<TCategoryTrait>>::Value,
    sys::Condition>::type  
DefaultCondition(const TCategoryTrait & categ_trait, const sys::Code & code,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return sys::Condition{code.Value(), categ_instance};
}

template<typename TCategoryTrait, typename TCode>
typename std::enable_if<
    !has::mmbr::func::DefaultCondition<TCategoryTrait, sys::Condition, 
        err::defn::type::code::Value, tmpl::Category<TCategoryTrait>>::Value &&
    !has::mmbr::func::DefaultCondition<TCategoryTrait, sys::Condition, 
        sys::Code, tmpl::Category<TCategoryTrait>>::Value, 
    sys::Condition>::type  
DefaultCondition(const TCategoryTrait & categ_trait, const TCode & code,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return sys::Condition{code, categ_instance};
}

} //!categ

} //!tmpl

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_TMPL_CATEG_DEFAULTCONDITION_H_
