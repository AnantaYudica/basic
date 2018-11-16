#ifndef BASIC_ERROR_ID_RECORD_H_
#define BASIC_ERROR_ID_RECORD_H_

#include "Flag.h"

#include "rec/Code.h"
#include "rec/Error.h"
#include "rec/ErrorSystem.h"

#include <utility>

namespace basic
{
namespace error
{
namespace id
{

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue>
class Record
{
public:
    typedef TErrorCodeValue ErrorCodeValueType;
    typedef TErrorSystemCategoryValue ErrorSystemCategoryValueType;
    typedef TErrorSystemCodeValue ErrorSystemCodeValueType;
public:
    typedef rec::Code<ErrorCodeValueType, 
        ErrorSystemCodeValueType> UnionCodeType;
public:
    typedef rec::Error<ErrorCodeValueType> ErrorType;
    typedef rec::ErrorSystem<ErrorSystemCategoryValueType,
        ErrorSystemCodeValueType> ErrorSystemType;
private:
    const ErrorSystemCategoryValueType m_errorSystemCategoryValue;
    const UnionCodeType m_codeValue;
public:
    constexpr Record() noexcept;
    constexpr Record(const ErrorCodeValueType& error_code_val) noexcept;
    constexpr Record(const flag::System&,
        const ErrorSystemCategoryValueType& error_system_category_val, 
        const ErrorSystemCodeValueType& error_system_code_val) noexcept;
public:
    constexpr Record(const Record<TErrorCodeValue, TErrorSystemCategoryValue,
        TErrorSystemCodeValue>& cpy) noexcept;
    constexpr Record(Record<TErrorCodeValue, TErrorSystemCategoryValue,
        TErrorSystemCodeValue>&& mov) noexcept;
public:
    ErrorType Error() const noexcept;
    ErrorSystemType ErrorSystem() const noexcept;
};

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue>
constexpr Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::Record() noexcept :
        m_errorSystemCategoryValue{0},
        m_codeValue()
{}

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue>
constexpr Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::
        Record(const ErrorCodeValueType& error_code_val) noexcept :
            m_errorSystemCategoryValue{0},
            m_codeValue(error_code_val, 0)
{}

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue>
constexpr Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::Record(const flag::System&,
        const ErrorSystemCategoryValueType& error_system_category_val, 
        const ErrorSystemCodeValueType& error_system_code_val) noexcept :
            m_errorSystemCategoryValue{error_system_category_val},
            m_codeValue(0, error_system_code_val)
{}

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue>
constexpr Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::Record(const Record<TErrorCodeValue, 
        TErrorSystemCategoryValue, TErrorSystemCodeValue>& cpy) noexcept :
            m_errorSystemCategoryValue(cpy.m_errorSystemCategoryValue),
            m_codeValue(cpy.m_codeValue)
{}

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue>
constexpr Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::Record(Record<TErrorCodeValue, 
        TErrorSystemCategoryValue, TErrorSystemCodeValue>&& mov) noexcept :
            m_errorSystemCategoryValue(std::move(mov.
                m_errorSystemCategoryValue)),
            m_codeValue(std::move(mov.m_codeValue))
{}

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue>
typename Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::ErrorType 
Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::Error() const noexcept
{
    return ErrorType(m_codeValue.Error);
}

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue>
typename Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::ErrorSystemType 
Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::ErrorSystem() const noexcept
{
    return ErrorSystemType(m_errorSystemCategoryValue, 
        m_codeValue.ErrorSystem);
}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_RECORD_H_
