#ifndef BASIC_ERROR_EXC_LOGIC_INVALID_ARGUMENT_H_
#define BASIC_ERROR_EXC_LOGIC_INVALID_ARGUMENT_H_

#include "../Invalid.h"
#include "../../../Identification.h"
#include "../../../id/Get.h"
#include "../../../id/Standard.h"
#include "../../../defn/type/Char.h"
#include "../../../defn/type/Output.h"
#include "../../../defn/func/output/Operator.h"
#include "../../../../defn/error/Identification.h"

#include <stdexcept>
#include <utility>

namespace basic
{
namespace error
{
namespace exc
{
namespace logic
{
namespace invalid
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class Argument : public exc::logic::Invalid
{
public:
    typedef typename error::Exception::TriggerType TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
protected:
    inline Argument() noexcept;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline Argument(const CharType * message) noexcept;
public:
    inline Argument(const CharType * message, const char* file, 
        const std::size_t& line) noexcept;

#else

public:
    inline Argument(const CharType * message) noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    inline Argument(const Argument & cpy) noexcept;
    inline Argument(Argument && mov) noexcept;
public:
    inline Argument & operator=(const Argument &) = delete;
    inline Argument & operator=(Argument &&) = delete;  
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const error::intf::Output & 
    operator>>(OutputType & out) const noexcept;
};

inline Argument::Argument() noexcept :
    TriggerType(basic::defn::error::logic_invalid_argument_id),
    exc::logic::Invalid("Domain Logic Invalid Argument Exception")
{}

inline Argument::Argument(const CharType * message) noexcept :
    TriggerType(basic::defn::error::logic_invalid_argument_id),
    exc::logic::Invalid(message)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

inline Argument::Argument(const CharType * message, const char* file, 
    const std::size_t& line) noexcept:
        TriggerType(basic::defn::error::logic_invalid_argument_id, file, line),
        exc::logic::Invalid(message)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

inline Argument::Argument(const Argument & cpy) noexcept :
    TriggerType(cpy),
    exc::logic::Invalid(cpy)
{}

inline Argument::Argument(Argument && mov) noexcept :
    TriggerType(std::move(mov)),
    logic::Invalid(std::move(mov))
{}

inline const typename Argument::CharType * Argument::Message() const noexcept
{
    return exc::logic::Invalid::Message();
}

inline const error::intf::Output & 
Argument::operator>>(OutputType & out) const noexcept
{
    exc::logic::Invalid::operator>>(out);
    return *this;
}

#elif USING_STANDARD_EXCEPTION

typedef std::invalid_argument Invalid;

#endif

} //!invalid

} //!logic

} //!exc

namespace id
{

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type  
Get(const std::invalid_argument& e) noexcept
{
    return Standard(basic::defn::error::logic_invalid_argument_id);
}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXC_LOGIC_INVALID_ARGUMENT_H_
