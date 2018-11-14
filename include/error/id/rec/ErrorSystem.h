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
    ErrorSystem() noexcept;
    ErrorSystem(const CategoryValueType& category_value, 
        const CodeValueType& code_value) noexcept;
public:
    ErrorSystem(const ErrorSystem<TCategoryValue, TCodeValue>& cpy) noexcept;
    ErrorSystem(ErrorSystem<TCategoryValue, TCodeValue>&& mov) noexcept;
public:
    const CategoryValueType& Category() const noexcept;
    const CodeValueType& Code() const noexcept;
};

template<typename TCategoryValue, typename TCodeValue>
ErrorSystem<TCategoryValue, TCodeValue>::ErrorSystem() noexcept :
    m_categoryValue{0},
    m_codeValue{0}
{}

template<typename TCategoryValue, typename TCodeValue>
ErrorSystem<TCategoryValue, TCodeValue>::
    ErrorSystem(const CategoryValueType& category_value, 
        const CodeValueType& code_value) noexcept :
            m_categoryValue{category_value},
            m_codeValue{code_value}
{}

template<typename TCategoryValue, typename TCodeValue>
ErrorSystem<TCategoryValue, TCodeValue>::
    ErrorSystem(const ErrorSystem<TCategoryValue, TCodeValue>& cpy) noexcept :
        m_categoryValue{cpy.m_categoryValue},
        m_codeValue{cpy.m_codeValue}
{}

template<typename TCategoryValue, typename TCodeValue>
ErrorSystem<TCategoryValue, TCodeValue>::
    ErrorSystem(ErrorSystem<TCategoryValue, TCodeValue>&& mov) noexcept :
        m_categoryValue{std::move(mov.m_categoryValue)},
        m_codeValue{std::move(mov.m_codeValue)}
{}

template<typename TCategoryValue, typename TCodeValue>
const typename ErrorSystem<TCategoryValue, TCodeValue>::CategoryValueType& 
ErrorSystem<TCategoryValue, TCodeValue>::Category() const noexcept
{
    return m_categoryValue;
}

template<typename TCategoryValue, typename TCodeValue>
const typename ErrorSystem<TCategoryValue, TCodeValue>::CodeValueType& 
ErrorSystem<TCategoryValue, TCodeValue>::Code() const noexcept
{
    return m_codeValue;
}

} //!rec

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_REC_ERRORSYSTEM_H_
