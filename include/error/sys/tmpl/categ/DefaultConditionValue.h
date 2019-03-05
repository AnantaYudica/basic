#ifndef BASIC_ERROR_SYS_TMPL_CATEG_DEFAULTCONDITIONVALUE_H_
#define BASIC_ERROR_SYS_TMPL_CATEG_DEFAULTCONDITIONVALUE_H_

#include "has/mmbr/func/DefaultConditionValue.h"
#include "../../../defn/type/sys/condition/Value.h"

#include <type_traits>

namespace basic
{
namespace error
{
namespace sys
{
namespace tmpl
{
namespace categ
{

template<typename TCategoryTrait>
inline typename std::enable_if<has::mmbr::func::
    DefaultConditionValue<TCategoryTrait>::Value, error::defn::type::sys::
    condition::Value>::type 
DefaultConditionValue(const TCategoryTrait & categ_trait) noexcept
{
    return categ_trait.DefaultConditionValue();
}

template<typename TCategoryTrait>
inline typename std::enable_if<!has::mmbr::func::
    DefaultConditionValue<TCategoryTrait>::Value, error::defn::type::sys::
    condition::Value>::type 
DefaultConditionValue(const TCategoryTrait & categ_trait) noexcept
{
    return 0;
}

} //!categ

} //!tmpl

} //!sys

} //!error

} //!basic

#endif //!BASIC_ERROR_SYS_TMPL_CATEG_DEFAULTCONDITIONVALUE_H_
