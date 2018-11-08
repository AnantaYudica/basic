#ifndef BASIC_ERROR_SYSTEM_CATEGORY_HAS_MMBR_FUNC_EQUIVALENT_H_
#define BASIC_ERROR_SYSTEM_CATEGORY_HAS_MMBR_FUNC_EQUIVALENT_H_

#include "../../../../../../macro/HasMemberFunction.h"

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
namespace _has
{
namespace _mmbr
{
namespace _func
{

__DEFINE_HAS_MMBR_FUNC_(_Equivalent, __Equivalent, TCategoryTrait, TRet, TArgs, 
    const,,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    Equivalent);

} //!_func

} //!_mmbr

} //!_has

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
namespace has
{
namespace mmbr
{
namespace func
{

template<typename TCategoryTrait, typename TCode, typename TCondition>
using Equivalent = _helper::_basic::_error::_system::_category::_has::
    _mmbr::_func::_Equivalent<TCategoryTrait, bool, const TCode&, 
    const TCondition&>;

} //!func

} //!mmbr

} //!has

} //!category

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_CATEGORY_HAS_MMBR_FUNC_EQUIVALENT_H_
