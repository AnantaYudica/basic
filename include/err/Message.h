#ifndef BASIC_ERR_MESSAGE_H_
#define BASIC_ERR_MESSAGE_H_

#include "../macro/HasMemberFunction.h"

#include <type_traits>

namespace _helper
{
namespace _basic
{
namespace _err
{
namespace _msg
{
namespace _has
{
namespace _mmbr
{

__DEFINE_HAS_MMBR_FUNC_(_Message, __Message, T, TRet, 
    TArgs, const,,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    Message);

__DEFINE_HAS_MMBR_FUNC_(_What, __What, T, TRet, 
    TArgs, const,,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    what);

} //!_mmbr

} //!_has

} //!_msg

} //!_err

} //!_basic

} //!_helper


namespace basic
{
namespace err
{

template<typename TError>
typename std::enable_if<
    _helper::_basic::_err::_msg::_has::_mmbr::_Message<TError, 
        const char *>::Value && 
    !_helper::_basic::_err::_msg::_has::_mmbr::_What<TError, 
        const char *>::Value, 
    const char>::type * Message(const TError& err) noexcept
{
    return err.Message();
}

template<typename TError>
typename std::enable_if<
    !_helper::_basic::_err::_msg::_has::_mmbr::_Message<TError, 
        const char *>::Value && 
    _helper::_basic::_err::_msg::_has::_mmbr::_What<TError, 
        const char *>::Value, 
    const char>::type * Message(const TError& err) noexcept
{
    return err.what();
}

template<typename TError>
typename std::enable_if<
    _helper::_basic::_err::_msg::_has::_mmbr::_Message<TError, 
        const char *>::Value && 
    _helper::_basic::_err::_msg::_has::_mmbr::_What<TError, 
        const char *>::Value, 
    const char>::type * Message(const TError& err)
{
    return err.what();
}

} //!err

} //!basic

#endif //!BASIC_ERR_MESSAGE_H_
