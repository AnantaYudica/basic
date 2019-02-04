#ifndef BASIC_ERROR_EXCEPTION_RUNTIME_OVERFLOW_H_
#define BASIC_ERROR_EXCEPTION_RUNTIME_OVERFLOW_H_

#include "../Runtime.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/func/output/Operator.h"
#include "../../../constant/error/Identification.h"

#include <stdexcept>
#include <utility>

namespace basic
{
namespace error
{
namespace exception
{
namespace runtime
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class Overflow : public exception::Runtime
{
public:
    typedef typename error::Exception::TriggerType TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
protected:
    inline Overflow() noexcept;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline Overflow(const CharType * message) noexcept;
public:
    inline Overflow(const CharType * message, const char * file, 
        const std::size_t & line) noexcept;

#else

public:
    inline Overflow(const CharType * message) noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    inline Overflow(const Overflow & cpy) noexcept;
    inline Overflow(Overflow && mov) noexcept;
public:
    inline Overflow & operator=(const Overflow &) = delete;
    inline Overflow & operator=(Overflow &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const error::intf::Output & 
    operator>>(OutputType & out) const noexcept;
};

inline Overflow::Overflow() noexcept :
    TriggerType(constant::error::runtime_overflow_id),
    exception::Runtime("Overflow Runtime Exception")
{}

inline Overflow::Overflow(const CharType * message) noexcept :
    TriggerType(constant::error::runtime_overflow_id),
    exception::Runtime(message)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

inline Overflow::Overflow(const CharType * message, const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(constant::error::runtime_overflow_id, file, line),
        exception::Runtime(message)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

inline Overflow::Overflow(const Overflow & cpy) noexcept :
    TriggerType(cpy),
    exception::Runtime(cpy)
{}

inline Overflow::Overflow(Overflow && mov) noexcept :
    TriggerType(std::move(mov)),
    exception::Runtime(std::move(mov))
{}

inline const typename Overflow::CharType * Overflow::Message() const noexcept
{
    return exception::Runtime::Message();
}

inline const error::intf::Output & 
Overflow::operator>>(OutputType & out) const noexcept
{
    exception::Runtime::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

typedef std::overflow_error Overflow;

#endif //!USING_STANDARD_EXCEPTION

} //!runtime

} //!exception

namespace id
{

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const std::overflow_error & e)
{
    return Standard(constant::error::runtime_overflow_id);
}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_RUNTIME_OVERFLOW_H_
