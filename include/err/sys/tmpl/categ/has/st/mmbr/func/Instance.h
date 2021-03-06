#ifndef BASIC_ERR_SYS_TMPL_CATEG_HAS_ST_MMBR_FUNC_INSTANCE_H_
#define BASIC_ERR_SYS_TMPL_CATEG_HAS_ST_MMBR_FUNC_INSTANCE_H_

#include "../../../../../../../../macro/HasStaticMemberFunction.h"

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
namespace _st
{
namespace _mmbr
{
namespace _func
{

__DEFINE_HAS_STATIC_MMBR_FUNC_(_Instance, __Instance, TCategoryTrait, TRet, 
    TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    Instance);

} //!_func

} //!_mmbr

} //!_st

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
namespace st
{
namespace mmbr
{
namespace func
{

template<typename TCategoryTrait>
using Instance = _helper::_basic::_err::_sys::_tmpl::_categ::
    _has::_st::_mmbr::_func::_Instance<TCategoryTrait, TCategoryTrait>;

} //!func

} //!mmbr

} //!st

} //!has

} //!categ

} //!tmpl

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_TMPL_CATEG_HAS_ST_MMBR_FUNC_INSTANCE_H_
