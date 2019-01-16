#ifndef BASIC_ERROR_EXCEPTION_LOGIC_LENGTH_H_
#define BASIC_ERROR_EXCEPTION_LOGIC_LENGTH_H_

#include "../Logic.h"
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
namespace logic
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class Length : public exception::Logic
{
public:
    typedef typename exception::Logic::TriggerType TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
protected:
    inline Length() noexcept;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline Length(const CharType * message) noexcept;
public:
    inline Length(const CharType * message, const char* file, 
        const std::size_t & line) noexcept;

#else

public:
    inline Length(const CharType * message) noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    inline Length(const Length & cpy) noexcept;
    inline Length(Length && mov) noexcept;
public:
    inline Length & operator=(const Length &) = delete;
    inline Length & operator=(Length &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const error::intf::Output & 
    operator>>(OutputType& out) const noexcept;
};

inline Length::Length() noexcept :
    TriggerType(constant::error::logic_length_id),
    exception::Logic("Domain Logic Length")
{}

inline Length::Length(const CharType * message) noexcept :
    TriggerType(constant::error::logic_length_id),
    exception::Logic(message)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

inline Length::Length(const CharType * message, const char* file, 
    const std::size_t& line) noexcept :
        TriggerType(constant::error::logic_length_id, file, line),
        exception::Logic(message)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

inline Length::Length(const Length & cpy) noexcept :
    TriggerType(cpy),
    exception::Logic(cpy)
{}

inline Length::Length(Length && mov) noexcept :
    TriggerType(std::move(mov)),
    exception::Logic(std::move(mov))
{}

inline const typename Length::CharType * Length::Message() const noexcept
{
    return exception::Logic::Message();
}

inline const error::intf::Output & 
Length::operator>>(OutputType & out) const noexcept
{
    exception::Logic::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

using Length = std::length_error;

#endif //!USING_STANDARD_EXCEPTION

} //!logic

} //!exception

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const std::length_error& e) noexcept
{
    return Standard(constant::error::logic_length_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_LOGIC_LENGTH_H_
