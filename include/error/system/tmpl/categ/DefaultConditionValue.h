#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEG_DEFAULTCONDITIONVALUE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEG_DEFAULTCONDITIONVALUE_H_

#include "has/mmbr/func/DefaultConditionValue.h"
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

template<typename TCategoryTrait>
inline typename std::enable_if<has::mmbr::func::
    DefaultConditionValue<TCategoryTrait>::Value, error::defn::type::system::
    condition::Value>::type 
DefaultConditionValue(const TCategoryTrait & categ_trait) noexcept
{
    return categ_trait.DefaultConditionValue();
}

template<typename TCategoryTrait>
inline typename std::enable_if<!has::mmbr::func::
    DefaultConditionValue<TCategoryTrait>::Value, error::defn::type::system::
    condition::Value>::type 
DefaultConditionValue(const TCategoryTrait & categ_trait) noexcept
{
    return 0;
}

} //!categ

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEG_DEFAULTCONDITIONVALUE_H_
