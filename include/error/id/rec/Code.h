#ifndef BASIC_ERROR_ID_REC_CODE_H_
#define BASIC_ERROR_ID_REC_CODE_H_

#include <utility>
#include <type_traits>

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
    constexpr Code(const TErrorCodeValue& val) noexcept;
    template<typename _TErrorSystemCodeValue = TErrorSystemCodeValue,
        typename = typename std::enable_if<!std::is_same<
            _TErrorSystemCodeValue, TErrorCodeValue>::value>::type>
    constexpr Code(const TErrorSystemCodeValue& val) noexcept;
    Code(const Code<TErrorCodeValue, 
        TErrorSystemCodeValue>& cpy) noexcept;
    Code(Code<TErrorCodeValue, 
        TErrorSystemCodeValue>&& mov) noexcept;

    Code<TErrorCodeValue, TErrorSystemCodeValue> & 
    operator=(const Code<TErrorCodeValue, 
            TErrorSystemCodeValue> & cpy) noexcept;
    Code<TErrorCodeValue, TErrorSystemCodeValue> & 
    operator=(Code<TErrorCodeValue, 
            TErrorSystemCodeValue> && mov) noexcept;

    Code<TErrorCodeValue, TErrorSystemCodeValue> &
    operator=(const TErrorCodeValue & val) noexcept;
    template<typename _TErrorSystemCodeValue = TErrorSystemCodeValue,
        typename = typename std::enable_if<!std::is_same<
            _TErrorSystemCodeValue, TErrorCodeValue>::value>::type>
    Code<TErrorCodeValue, TErrorSystemCodeValue> &
    operator=(const TErrorSystemCodeValue & val) noexcept;
};

template<typename TErrorCodeValue, typename TErrorSystemCodeValue>
constexpr Code<TErrorCodeValue, TErrorSystemCodeValue>::Code() noexcept
{}

template<typename TErrorCodeValue, typename TErrorSystemCodeValue>
constexpr Code<TErrorCodeValue, TErrorSystemCodeValue>::
    Code(const TErrorCodeValue& val) noexcept :
        Error(val)
{}

template<typename TErrorCodeValue, typename TErrorSystemCodeValue>
template<typename _TErrorSystemCodeValue, typename>
constexpr Code<TErrorCodeValue, TErrorSystemCodeValue>::
    Code(const TErrorSystemCodeValue& val) noexcept :
        ErrorSystem(val)
{}

template<typename TErrorCodeValue, typename TErrorSystemCodeValue>
Code<TErrorCodeValue, TErrorSystemCodeValue>::
    Code(const Code<TErrorCodeValue, TErrorSystemCodeValue>& cpy) noexcept :
        Error(cpy.Error)
{
    ErrorSystem = cpy.ErrorSystem;
}

template<typename TErrorCodeValue, typename TErrorSystemCodeValue>
Code<TErrorCodeValue, TErrorSystemCodeValue>::
    Code(Code<TErrorCodeValue, TErrorSystemCodeValue>&& mov) noexcept :
        Error(mov.Error)
{
    ErrorSystem = mov.ErrorSystem;
    mov.Error = Code<TErrorCodeValue, TErrorSystemCodeValue>{}.Error;
    mov.ErrorSystem = Code<TErrorCodeValue, 
        TErrorSystemCodeValue>{}.ErrorSystem;
}

template<typename TErrorCodeValue, typename TErrorSystemCodeValue>
Code<TErrorCodeValue, TErrorSystemCodeValue> & 
Code<TErrorCodeValue, TErrorSystemCodeValue>::
    operator=(const Code<TErrorCodeValue, 
        TErrorSystemCodeValue> & cpy) noexcept
{
    this->Error = cpy.Error;
    this->ErrorSystem = cpy.ErrorSystem;
    return *this;
}

template<typename TErrorCodeValue, typename TErrorSystemCodeValue>
Code<TErrorCodeValue, TErrorSystemCodeValue> & 
Code<TErrorCodeValue, TErrorSystemCodeValue>::operator=(Code<TErrorCodeValue, 
    TErrorSystemCodeValue> && mov) noexcept
{
    this->Error = mov.Error;
    this->ErrorSystem = mov.ErrorSystem;
    mov.Error = Code<TErrorCodeValue, TErrorSystemCodeValue>{}.Error;
    mov.ErrorSystem = Code<TErrorCodeValue, 
        TErrorSystemCodeValue>{}.ErrorSystem;
    return *this;
}

template<typename TErrorCodeValue, typename TErrorSystemCodeValue>
Code<TErrorCodeValue, TErrorSystemCodeValue> &
Code<TErrorCodeValue, TErrorSystemCodeValue>::
        operator=(const TErrorCodeValue & val) noexcept
{
    this->Error = val;
    return *this;
}

template<typename TErrorCodeValue, typename TErrorSystemCodeValue>
template<typename _TErrorSystemCodeValue, typename>
Code<TErrorCodeValue, TErrorSystemCodeValue> &
Code<TErrorCodeValue, TErrorSystemCodeValue>::
    operator=(const TErrorSystemCodeValue & val) noexcept
{
    this->ErrorSystem = val;
    return *this;
}

} //!rec

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_REC_CODE_H_
