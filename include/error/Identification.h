#ifndef BASIC_ERROR_IDENTIFICATION_H_
#define BASIC_ERROR_IDENTIFICATION_H_

#include "id/Record.h"

#include <utility>

namespace basic
{
namespace error
{

template<typename TRecord = id::Record>
class Identification : public TRecord
{
public:
    typedef TRecord RecordType;
    typedef typename RecordType::ErrorType ErrorType;
    typedef typename RecordType::SystemErrorType SystemErrorType;
public:
    constexpr Identification() noexcept;
    constexpr Identification(const RecordType& rec) noexcept;
public:
    Identification(const Identification<TRecord>& cpy) noexcept;
    Identification(Identification<TRecord>&& mov) noexcept;
public:
    ErrorType Error() const noexcept;
    SystemErrorType SystemError() const noexcept;
};

template<typename TRecord>
constexpr Identification<TRecord>::Identification() noexcept :
{}

template<typename TRecord>
constexpr Identification<TRecord>::Identification(const RecordType& rec) 
    noexcept :
        RecordType(rec)
{}

template<typename TRecord>
Identification<TRecord>::Identification(const Identification<TRecord>& cpy) 
    noexcept :
        RecordType(cpy)
{}

template<typename TRecord>
Identification<TRecord>::Identification(Identification<TRecord>&& mov) 
    noexcept :
        RecordType(std::move(RecordType))
{}

template<typename TRecord>
typename Identification<TRecord>::ErrorType 
Identification<TRecord>::Error() const noexcept
{
    return std::move(RecordType::Error());
}

template<typename TRecord>
typename Identification<TRecord>::SystemErrorType 
Identification<TRecord>::SystemError() const noexcept
{
    return std::move(RecordType::SystemError());
}

} //!error

} //!basic

#endif //!BASIC_ERROR_IDENTIFICATION_H_
