#ifndef BASIC_ERROR_ID_REC_CODE_H_
#define BASIC_ERROR_ID_REC_CODE_H_

#include <utility>

namespace basic
{
namespace error
{
namespace id
{
namespace rec
{

template<typename TErrorCodeValue, typename TSystemErrorCodeValue>
union Code
{
    TErrorCodeValue Error;
    TSystemErrorCodeValue SystemError;
    constexpr Code() noexcept;
    constexpr Code(const TErrorCodeValue& error, 
        const TSystemErrorCodeValue& system_error) noexcept;
    constexpr Code(const Code<TErrorCodeValue, 
        TSystemErrorCodeValue>& cpy) noexcept;
    constexpr Code(Code<TErrorCodeValue, 
        TSystemErrorCodeValue>&& mov) noexcept;
};

template<typename TErrorCodeValue, typename TSystemErrorCodeValue>
constexpr Code<TErrorCodeValue, TSystemErrorCodeValue>::Code() noexcept :
    Error{0},
    SystemError{0}
{}

template<typename TErrorCodeValue, typename TSystemErrorCodeValue>
constexpr Code<TErrorCodeValue, TSystemErrorCodeValue>::
    Code(const TErrorCodeValue& error, 
        const TSystemErrorCodeValue& system_error) noexcept :
            Error{error},
            SystemError{SystemError | system_error}
{}

template<typename TErrorCodeValue, typename TSystemErrorCodeValue>
constexpr Code<TErrorCodeValue, TSystemErrorCodeValue>::
    Code(const Code<TErrorCodeValue, TSystemErrorCodeValue>& cpy) noexcept :
        Error{cpy.Error},
        SystemError{SystemError | cpy.SystemError}
{}

template<typename TErrorCodeValue, typename TSystemErrorCodeValue>
constexpr Code<TErrorCodeValue, TSystemErrorCodeValue>::
    Code(Code<TErrorCodeValue, TSystemErrorCodeValue>&& mov) noexcept :
        Error{mov.Error},
        SystemError{SystemError | mov.SystemError}
{}

} //!rec

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_REC_CODE_H_
