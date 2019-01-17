#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEGORY_HAS_MMBR_FUNC_VALUE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEGORY_HAS_MMBR_FUNC_VALUE_H_

#include "../../../../../../../macro/HasMemberFunction.h"

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
namespace _has
{
namespace _mmbr
{
namespace _func
{

__DEFINE_HAS_MMBR_FUNC_(_Value, __Value, TCategoryTrait, TRet, TArgs, const,,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Value);

} //!_func

} //!_mmbr

} //!_has

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
namespace has
{
namespace mmbr
{
namespace func
{

template<typename TCategoryTrait, typename TValue>
using Value = _helper::_basic::_error::_system::_tmpl::_category::
    _has::_mmbr::_func::_Value<TCategoryTrait, TValue>;

} //!func

} //!mmbr

} //!has

} //!category

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEGORY_HAS_MMBR_FUNC_VALUE_H_
