#ifndef BASIC_ERR_SYS_TMPL_CATEG_DEFN_TYPE_CODE_SET_VALUE_H_
#define BASIC_ERR_SYS_TMPL_CATEG_DEFN_TYPE_CODE_SET_VALUE_H_

#include "../../../../../../../defn/type/sys/code/Value.h"

#include "../../../../has/mmbr/defn/type/CodeEnum.h"

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
namespace _code
{
namespace _set
{

template<typename TCategoryTrait, bool = basic::err::sys::tmpl::categ::
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value>
struct _Value
{
    typedef basic::err::defn::type::sys::code::Value Type;
};

template<typename TCategoryTrait>
struct _Value<TCategoryTrait, true>
{
    typedef typename TCategoryTrait::CodeEnumType Type;
};

} //!_set

} //!_code

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
namespace code
{
namespace set
{

template<typename TCategoryTrait>
using Value = typename _helper::_basic::_err::_sys::_tmpl::_categ::
    _defn::_type::_code::_set::_Value<TCategoryTrait>::Type;

} //!set

} //!code

} //!type

} //!defn

} //!categ

} //!tmpl

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_TMPL_CATEG_DEFN_TYPE_CODE_SET_VALUE_H_
