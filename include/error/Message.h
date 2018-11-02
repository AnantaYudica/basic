#ifndef BASIC_ERROR_MESSAGE_H_
#define BASIC_ERROR_MESSAGE_H_

#include "../macro/HasMemberFunction.h"
#include "../Error.h"

#include <type_traits>

namespace _helper
{
namespace _basic
{
namespace _error
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

} //!_error

} //!_basic

} //!_helper


namespace basic
{
namespace error
{

template<typename TError>
typename std::enable_if<
    _helper::_basic::_error::_msg::_has::_mmbr::_Message<TError, 
        BASIC_ERROR_OUTPUT_TYPE&, BASIC_ERROR_OUTPUT_TYPE&>::Value && 
    !_helper::_basic::_error::_msg::_has::_mmbr::_What<TError, 
        const char *>::Value, 
    BASIC_ERROR_OUTPUT_TYPE>::type& 
        Message(BASIC_ERROR_OUTPUT_TYPE& out, const TError& error)
{
    error.Message(out);
    return  out;
}

template<typename TError>
typename std::enable_if<
    !_helper::_basic::_error::_msg::_has::_mmbr::_Message<TError, 
        BASIC_ERROR_OUTPUT_TYPE&, BASIC_ERROR_OUTPUT_TYPE&>::Value && 
    _helper::_basic::_error::_msg::_has::_mmbr::_What<TError, 
        const char *>::Value, 
    BASIC_ERROR_OUTPUT_TYPE>::type& 
        Message(BASIC_ERROR_OUTPUT_TYPE& out, const TError& error)
{
    BASIC_ERROR_OUTPUT_OPERATOR(out, error.what());
    return out;
}

template<typename TError>
typename std::enable_if<
    _helper::_basic::_error::_msg::_has::_mmbr::_Message<TError, 
        BASIC_ERROR_OUTPUT_TYPE&, BASIC_ERROR_OUTPUT_TYPE&>::Value && 
    _helper::_basic::_error::_msg::_has::_mmbr::_What<TError, 
        const char *>::Value, 
    BASIC_ERROR_OUTPUT_TYPE>::type& 
        Message(BASIC_ERROR_OUTPUT_TYPE& out, const TError& error)
{
    BASIC_ERROR_OUTPUT_OPERATOR(out, error.what());
    return out;
}

} //!error

} //!basic

#endif //!BASIC_ERROR_MESSAGE_H_
