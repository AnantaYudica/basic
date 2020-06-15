#ifndef BASIC_ERR_SYS_TMPL_CATEG_DEFAULTCONDITIONVALUE_H_
#define BASIC_ERR_SYS_TMPL_CATEG_DEFAULTCONDITIONVALUE_H_

#include "has/mmbr/func/DefaultConditionValue.h"
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

template<typename TCategoryTrait>
inline typename std::enable_if<has::mmbr::func::
    DefaultConditionValue<TCategoryTrait>::Value, err::defn::type::sys::
    cond::Value>::type 
DefaultConditionValue(const TCategoryTrait & categ_trait) noexcept
{
    return categ_trait.DefaultConditionValue();
}

template<typename TCategoryTrait>
inline typename std::enable_if<!has::mmbr::func::
    DefaultConditionValue<TCategoryTrait>::Value, err::defn::type::sys::
    cond::Value>::type 
DefaultConditionValue(const TCategoryTrait & categ_trait) noexcept
{
    return 0;
}

} //!categ

} //!tmpl

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_TMPL_CATEG_DEFAULTCONDITIONVALUE_H_
