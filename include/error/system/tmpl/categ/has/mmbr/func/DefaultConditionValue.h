#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEG_HAS_MMBR_FUNC_DEFAULTCONDITIONVALUE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEG_HAS_MMBR_FUNC_DEFAULTCONDITIONVALUE_H_

#include "../../../../../../../macro/HasMemberFunction.h"
#include "../../../../../../defn/type/system/condition/Value.h"

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
namespace mmbr
{
namespace func
{

template<typename TCategoryTrait>
using DefaultConditionValue = _helper::_basic::_error::_system::_tmpl::_categ::
    _has::_mmbr::_func::_DefaultConditionValue<TCategoryTrait, error::defn::type::
    system::condition::Value>;

} //!func

} //!mmbr

} //!has

} //!categ

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEG_HAS_MMBR_FUNC_DEFAULTCONDITIONVALUE_H_
