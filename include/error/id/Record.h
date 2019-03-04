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
    typedef id::Flag FlagType;
public:
    typedef TErrorCodeValue ErrorCodeValueType;
    typedef TErrorSystemCategoryValue ErrorSystemCategoryValueType;
    typedef TErrorSystemCodeValue ErrorSystemCodeValueType;
public:
    typedef rec::Error<ErrorCodeValueType> ErrorType;
    typedef rec::ErrorSystem<ErrorSystemCategoryValueType,
        ErrorSystemCodeValueType> ErrorSystemType;
public:
    typedef rec::Code<TErrorCodeValue, TErrorSystemCodeValue> UnionCodeType;
private:
    FlagType m_flag;
    ErrorSystemCategoryValueType m_categ;
    UnionCodeType m_code;
public:
    static constexpr std::size_t MaximumAllocation() noexcept;
public:
    constexpr Record(const FlagType & flag) noexcept;
    constexpr Record(const FlagType & flag, 
        const ErrorCodeValueType& error_code_val) noexcept;
    constexpr Record(const FlagType & flag,
        const ErrorSystemCategoryValueType& error_system_categ_val, 
        const ErrorSystemCodeValueType& error_system_code_val) noexcept;
    constexpr Record(const FlagType & flag, const Record<TErrorCodeValue, 
        TErrorSystemCategoryValue, TErrorSystemCodeValue> & record) noexcept;
public:
    constexpr Record(const Record<TErrorCodeValue, TErrorSystemCategoryValue,
        TErrorSystemCodeValue> & cpy) noexcept;
    Record(Record<TErrorCodeValue, TErrorSystemCategoryValue,
        TErrorSystemCodeValue> && mov) noexcept;
public:
    Record<TErrorCodeValue, TErrorSystemCategoryValue,
        TErrorSystemCodeValue> & 
    operator=(const Record<TErrorCodeValue, TErrorSystemCategoryValue, 
        TErrorSystemCodeValue> &) = delete;
    Record<TErrorCodeValue, TErrorSystemCategoryValue,
        TErrorSystemCodeValue> & 
    operator=(Record<TErrorCodeValue, TErrorSystemCategoryValue, 
        TErrorSystemCodeValue> &&) = delete;
public:
    constexpr const FlagType & Flag() const noexcept; 
    constexpr ErrorType Error() const noexcept;
    constexpr ErrorSystemType ErrorSystem() const noexcept;
};

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue>
constexpr std::size_t Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::MaximumAllocation() noexcept
{
    return sizeof(FlagType) + sizeof(ErrorSystemCategoryValueType) +
        sizeof(UnionCodeType);
}

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue>
constexpr Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::Record(const FlagType & flag) noexcept :
        m_flag(flag),
        m_categ(0),
        m_code(0)
{}

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue>
constexpr Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::Record(const FlagType & flag, 
        const ErrorCodeValueType& error_code_val) noexcept :
            m_flag(flag),
            m_categ(0),
            m_code(error_code_val)
{}

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue>
constexpr Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::Record(const FlagType & flag,
        const ErrorSystemCategoryValueType& error_system_categ_val, 
        const ErrorSystemCodeValueType& error_system_code_val) noexcept :
            m_flag(flag),
            m_categ(error_system_categ_val),
            m_code(error_system_code_val)
{}

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue>
constexpr Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::Record(const FlagType & flag, 
        const Record<TErrorCodeValue, TErrorSystemCategoryValue, 
        TErrorSystemCodeValue> & record) noexcept :
            m_flag(flag),
            m_categ(record.m_categ),
            m_code(record.m_code)
{}

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue>
constexpr Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::Record(const Record<TErrorCodeValue, 
        TErrorSystemCategoryValue, TErrorSystemCodeValue> & cpy) noexcept :
            m_flag(cpy.m_flag),
            m_categ(cpy.m_categ),
            m_code(cpy.m_code)
{}

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue>
Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::Record(Record<TErrorCodeValue, 
        TErrorSystemCategoryValue, TErrorSystemCodeValue>&& mov) noexcept :
            m_flag(std::move(mov.m_flag)),
            m_categ(std::move(mov.m_categ)),
            m_code(std::move(mov.m_code))
{
    mov.m_categ = Record<TErrorCodeValue, TErrorSystemCategoryValue,
        TErrorSystemCodeValue>{basic::error::id::Flag{}}.m_categ;
    mov.m_code = Record<TErrorCodeValue, TErrorSystemCategoryValue,
        TErrorSystemCodeValue>{basic::error::id::Flag{}}.m_code;
}

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue>
constexpr const typename Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::FlagType &
Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::Flag() const noexcept
{
    return m_flag;
}

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue>
constexpr typename Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::ErrorType
Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::Error() const noexcept
{
    return ErrorType{m_code.Error};
}

template<typename TErrorCodeValue, typename TErrorSystemCategoryValue, 
    typename TErrorSystemCodeValue>
constexpr typename Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::ErrorSystemType
Record<TErrorCodeValue, TErrorSystemCategoryValue,
    TErrorSystemCodeValue>::ErrorSystem() const noexcept
{
    return ErrorSystemType{m_categ, m_code.ErrorSystem};
}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_RECORD_H_
