#ifndef BASIC_ERROR_SYSTEM_CATEGORY_DEFN_TYPE_CODE_SET_VALUE_H_
#define BASIC_ERROR_SYSTEM_CATEGORY_DEFN_TYPE_CODE_SET_VALUE_H_

#include "../../../../../defn/type/code/Value.h"

#include "../../../../has/mmbr/defn/type/CodeEnum.h"

namespace _helper
{
namespace _basic
{
namespace _error
{
namespace _system
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
    typedef basic::error::system::defn::type::code::Value Type;
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
using Value = typename _helper::_basic::_error::_system::_category::
    _defn::_type::_code::_set::_Value<TCategoryTrait>::Type;

} //!set

} //!code

} //!type

} //!defn

} //!category

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_CATEGORY_DEFN_TYPE_CODE_SET_VALUE_H_