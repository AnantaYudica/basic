#ifndef BASIC_ERROR_SYS_TMPL_CATEG_HAS_MMBR_FUNC_TOCONDITIONVALUE_H_
#define BASIC_ERROR_SYS_TMPL_CATEG_HAS_MMBR_FUNC_TOCONDITIONVALUE_H_

#include "../../../../../../../macro/HasMemberFunction.h"
#include "../../../../../../defn/type/sys/cond/Value.h"

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

__DEFINE_HAS_MMBR_FUNC_(_ToConditionValue, __ToConditionValue, TCategoryTrait, 
    TRet, TArgs, const,,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, 
    PROTO_FUNC_T_RET_NAME_,, ToConditionValue);

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

template<typename TCategoryTrait, typename TConditionEnum>
using ToConditionValue = _helper::_basic::_error::_sys::_tmpl::_categ::
    _has::_mmbr::_func::_ToConditionValue<TCategoryTrait, 
    error::defn::type::sys::cond::Value, TConditionEnum>;

} //!func

} //!mmbr

} //!has

} //!categ

} //!tmpl

} //!sys

} //!error

} //!basic

#endif //!BASIC_ERROR_SYS_TMPL_CATEG_HAS_MMBR_FUNC_TOCONDITIONVALUE_H_
