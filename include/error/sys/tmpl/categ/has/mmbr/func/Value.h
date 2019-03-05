#ifndef BASIC_ERROR_SYS_TMPL_CATEG_HAS_MMBR_FUNC_VALUE_H_
#define BASIC_ERROR_SYS_TMPL_CATEG_HAS_MMBR_FUNC_VALUE_H_

#include "../../../../../../../macro/HasMemberFunction.h"

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
namespace has
{
namespace mmbr
{
namespace func
{

template<typename TCategoryTrait, typename TValue>
using Value = _helper::_basic::_error::_sys::_tmpl::_categ::
    _has::_mmbr::_func::_Value<TCategoryTrait, TValue>;

} //!func

} //!mmbr

} //!has

} //!categ

} //!tmpl

} //!sys

} //!error

} //!basic

#endif //!BASIC_ERROR_SYS_TMPL_CATEG_HAS_MMBR_FUNC_VALUE_H_
