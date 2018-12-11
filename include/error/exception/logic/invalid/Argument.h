#ifndef BASIC_ERROR_EXCEPTION_LOGIC_INVALID_ARGUMENT_H_
#define BASIC_ERROR_EXCEPTION_LOGIC_INVALID_ARGUMENT_H_

#include "../Invalid.h"
#include "../../../Identification.h"
#include "../../../id/Get.h"
#include "../../../id/Standard.h"
#include "../../../defn/type/Char.h"
#include "../../../defn/type/Output.h"
#include "../../../output/Operator.h"
#include "../../../../constant/error/Identification.h"

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
namespace invalid
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class Argument : public exception::logic::Invalid
{
public:
    typedef typename error::Exception::TriggerType TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputValueType;
protected:
    Argument() noexcept;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    Argument(const CharType * message) noexcept;
public:
    Argument(const CharType * message, const char* file, 
        const std::size_t& line) noexcept;

#else

public:
    Argument(const CharType * message) noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    Argument(const Argument & cpy) noexcept;
    Argument(Argument && mov) noexcept;
public:
    ~Argument();
public:
    Argument & operator=(const Argument &) = delete;
    Argument & operator=(Argument &&) = delete;  
public:
    virtual const CharType * Message() const noexcept;
protected:
    virtual OutputValueType & Output(OutputValueType & out) const noexcept;
};

Argument::Argument() noexcept :
    TriggerType(constant::error::logic_invalid_argument_id),
    exception::logic::Invalid("Domain Logic Invalid Argument Exception")
{}

Argument::Argument(const CharType * message) noexcept :
    TriggerType(constant::error::logic_invalid_argument_id),
    exception::logic::Invalid(message)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

Argument::Argument(const CharType * message, const char* file, 
    const std::size_t& line) noexcept:
        TriggerType(constant::error::logic_invalid_argument_id, file, line),
        exception::logic::Invalid(message)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

Argument::Argument(const Argument & cpy) noexcept :
    TriggerType(cpy),
    exception::logic::Invalid(cpy)
{}

Argument::Argument(Argument && mov) noexcept :
    TriggerType(std::move(mov)),
    logic::Invalid(std::move(mov))
{}

const typename Argument::CharType * Argument::Message() const noexcept
{
    return exception::logic::Invalid::Message();
}

typename Argument::OutputValueType & 
Argument::Output(OutputValueType & out) const noexcept
{
    return exception::logic::Invalid::Output(out);
}

#elif USING_STANDARD_EXCEPTION

typedef std::invalid_argument Invalid;

#endif

} //!invalid

} //!logic

} //!exception

namespace id
{

template<typename TTagError = tag::Trigger>
typename enable_if::tag::Trigger<TTagError>::Type  
Get(const std::invalid_argument& e) noexcept
{
    return Standard(constant::error::logic_invalid_argument_id);
}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_LOGIC_INVALID_ARGUMENT_H_
