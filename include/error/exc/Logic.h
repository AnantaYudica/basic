#ifndef BASIC_ERROR_EXC_LOGIC_H_
#define BASIC_ERROR_EXC_LOGIC_H_

#include "../Exception.h"
#include "../Identification.h"
#include "../id/Get.h"
#include "../id/Standard.h"
#include "../defn/type/Char.h"
#include "../defn/type/Output.h"
#include "../defn/func/output/Operator.h"
#include "../msg/String.h"
#include "../../defn/error/Identification.h"

#include <stdexcept>
#include <utility>

namespace basic
{
namespace error
{
namespace exc
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class Logic : public error::Exception
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
    inline Logic() noexcept;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline Logic(const CharType * message) noexcept;
public:
    inline Logic(const CharType * message, const char * file, 
        const std::size_t & line) noexcept;

#else

public:
    inline Logic(const CharType * message) noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline Logic(StringType && message) noexcept;
public:
    inline Logic(const Logic & cpy) noexcept;
    inline Logic(Logic && mov) noexcept;
public:
    inline Logic & operator=(const Logic &) = delete;
    inline Logic & operator=(Logic &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const error::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

inline Logic::Logic() noexcept :
    TriggerType(basic::defn::error::logic_id),
    m_message("Logic Exception")
{}

inline Logic::Logic(const CharType * message) noexcept :
    TriggerType(basic::defn::error::logic_id),
    m_message(message)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

inline Logic::Logic(const CharType * message, const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(basic::defn::error::logic_id, file, line),
        m_message(message)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

inline Logic::Logic(StringType && message) noexcept :
    TriggerType(basic::defn::error::logic_id),
    m_message(std::move(message))
{}

inline Logic::Logic(const Logic & cpy) noexcept :
    TriggerType(cpy),
    m_message(cpy.m_message),
    error::Exception(cpy)
{}

inline Logic::Logic(Logic && mov) noexcept :
    TriggerType(std::move(mov)),
    m_message(std::move(mov.m_message)),
    error::Exception(std::move(mov))
{}

inline const typename Logic::CharType * Logic::Message() const noexcept
{
    if (m_message)
        return m_message.Value();
    return "Logic Exception";
}

inline const error::intf::Output & 
Logic::operator>>(OutputType & out) const noexcept
{
    error::Exception::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

using Logic = std::logic_error;

#endif //!USING_STANDARD_EXCEPTION

} //!exc

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const std::logic_error & e) noexcept
{
    return Standard(basic::defn::error::logic_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXC_LOGIC_H_
