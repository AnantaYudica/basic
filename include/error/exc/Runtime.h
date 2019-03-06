#ifndef BASIC_ERROR_EXC_RUNTIME_H_
#define BASIC_ERROR_EXC_RUNTIME_H_

#include "../Exception.h"
#include "../Identification.h"
#include "../id/Get.h"
#include "../id/Standard.h"
#include "../defn/type/Char.h"
#include "../defn/type/Output.h"
#include "../defn/func/output/Operator.h"
#include "../msg/String.h"
#include "../../constant/error/Identification.h"

#include <stdexcept>
#include <utility>

namespace basic
{
namespace error
{
namespace exc
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class Runtime : public error::Exception
{
public:
    typedef typename error::Exception::TriggerType TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
public:
    typedef msg::String StringType;
private:
    StringType m_message;
protected:
    inline Runtime() noexcept;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline Runtime(const CharType * message) noexcept;
public:
    inline Runtime(const CharType * message, const char* file, 
        const std::size_t& line) noexcept;

#else

public:
    inline Runtime(const CharType * message) noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline Runtime(StringType && message) noexcept;
public:
    inline Runtime(const Runtime & cpy) noexcept;
    inline Runtime(Runtime && mov) noexcept;
public:
    inline Runtime & operator=(const Runtime &) = delete;
    inline Runtime & operator=(Runtime &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const error::intf::Output & 
    operator>>(OutputType & out) const noexcept;
};

inline Runtime::Runtime() noexcept :
    TriggerType(constant::error::runtime_id),
    m_message("Runtime Exception")
{}

inline Runtime::Runtime(const CharType * message) noexcept :
    TriggerType(constant::error::runtime_id),
    m_message(message)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

inline Runtime::Runtime(const CharType * message, const char* file, 
    const std::size_t& line) noexcept :
        TriggerType(constant::error::runtime_id, file, line),
        m_message(message)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

inline Runtime::Runtime(StringType && message) noexcept :
    TriggerType(constant::error::runtime_id),
    m_message(std::move(message))
{}

inline Runtime::Runtime(const Runtime & cpy) noexcept :
    TriggerType(cpy),
    error::Exception(cpy)
{}

inline Runtime::Runtime(Runtime && mov) noexcept :
    TriggerType(std::move(mov)),
    error::Exception(std::move(mov))
{}

inline const typename Runtime::CharType * Runtime::Message() const noexcept
{
    if (m_message)
        return m_message.Value();
    return "Runtime Exception";
}

inline const error::intf::Output & 
Runtime::operator>>(OutputType & out) const noexcept
{
    error::Exception::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

typedef std::runtime_error Runtime;

#endif

} //!exc

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const std::runtime_error & e) noexcept
{
    return Standard(constant::error::runtime_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXC_RUNTIME_H_
