#ifndef BASIC_ERR_SYS_TMPL_CATEG_HAS_MMBR_FUNC_TOCODEVALUE_H_
#define BASIC_ERR_SYS_TMPL_CATEG_HAS_MMBR_FUNC_TOCODEVALUE_H_

#include "../../../../../../../macro/HasMemberFunction.h"
#include "../../../../../../defn/type/sys/code/Value.h"

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

__DEFINE_HAS_MMBR_FUNC_(_ToCodeValue, __ToCodeValue, TCategoryTrait, TRet, 
    TArgs, const,,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    ToCodeValue);

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

template<typename TCategoryTrait, typename TCodeEnum>
using ToCodeValue = _helper::_basic::_err::_sys::_tmpl::_categ::
    _has::_mmbr::_func::_ToCodeValue<TCategoryTrait, 
    err::defn::type::sys::code::Value, const TCodeEnum &>;

} //!func

} //!mmbr

} //!has

} //!categ

} //!tmpl

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_TMPL_CATEG_HAS_MMBR_FUNC_TOCODEVALUE_H_
