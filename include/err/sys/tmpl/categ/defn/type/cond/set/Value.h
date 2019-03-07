#ifndef BASIC_ERR_SYS_TMPL_CATEG_DEFN_TYPE_COND_SET_VALUE_H_
#define BASIC_ERR_SYS_TMPL_CATEG_DEFN_TYPE_COND_SET_VALUE_H_

#include "../../../../../../../defn/type/sys/cond/Value.h"

#include "../../../../has/mmbr/defn/type/ConditionEnum.h"

namespace _helper
{
namespace _basic
{
namespace _err
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
namespace _cond
{
namespace _set
{

template<typename TCategoryTrait, bool = basic::err::sys::tmpl::categ::
    has::mmbr::defn::type::ConditionEnum<TCategoryTrait>::Value>
struct _Value
{
    typedef basic::err::defn::type::sys::cond::Value Type;
};

template<typename TCategoryTrait>
struct _Value<TCategoryTrait, true>
{
    typedef typename TCategoryTrait::ConditionEnumType Type;
};

} //!_set

} //!_cond

} //!_type

} //!_defn

} //!_categ

} //!_tmpl

} //!_sys

} //!_err

} //!_basic

} //!_helper

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
namespace defn
{
namespace type
{
namespace cond
{
namespace set
{

template<typename TCategoryTrait>
using Value = typename _helper::_basic::_err::_sys::_tmpl::_categ::
    _defn::_type::_cond::_set::_Value<TCategoryTrait>::Type;

} //!set

} //!cond

} //!type

} //!defn

} //!categ

} //!tmpl

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_TMPL_CATEG_DEFN_TYPE_COND_SET_VALUE_H_
