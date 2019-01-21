#ifndef BASIC_ERROR_EXCEPTION_RUNTIME_UNDERFLOW_H_
#define BASIC_ERROR_EXCEPTION_RUNTIME_UNDERFLOW_H_

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

class Underflow : public exception::Runtime
{
public:
    typedef typename error::Exception::TriggerType TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
protected:
    inline Underflow() noexcept;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline Underflow(const CharType * message) noexcept;
public:
    inline Underflow(const CharType * message, const char * file, 
        const std::size_t & line) noexcept;

#else

public:
    inline Underflow(const CharType * message) noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    inline Underflow(const Underflow & cpy) noexcept;
    inline Underflow(Underflow && mov) noexcept;
public:
    inline Underflow & operator=(const Underflow &) = delete;
    inline Underflow & operator=(Underflow &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const error::intf::Output & 
    operator>>(OutputType & out) const noexcept;
};

inline Underflow::Underflow() noexcept :
    TriggerType(constant::error::runtime_underflow_id),
    exception::Runtime("Underflow Runtime Exception")
{}

inline Underflow::Underflow(const CharType * message) noexcept :
    TriggerType(constant::error::runtime_underflow_id),
    exception::Runtime(message)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

inline Underflow::Underflow(const CharType * message, const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(constant::error::runtime_underflow_id, file, line),
        exception::Runtime(message)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

inline Underflow::Underflow(const Underflow & cpy) noexcept :
    TriggerType(cpy),
    exception::Runtime(cpy)
{}

inline Underflow::Underflow(Underflow && mov) noexcept :
    TriggerType(std::move(mov)),
    exception::Runtime(std::move(mov))
{}

inline const typename Underflow::CharType * Underflow::Message() const noexcept
{
    return exception::Runtime::Message();
}

inline const error::intf::Output & 
Underflow::operator>>(OutputType & out) const noexcept
{
    exception::Runtime::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

typedef std::underflow_error Underflow;

#endif //!USING_STANDARD_EXCEPTION

} //!runtime

} //!exception

namespace id
{

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const std::underflow_error & e)
{
    return Standard(constant::error::runtime_underflow_id);
}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_RUNTIME_UNDERFLOW_H_
