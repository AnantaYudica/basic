#ifndef BASIC_ERR_SYS_TMPL_CATEG_HAS_MMBR_FUNC_DEFAULTCONDITIONVALUE_H_
#define BASIC_ERR_SYS_TMPL_CATEG_HAS_MMBR_FUNC_DEFAULTCONDITIONVALUE_H_

#include "../../../../../../../macro/HasMemberFunction.h"
#include "../../../../../../defn/type/sys/cond/Value.h"

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
namespace _has
{
namespace _mmbr
{
namespace _func
{

__DEFINE_HAS_MMBR_FUNC_(_DefaultConditionValue, __DefaultConditionValue, 
    TCategoryTrait, TRet, TArgs, const,,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, 
    PROTO_FUNC_T_RET_NAME_,, DefaultConditionValue);

} //!_func

} //!_mmbr

} //!_has

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
namespace has
{
namespace mmbr
{
namespace func
{

template<typename TCategoryTrait>
using DefaultConditionValue = _helper::_basic::_err::_sys::_tmpl::_categ::
    _has::_mmbr::_func::_DefaultConditionValue<TCategoryTrait, err::defn::type::
    sys::cond::Value>;

} //!func

} //!mmbr

} //!has

} //!categ

} //!tmpl

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_TMPL_CATEG_HAS_MMBR_FUNC_DEFAULTCONDITIONVALUE_H_
