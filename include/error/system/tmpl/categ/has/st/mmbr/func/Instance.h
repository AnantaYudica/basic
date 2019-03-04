#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEG_HAS_ST_MMBR_FUNC_INSTANCE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEG_HAS_ST_MMBR_FUNC_INSTANCE_H_

#include "../../../../../../../../macro/HasStaticMemberFunction.h"

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
using Instance = _helper::_basic::_error::_system::_tmpl::_categ::
    _has::_st::_mmbr::_func::_Instance<TCategoryTrait, TCategoryTrait>;

} //!func

} //!mmbr

} //!st

} //!has

} //!categ

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEG_HAS_ST_MMBR_FUNC_INSTANCE_H_
