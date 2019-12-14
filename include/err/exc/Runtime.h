#ifndef BASIC_ERR_EXC_RUNTIME_H_
#define BASIC_ERR_EXC_RUNTIME_H_

#include "../Exception.h"
#include "../Identification.h"
#include "../id/Get.h"
#include "../id/Standard.h"
#include "../defn/type/Char.h"
#include "../defn/type/Output.h"
#include "../defn/func/output/Operator.h"
#include "../msg/String.h"
#include "../../defn/err/Identification.h"

#include <stdexcept>
#include <utility>

namespace basic
{
namespace err
{
namespace exc
{

#ifdef USING_BASIC_ERR_EXCEPTION

class Runtime : public err::Exception
{
public:
    typedef typename err::Exception::TriggerType TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
public:
    typedef msg::String StringType;
private:
    StringType m_message;
protected:
    inline Runtime() noexcept;

#ifdef USING_BASIC_ERR_FILE_AND_LINE

protected:
    inline Runtime(const CharType * message) noexcept;
public:
    inline Runtime(const CharType * message, const char* file, 
        const std::size_t& line) noexcept;

#else

public:
    inline Runtime(const CharType * message) noexcept;

#endif //!USING_BASIC_ERR_FILE_AND_LINE

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
    virtual inline const err::intf::Output & 
    operator>>(OutputType & out) const noexcept;
};

inline Runtime::Runtime() noexcept :
#ifdef USING_BASIC_ERR_FILE_AND_LINE
    TriggerType(basic::defn::err::logic_id,
        "unknown", static_cast<std::size_t>(-1)),
#else
    TriggerType(basic::defn::err::runtime_id),
#endif //!USING_BASIC_ERR_FILE_AND_LINE
    m_message("Runtime Exception")
{}

inline Runtime::Runtime(const CharType * message) noexcept :
    TriggerType(basic::defn::err::runtime_id),
    m_message(message)
{}

#ifdef USING_BASIC_ERR_FILE_AND_LINE

inline Runtime::Runtime(const CharType * message, const char* file, 
    const std::size_t& line) noexcept :
        TriggerType(basic::defn::err::runtime_id, file, line),
        m_message(message)
{}

#endif //!USING_BASIC_ERR_FILE_AND_LINE

inline Runtime::Runtime(StringType && message) noexcept :
    TriggerType(basic::defn::err::runtime_id),
    m_message(std::move(message))
{}

inline Runtime::Runtime(const Runtime & cpy) noexcept :
    TriggerType(cpy),
    err::Exception(cpy)
{}

inline Runtime::Runtime(Runtime && mov) noexcept :
    TriggerType(std::move(mov)),
    err::Exception(std::move(mov))
{}

inline const typename Runtime::CharType * Runtime::Message() const noexcept
{
    if (m_message)
        return m_message.Value();
    return "Runtime Exception";
}

inline const err::intf::Output & 
Runtime::operator>>(OutputType & out) const noexcept
{
    err::Exception::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERR_EXCEPTION

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
    return Standard(basic::defn::err::runtime_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!err

} //!basic

#endif //!BASIC_ERR_EXC_RUNTIME_H_
