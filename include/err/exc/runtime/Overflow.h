#ifndef BASIC_ERR_EXC_RUNTIME_OVERFLOW_H_
#define BASIC_ERR_EXC_RUNTIME_OVERFLOW_H_

#include "../Runtime.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/func/output/Operator.h"
#include "../../../defn/err/Identification.h"

#include <stdexcept>
#include <utility>

namespace basic
{
namespace err
{
namespace exc
{
namespace runtime
{

#ifdef USING_BASIC_ERR_EXCEPTION

class Overflow : public exc::Runtime
{
public:
    typedef typename err::Exception::TriggerType TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
protected:
    inline Overflow() noexcept;

#ifdef USING_BASIC_ERR_FILE_AND_LINE

protected:
    inline Overflow(const CharType * message) noexcept;
public:
    inline Overflow(const CharType * message, const char * file, 
        const std::size_t & line) noexcept;

#else

public:
    inline Overflow(const CharType * message) noexcept;

#endif //!USING_BASIC_ERR_FILE_AND_LINE

public:
    inline Overflow(const Overflow & cpy) noexcept;
    inline Overflow(Overflow && mov) noexcept;
public:
    inline Overflow & operator=(const Overflow &) = delete;
    inline Overflow & operator=(Overflow &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const err::intf::Output & 
    operator>>(OutputType & out) const noexcept;
};

inline Overflow::Overflow() noexcept :
#ifdef USING_BASIC_ERR_FILE_AND_LINE
    TriggerType(basic::defn::err::runtime_overflow_id,
        "unknown", static_cast<std::size_t>(-1)),
#else
    TriggerType(basic::defn::err::runtime_overflow_id),
#endif //USING_BASIC_ERR_FILE_AND_LINE
    exc::Runtime("Overflow Runtime Exception")
{}

inline Overflow::Overflow(const CharType * message) noexcept :
    TriggerType(basic::defn::err::runtime_overflow_id),
    exc::Runtime(message)
{}

#ifdef USING_BASIC_ERR_FILE_AND_LINE

inline Overflow::Overflow(const CharType * message, const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(basic::defn::err::runtime_overflow_id, file, line),
        exc::Runtime(message)
{}

#endif //!USING_BASIC_ERR_FILE_AND_LINE

inline Overflow::Overflow(const Overflow & cpy) noexcept :
    TriggerType(cpy),
    exc::Runtime(cpy)
{}

inline Overflow::Overflow(Overflow && mov) noexcept :
    TriggerType(std::move(mov)),
    exc::Runtime(std::move(mov))
{}

inline const typename Overflow::CharType * Overflow::Message() const noexcept
{
    return exc::Runtime::Message();
}

inline const err::intf::Output & 
Overflow::operator>>(OutputType & out) const noexcept
{
    exc::Runtime::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

typedef std::overflow_error Overflow;

#endif //!USING_STANDARD_EXCEPTION

} //!runtime

} //!exc

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const std::overflow_error & e)
{
    return Standard(basic::defn::err::runtime_overflow_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!err

} //!basic

#endif //!BASIC_ERR_EXC_RUNTIME_OVERFLOW_H_
