#ifndef BASIC_ERROR_ID_REC_ERROR_H_
#define BASIC_ERROR_ID_REC_ERROR_H_

#include <utility>

namespace basic
{
namespace error
{
namespace id
{
namespace rec
{

template<typename TCodeValue>
class Error
{
public:
    typedef TCodeValue CodeValueType;
private:
    CodeValueType m_codeValue;
public:
    Error() noexcept;
    Error(const CodeValueType& code_value) noexcept;
public:
    Error(const Error<TCodeValue>& cpy) noexcept;
    Error(Error<TCodeValue>&& mov) noexcept;
public:
    Error<TCodeValue> & operator=(const Error<TCodeValue> & cpy) noexcept;
    Error<TCodeValue> & operator=(Error<TCodeValue> && mov) noexcept;
public:
    Error<TCodeValue> & operator=(const CodeValueType & code_value) noexcept;
public:
    const CodeValueType& Code() const noexcept;
};

template<typename TCodeValue>
Error<TCodeValue>::Error() noexcept :
    m_codeValue{0}
{}

template<typename TCodeValue>
Error<TCodeValue>::Error(const CodeValueType& code_value) noexcept :
    m_codeValue{code_value}
{}

template<typename TCodeValue>
Error<TCodeValue>::Error(const Error<TCodeValue>& cpy) noexcept :
    m_codeValue(cpy.m_codeValue)
{}

template<typename TCodeValue>
Error<TCodeValue>::Error(Error<TCodeValue>&& mov) noexcept :
    m_codeValue(std::move(mov.m_codeValue))
{
    mov.m_codeValue = Error<TCodeValue>{}.m_codeValue;
}

template<typename TCodeValue>
Error<TCodeValue> & Error<TCodeValue>::
    operator=(const Error<TCodeValue> & cpy) noexcept
{
    this->m_codeValue = cpy.m_codeValue;
    return *this;
}

template<typename TCodeValue>
Error<TCodeValue> & Error<TCodeValue>::
    operator=(Error<TCodeValue> && mov) noexcept
{
    this->m_codeValue = mov.m_codeValue;
    mov.m_codeValue = Error<TCodeValue>{}.m_codeValue;
    return *this;
}

template<typename TCodeValue>
Error<TCodeValue> & Error<TCodeValue>::
    operator=(const CodeValueType & code_value) noexcept
{
    this->m_codeValue = code_value;
    return *this;
}

template<typename TCodeValue>
const typename Error<TCodeValue>::CodeValueType& 
Error<TCodeValue>::Code() const noexcept
{
    return m_codeValue;
}

} //!rec

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_REC_ERROR_H_
