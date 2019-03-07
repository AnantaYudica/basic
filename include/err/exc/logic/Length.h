#ifndef BASIC_ERR_EXC_LOGIC_LENGTH_H_
#define BASIC_ERR_EXC_LOGIC_LENGTH_H_

#include "../Logic.h"
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
namespace logic
{

#ifdef USING_BASIC_ERR_EXCEPTION

class Length : public exc::Logic
{
public:
    typedef typename exc::Logic::TriggerType TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
protected:
    inline Length() noexcept;

#ifdef USING_BASIC_ERR_FILE_AND_LINE

protected:
    inline Length(const CharType * message) noexcept;
public:
    inline Length(const CharType * message, const char* file, 
        const std::size_t & line) noexcept;

#else

public:
    inline Length(const CharType * message) noexcept;

#endif //!USING_BASIC_ERR_FILE_AND_LINE

public:
    inline Length(const Length & cpy) noexcept;
    inline Length(Length && mov) noexcept;
public:
    inline Length & operator=(const Length &) = delete;
    inline Length & operator=(Length &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const err::intf::Output & 
    operator>>(OutputType& out) const noexcept;
};

inline Length::Length() noexcept :
    TriggerType(basic::defn::err::logic_length_id),
    exc::Logic("Domain Logic Length")
{}

inline Length::Length(const CharType * message) noexcept :
    TriggerType(basic::defn::err::logic_length_id),
    exc::Logic(message)
{}

#ifdef USING_BASIC_ERR_FILE_AND_LINE

inline Length::Length(const CharType * message, const char* file, 
    const std::size_t& line) noexcept :
        TriggerType(basic::defn::err::logic_length_id, file, line),
        exc::Logic(message)
{}

#endif //!USING_BASIC_ERR_FILE_AND_LINE

inline Length::Length(const Length & cpy) noexcept :
    TriggerType(cpy),
    exc::Logic(cpy)
{}

inline Length::Length(Length && mov) noexcept :
    TriggerType(std::move(mov)),
    exc::Logic(std::move(mov))
{}

inline const typename Length::CharType * Length::Message() const noexcept
{
    return exc::Logic::Message();
}

inline const err::intf::Output & 
Length::operator>>(OutputType & out) const noexcept
{
    exc::Logic::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

using Length = std::length_error;

#endif //!USING_STANDARD_EXCEPTION

} //!logic

} //!exc

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const std::length_error& e) noexcept
{
    return Standard(basic::defn::err::logic_length_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!err

} //!basic

#endif //!BASIC_ERR_EXC_LOGIC_LENGTH_H_
