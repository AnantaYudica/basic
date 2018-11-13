#ifndef BASIC_ERROR_ID_RECORD_H_
#define BASIC_ERROR_ID_RECORD_H_

#include "Flag.h"

#include "rec/Code.h"
#include "rec/Error.h"
#include "rec/SystemError.h"

#include <utility>

namespace basic
{
namespace error
{
namespace id
{

template<typename TErrorCodeValue, typename TSystemErrorCategoryValue, 
    typename TSystemErrorCodeValue>
class Record
{
public:
    typedef TErrorCodeValue ErrorCodeValueType;
    typedef TSystemErrorCategoryValue SystemErrorCategoryValueType;
    typedef TSystemErrorCodeValue SystemErrorCodeValueType;
public:
    typedef rec::Code<ErrorCodeValueType, 
        SystemErrorCodeValueType> UnionCodeType;
public:
    typedef rec::Error<ErrorCodeValueType> ErrorType;
    typedef rec::SystemError<SystemErrorCategoryValueType,
        SystemErrorCodeValueType> SystemErrorType;
private:
    const SystemErrorCategoryValueType m_systemErrorCategoryValue;
    const UnionCodeType m_codeValue;
public:
    constexpr Record() noexcept;
    constexpr Record(const ErrorCodeValueType& error_code_val) noexcept;
    constexpr Record(const flag::System&,
        const SystemErrorCategoryValueType& system_error_category_val, 
        const SystemErrorCodeValueType& system_error_code_val) noexcept;
public:
    Record(const Record<TErrorCodeValue, TSystemErrorCategoryValue,
        TSystemErrorCodeValue>& cpy) noexcept;
    Record(Record<TErrorCodeValue, TSystemErrorCategoryValue,
        TSystemErrorCodeValue>&& mov) noexcept;
public:
    ErrorType Error() const noexcept;
    SystemErrorType SystemError() const noexcept;
};

template<typename TErrorCodeValue, typename TSystemErrorCategoryValue, 
    typename TSystemErrorCodeValue>
constexpr Record<TErrorCodeValue, TSystemErrorCategoryValue,
    TSystemErrorCodeValue>::Record() noexcept :
        m_systemErrorCategoryValue{0},
        m_codeValue()
{}

template<typename TErrorCodeValue, typename TSystemErrorCategoryValue, 
    typename TSystemErrorCodeValue>
constexpr Record<TErrorCodeValue, TSystemErrorCategoryValue,
    TSystemErrorCodeValue>::
        Record(const ErrorCodeValueType& error_code_val) noexcept :
            m_systemErrorCategoryValue{0},
            m_codeValue(error_code_val, 0)
{}

template<typename TErrorCodeValue, typename TSystemErrorCategoryValue, 
    typename TSystemErrorCodeValue>
constexpr Record<TErrorCodeValue, TSystemErrorCategoryValue,
    TSystemErrorCodeValue>::Record(const flag::System&,
        const SystemErrorCategoryValueType& system_error_category_val, 
        const SystemErrorCodeValueType& system_error_code_val) noexcept :
            m_systemErrorCategoryValue{system_error_category_val},
            m_codeValue(0, system_error_code_val)
{}

template<typename TErrorCodeValue, typename TSystemErrorCategoryValue, 
    typename TSystemErrorCodeValue>
Record<TErrorCodeValue, TSystemErrorCategoryValue,
    TSystemErrorCodeValue>::Record(const Record<TErrorCodeValue, 
        TSystemErrorCategoryValue, TSystemErrorCodeValue>& cpy) noexcept :
            m_systemErrorCategoryValue(cpy.m_systemErrorCategoryValue),
            m_codeValue(cpy.m_codeValue)
{}

template<typename TErrorCodeValue, typename TSystemErrorCategoryValue, 
    typename TSystemErrorCodeValue>
Record<TErrorCodeValue, TSystemErrorCategoryValue,
    TSystemErrorCodeValue>::Record(Record<TErrorCodeValue, 
        TSystemErrorCategoryValue, TSystemErrorCodeValue>&& mov) noexcept :
            m_systemErrorCategoryValue(std::move(mov.
                m_systemErrorCategoryValue)),
            m_codeValue(std::move(mov.m_codeValue))
{}

template<typename TErrorCodeValue, typename TSystemErrorCategoryValue, 
    typename TSystemErrorCodeValue>
typename Record<TErrorCodeValue, TSystemErrorCategoryValue,
    TSystemErrorCodeValue>::ErrorType 
Record<TErrorCodeValue, TSystemErrorCategoryValue,
    TSystemErrorCodeValue>::Error() const noexcept
{
    return ErrorType(m_codeValue.Error);
}

template<typename TErrorCodeValue, typename TSystemErrorCategoryValue, 
    typename TSystemErrorCodeValue>
typename Record<TErrorCodeValue, TSystemErrorCategoryValue,
    TSystemErrorCodeValue>::SystemErrorType 
Record<TErrorCodeValue, TSystemErrorCategoryValue,
    TSystemErrorCodeValue>::SystemError() const noexcept
{
    return SystemErrorType(m_systemErrorCategoryValue, 
        m_codeValue.SystemError);
}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_RECORD_H_
