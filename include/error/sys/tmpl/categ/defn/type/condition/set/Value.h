#ifndef BASIC_ERROR_SYS_TMPL_CATEG_DEFN_TYPE_CONDITION_SET_VALUE_H_
#define BASIC_ERROR_SYS_TMPL_CATEG_DEFN_TYPE_CONDITION_SET_VALUE_H_

#include "../../../../../../../defn/type/sys/condition/Value.h"

#include "../../../../has/mmbr/defn/type/ConditionEnum.h"

namespace _helper
{
namespace _basic
{
namespace _error
{
namespace _sys
{
namespace _tmpl
{
namespace _categ
{
namespace _defn
{
namespace _type
{
namespace _condition
{
namespace _set
{

template<typename TCategoryTrait, bool = basic::error::sys::tmpl::categ::
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value>
struct _Value
{
    typedef basic::error::defn::type::sys::condition::Value Type;
};

template<typename TCategoryTrait>
struct _Value<TCategoryTrait, true>
{
    typedef typename TCategoryTrait::ConditionEnumType Type;
};

} //!_set

} //!_condition

} //!_type

} //!_defn

} //!_categ

} //!_tmpl

} //!_sys

} //!_error

} //!_basic

} //!_helper

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
namespace defn
{
namespace type
{
namespace condition
{
namespace set
{

template<typename TCategoryTrait>
using Value = typename _helper::_basic::_error::_sys::_tmpl::_categ::
    _defn::_type::_condition::_set::_Value<TCategoryTrait>::Type;

} //!set

} //!condition

} //!type

} //!defn

} //!categ

} //!tmpl

} //!sys

} //!error

} //!basic

#endif //!BASIC_ERROR_SYS_TMPL_CATEG_DEFN_TYPE_CONDITION_SET_VALUE_H_
