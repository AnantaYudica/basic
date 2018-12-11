#ifndef BASIC_ERROR_EXCEPTION_RUNTIME_OVERFLOW_H_
#define BASIC_ERROR_EXCEPTION_RUNTIME_OVERFLOW_H_

#include "../Runtime.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../output/Operator.h"
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
    typedef defn::type::Output OutputValueType;
protected:
    Overflow() noexcept;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    Overflow(const CharType * message) noexcept;
public:
    Overflow(const CharType * message, const char * file, 
        const std::size_t & line) noexcept;

#else

public:
    Overflow(const CharType * message) noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    Overflow(const Overflow & cpy) noexcept;
    Overflow(Overflow && mov) noexcept;
public:
    Overflow & operator=(const Overflow &) = delete;
    Overflow & operator=(Overflow &&) = delete;
public:
    virtual const CharType * Message() const noexcept;
protected:
    virtual OutputValueType & Output(OutputValueType & out) const noexcept;
};

Overflow::Overflow() noexcept :
    TriggerType(constant::error::runtime_overflow_id),
    exception::Runtime("Overflow Runtime Exception")
{}

Overflow::Overflow(const CharType * message) noexcept :
    TriggerType(constant::error::runtime_overflow_id),
    exception::Runtime(message)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

Overflow::Overflow(const CharType * message, const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(constant::error::runtime_overflow_id, file, line),
        exception::Runtime(message)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

Overflow::Overflow(const Overflow & cpy) noexcept :
    TriggerType(cpy),
    exception::Runtime(cpy)
{}

Overflow::Overflow(Overflow && mov) noexcept :
    TriggerType(std::move(mov)),
    exception::Runtime(std::move(mov))
{}

const typename Overflow::CharType * Overflow::Message() const noexcept
{
    return exception::Runtime::Message();
}

typename Overflow::OutputValueType & 
Overflow::Output(OutputValueType & out) const noexcept
{
    return exception::Runtime::Output(out);
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
typename enable_if::tag::Trigger<TTagError>::Type 
Get(const std::overflow_error & e)
{
    return Standard(constant::error::runtime_overflow_id);
}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_RUNTIME_OVERFLOW_H_
