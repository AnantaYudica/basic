#ifndef BASIC_ERROR_EXCEPTION_LOGIC_INVALID_H_
#define BASIC_ERROR_EXCEPTION_LOGIC_INVALID_H_

#include "../Logic.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../output/Operator.h"
#include "../../../constant/error/Identification.h"

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

class Invalid : public exception::Logic
{
public:
    typedef typename error::Exception::TriggerType TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputValueType;
protected:
    Invalid() noexcept;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    Invalid(const CharType * message) noexcept;
public:
    Invalid(const CharType * message, const char * file, 
        const std::size_t & line) noexcept;

#else

public:
    Invalid(const CharType * message) noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    Invalid(const Invalid & cpy) noexcept;
    Invalid(Invalid && mov) noexcept;
public:
    Invalid & operator=(const Invalid &) = delete;
    Invalid & operator=(Invalid &&) = delete;
public:
    virtual const CharType * Message() const noexcept;
protected:
    virtual OutputValueType & Output(OutputValueType & out) const noexcept;
};

Invalid::Invalid() noexcept :
    TriggerType(constant::error::logic_invalid_id),
    exception::Logic("Domain Logic Invalid")
{}

Invalid::Invalid(const CharType * message) noexcept :
    TriggerType(constant::error::logic_invalid_id),
    exception::Logic(message)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

Invalid::Invalid(const CharType * message, const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(constant::error::logic_invalid_id, file, line),
        exception::Logic(message)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

Invalid::Invalid(const Invalid & cpy) noexcept :
    TriggerType(cpy),
    exception::Logic(cpy)
{}

Invalid::Invalid(Invalid && mov) noexcept :
    TriggerType(std::move(mov)),
    exception::Logic(std::move(mov))
{}

const typename Invalid::CharType * Invalid::Message() const noexcept
{
    return exception::Logic::Message();
}

typename Invalid::OutputValueType & 
Invalid::Output(OutputValueType & out) const noexcept
{
    return exception::Logic::Output(out);
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

class Invalid : public std::logic_error
{

};

#endif //!USING_STANDARD_EXCEPTION

} //!logic

} //!exception

namespace id
{

#ifdef USING_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

template<typename TTagError = tag::Trigger>
typename enable_if::tag::Trigger<TTagError>::Type  
Get(const exception::logic::Invalid& e) noexcept
{
    return Standard(constant::error::logic_invalid_id);
}

#endif //!USING_STANDARD_EXCEPTION

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_LOGIC_INVALID_H_
