#ifndef BASIC_ERROR_ID_REC_ERRORSYSTEM_H_
#define BASIC_ERROR_ID_REC_ERRORSYSTEM_H_

#include <utility>

namespace basic
{
namespace error
{
namespace id
{
namespace rec
{

template<typename TCategoryValue, typename TCodeValue>
class ErrorSystem
{
public:
    typedef TCategoryValue CategoryValueType;
    typedef TCodeValue CodeValueType;
private:
    CategoryValueType m_categoryValue;
    CodeValueType m_codeValue;
public:
    constexpr ErrorSystem(const CategoryValueType & category_value) noexcept;
    constexpr ErrorSystem(const CategoryValueType& category_value, 
        const CodeValueType& code_value) noexcept;
public:
    constexpr ErrorSystem(const ErrorSystem<TCategoryValue, 
        TCodeValue>& cpy) noexcept;
    ErrorSystem(ErrorSystem<TCategoryValue, TCodeValue>&& mov) noexcept;
public:
    ErrorSystem<TCategoryValue, TCodeValue> & 
    operator=(const ErrorSystem<TCategoryValue, TCodeValue> & cpy) noexcept;
    ErrorSystem<TCategoryValue, TCodeValue> & 
    operator=(ErrorSystem<TCategoryValue, TCodeValue> && mov) noexcept;
public:
    ErrorSystem<TCategoryValue, TCodeValue> & 
    operator=(const CodeValueType & code_value) noexcept;
public:
    constexpr const CategoryValueType& Category() const noexcept;
    constexpr const CodeValueType& Code() const noexcept;
};

template<typename TCategoryValue, typename TCodeValue>
constexpr ErrorSystem<TCategoryValue, TCodeValue>::
    ErrorSystem(const CategoryValueType & category_value) noexcept :
        m_categoryValue{category_value},
        m_codeValue{0}
{}

template<typename TCategoryValue, typename TCodeValue>
constexpr ErrorSystem<TCategoryValue, TCodeValue>::
    ErrorSystem(const CategoryValueType& category_value, 
        const CodeValueType& code_value) noexcept :
            m_categoryValue{category_value},
            m_codeValue{code_value}
{}

template<typename TCategoryValue, typename TCodeValue>
constexpr ErrorSystem<TCategoryValue, TCodeValue>::
    ErrorSystem(const ErrorSystem<TCategoryValue, TCodeValue>& cpy) noexcept :
        m_categoryValue{cpy.m_categoryValue},
        m_codeValue{cpy.m_codeValue}
{}

template<typename TCategoryValue, typename TCodeValue>
ErrorSystem<TCategoryValue, TCodeValue>::
    ErrorSystem(ErrorSystem<TCategoryValue, TCodeValue>&& mov) noexcept :
        m_categoryValue{std::move(mov.m_categoryValue)},
        m_codeValue{std::move(mov.m_codeValue)}
{
    mov.m_codeValue = ErrorSystem<TCategoryValue, 
        TCodeValue>{mov.m_categoryValue}.m_codeValue;
}

template<typename TCategoryValue, typename TCodeValue>
ErrorSystem<TCategoryValue, TCodeValue> & 
ErrorSystem<TCategoryValue, TCodeValue>::
    operator=(const ErrorSystem<TCategoryValue, TCodeValue> & cpy) noexcept
{
    this->m_categoryValue = cpy.m_categoryValue;
    this->m_codeValue = cpy.m_codeValue;
    return *this;
}

template<typename TCategoryValue, typename TCodeValue>
ErrorSystem<TCategoryValue, TCodeValue> & 
ErrorSystem<TCategoryValue, TCodeValue>::
    operator=(ErrorSystem<TCategoryValue, TCodeValue> && mov) noexcept
{
    this->m_categoryValue = std::move(mov.m_categoryValue);
    this->m_codeValue = std::move(mov.m_codeValue);
    mov.m_codeValue = ErrorSystem<TCategoryValue, 
        TCodeValue>{mov.m_categoryValue}.m_codeValue;
    return *this;
}

template<typename TCategoryValue, typename TCodeValue>
ErrorSystem<TCategoryValue, TCodeValue> & 
ErrorSystem<TCategoryValue, TCodeValue>::
    operator=(const CodeValueType & code_value) noexcept
{
    this->m_codeValue = code_value;
    return *this;
}

template<typename TCategoryValue, typename TCodeValue>
constexpr const typename ErrorSystem<TCategoryValue, TCodeValue>::
    CategoryValueType& 
ErrorSystem<TCategoryValue, TCodeValue>::Category() const noexcept
{
    return m_categoryValue;
}

template<typename TCategoryValue, typename TCodeValue>
constexpr const typename ErrorSystem<TCategoryValue, TCodeValue>::
    CodeValueType& 
ErrorSystem<TCategoryValue, TCodeValue>::Code() const noexcept
{
    return m_codeValue;
}

} //!rec

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_REC_ERRORSYSTEM_H_
