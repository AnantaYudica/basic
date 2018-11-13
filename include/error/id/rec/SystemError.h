#ifndef BASIC_ERROR_ID_REC_SYSTEMERROR_H_
#define BASIC_ERROR_ID_REC_SYSTEMERROR_H_

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
class SystemError
{
public:
    typedef TCategoryValue CategoryValueType;
    typedef TCodeValue CodeValueType;
private:
    CategoryValueType m_categoryValue;
    CodeValueType m_codeValue;
public:
    SystemError() noexcept;
    SystemError(const CategoryValueType& category_value, 
        const CodeValueType& code_value) noexcept;
public:
    SystemError(const SystemError<TCategoryValue, TCodeValue>& cpy) noexcept;
    SystemError(SystemError<TCategoryValue, TCodeValue>&& mov) noexcept;
public:
    const CategoryValueType& Category() const noexcept;
    const CodeValueType& Code() const noexcept;
};

template<typename TCategoryValue, typename TCodeValue>
SystemError<TCategoryValue, TCodeValue>::SystemError() noexcept :
    m_categoryValue{0},
    m_codeValue{0}
{}

template<typename TCategoryValue, typename TCodeValue>
SystemError<TCategoryValue, TCodeValue>::
    SystemError(const CategoryValueType& category_value, 
        const CodeValueType& code_value) noexcept :
            m_categoryValue{category_value},
            m_codeValue{code_value}
{}

template<typename TCategoryValue, typename TCodeValue>
SystemError<TCategoryValue, TCodeValue>::
    SystemError(const SystemError<TCategoryValue, TCodeValue>& cpy) noexcept :
        m_categoryValue{cpy.m_categoryValue},
        m_codeValue{cpy.m_codeValue}
{}

template<typename TCategoryValue, typename TCodeValue>
SystemError<TCategoryValue, TCodeValue>::
    SystemError(SystemError<TCategoryValue, TCodeValue>&& mov) noexcept :
        m_categoryValue{std::move(mov.m_categoryValue)},
        m_codeValue{std::move(mov.m_codeValue)}
{}

template<typename TCategoryValue, typename TCodeValue>
const typename SystemError<TCategoryValue, TCodeValue>::CategoryValueType& 
SystemError<TCategoryValue, TCodeValue>::Category() const noexcept
{
    return m_categoryValue;
}

template<typename TCategoryValue, typename TCodeValue>
const typename SystemError<TCategoryValue, TCodeValue>::CodeValueType& 
SystemError<TCategoryValue, TCodeValue>::Code() const noexcept
{
    return m_codeValue;
}

} //!rec

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_REC_SYSTEMERROR_H_
