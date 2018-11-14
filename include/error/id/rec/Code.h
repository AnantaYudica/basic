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

template<typename TErrorCodeValue, typename TErrorSystemCodeValue>
union Code
{
    TErrorCodeValue Error;
    TErrorSystemCodeValue ErrorSystem;
    constexpr Code() noexcept;
    constexpr Code(const TErrorCodeValue& error, 
        const TErrorSystemCodeValue& error_system) noexcept;
    constexpr Code(const Code<TErrorCodeValue, 
        TErrorSystemCodeValue>& cpy) noexcept;
    constexpr Code(Code<TErrorCodeValue, 
        TErrorSystemCodeValue>&& mov) noexcept;
};

template<typename TErrorCodeValue, typename TErrorSystemCodeValue>
constexpr Code<TErrorCodeValue, TErrorSystemCodeValue>::Code() noexcept :
    Error{0},
    ErrorSystem{0}
{}

template<typename TErrorCodeValue, typename TErrorSystemCodeValue>
constexpr Code<TErrorCodeValue, TErrorSystemCodeValue>::
    Code(const TErrorCodeValue& error, 
        const TErrorSystemCodeValue& error_system) noexcept :
            Error{error},
            ErrorSystem{ErrorSystem | error_system}
{}

template<typename TErrorCodeValue, typename TErrorSystemCodeValue>
constexpr Code<TErrorCodeValue, TErrorSystemCodeValue>::
    Code(const Code<TErrorCodeValue, TErrorSystemCodeValue>& cpy) noexcept :
        Error{cpy.Error},
        ErrorSystem{ErrorSystem | cpy.ErrorSystem}
{}

template<typename TErrorCodeValue, typename TErrorSystemCodeValue>
constexpr Code<TErrorCodeValue, TErrorSystemCodeValue>::
    Code(Code<TErrorCodeValue, TErrorSystemCodeValue>&& mov) noexcept :
        Error{mov.Error},
        ErrorSystem{ErrorSystem | mov.ErrorSystem}
{}

} //!rec

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_REC_CODE_H_
