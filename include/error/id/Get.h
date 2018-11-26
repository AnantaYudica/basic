#ifndef BASIC_ERROR_ID_GET_H_
#define BASIC_ERROR_ID_GET_H_

#include "../../macro/HasMemberFunction.h"
#include "../Identification.h"

#include <type_traits>

namespace _helper
{
namespace _basic
{
namespace _error
{
namespace _id
{
namespace _has
{
namespace _mmbr
{
namespace _func
{

__DEFINE_HAS_MMBR_FUNC_(_GetIdentification, __GetIdentification, T, TRet, 
    TArgs, const,,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    GetIdentification);

} //!_func

} //!_mmbr

} //!_has

} //!_id

} //!_error

} //!_basic

} //!_helper

namespace basic
{
namespace error
{
namespace id
{

template<typename TException>
constexpr typename std::enable_if<_helper::_basic::_error::_id::_has::
    _mmbr::_func::_GetIdentification<TException, const Identification&>::Value,
    Identification>::type Get(const TException& e) noexcept
{
    return e.GetIdentification();
}

template<typename TException>
constexpr typename std::enable_if<!_helper::_basic::_error::_id::_has::
    _mmbr::_func::_GetIdentification<TException, const Identification&>::Value,
    Identification>::type Get(const TException& e) noexcept
{
    return {};
}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_GET_H_
