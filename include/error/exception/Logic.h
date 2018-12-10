#ifndef BASIC_ERROR_EXCEPTION_LOGIC_H_
#define BASIC_ERROR_EXCEPTION_LOGIC_H_

#include "../Exception.h"
#include "../Identification.h"
#include "../id/Get.h"
#include "../id/Standard.h"
#include "../defn/type/Char.h"
#include "../defn/type/Output.h"
#include "../output/Operator.h"
#include "../msg/String.h"
#include "../../constant/error/Identification.h"

#include <stdexcept>
#include <utility>

namespace basic
{
namespace error
{
namespace exception
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class Logic : public error::Exception
{
public:
    typedef typename error::Exception::TriggerType TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputValueType;
public:
    typedef msg::String StringType;
private:
    StringType m_message;
protected:
    Logic() noexcept;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    Logic(const CharType * message) noexcept;
public:
    Logic(const CharType * message, const char * file, 
        const std::size_t & line) noexcept;

#else

public:
    Logic(const CharType * message) noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

protected:
    Logic(StringType && message) noexcept;
public:
    Logic(const Logic & cpy) noexcept;
    Logic(Logic && mov) noexcept;
public:
    Logic & operator=(const Logic &) = delete;
    Logic & operator=(Logic &&) = delete;
public:
    virtual const CharType * Message() const noexcept;
protected:
    virtual OutputValueType & Output(OutputValueType & out) const noexcept;
};

Logic::Logic() noexcept :
    TriggerType(constant::error::logic_id),
    m_message("Logic Exception")
{}

Logic::Logic(const CharType * message) noexcept :
    TriggerType(constant::error::logic_id),
    m_message(message)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

Logic::Logic(const CharType * message, const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(constant::error::logic_id, file, line),
        m_message(message)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

Logic::Logic(StringType && message) noexcept :
    TriggerType(constant::error::logic_id),
    m_message(std::move(message))
{}

Logic::Logic(const Logic & cpy) noexcept :
    TriggerType(cpy),
    m_message(cpy.m_message),
    error::Exception(cpy)
{}

Logic::Logic(Logic && mov) noexcept :
    TriggerType(std::move(mov)),
    m_message(std::move(mov.m_message)),
    error::Exception(std::move(mov))
{}

const typename Logic::CharType * Logic::Message() const noexcept
{
    if (m_message)
        return m_message.Value();
    return "Logic Exception";
}

typename Logic::OutputValueType & 
Logic::Output(OutputValueType & out) const noexcept
{
    error::Exception::Output(out);
    return out;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

using Logic = std::logic_error;

#endif //!USING_STANDARD_EXCEPTION

} //!exception

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger>
typename enable_if::tag::Trigger<TTagError>::Type 
Get(const std::logic_error & e) noexcept
{
    return Standard(constant::error::logic_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_LOGIC_H_
