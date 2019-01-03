#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEGORY_DEFN_TYPE_CODE_SET_VALUE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEGORY_DEFN_TYPE_CODE_SET_VALUE_H_

#include "../../../../../../../defn/type/system/code/Value.h"

#include "../../../../has/mmbr/defn/type/CodeEnum.h"

namespace _helper
{
namespace _basic
{
namespace _error
{
namespace _system
{
namespace _tmpl
{
namespace _category
{
namespace _defn
{
namespace _type
{
namespace _code
{
namespace _set
{

template<typename TCategoryTrait, bool = basic::error::system::category::has::
    mmbr::defn::type::CodeEnum<TCategoryTrait>::Value>
struct _Value
{
    typedef basic::error::defn::type::system::code::Value Type;
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

} //!_category

} //!_tmpl

} //!_system

} //!_error

} //!_basic

} //!_helper

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
namespace defn
{
namespace type
{
namespace code
{
namespace set
{

template<typename TCategoryTrait>
using Value = typename _helper::_basic::_error::_system::_tmpl::_category::
    _defn::_type::_code::_set::_Value<TCategoryTrait>::Type;

} //!set

} //!code

} //!type

} //!defn

} //!category

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEGORY_DEFN_TYPE_CODE_SET_VALUE_H_
