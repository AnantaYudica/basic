#ifndef BASIC_ERROR_EXCEPTION_LOGIC_DOMAIN_H_
#define BASIC_ERROR_EXCEPTION_LOGIC_DOMAIN_H_

#include "../Logic.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../output/Operator.h"
#include "../../msg/String.h"
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

class Domain : public exception::Logic
{
public:
    typedef typename error::Exception::TriggerType TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputValueType;
protected:
    Domain() noexcept;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    Domain(const CharType * message) noexcept;
public:
    Domain(const CharType * message, const char * file, 
        const std::size_t & line) noexcept;

#else

public:
    Domain(const CharType * message) noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    Domain(const Domain & cpy) noexcept;
    Domain(Domain && mov) noexcept;
public:
    Domain& operator=(const Domain &) = delete;
    Domain& operator=(Domain &&) = delete;
public:
    virtual const CharType * Message() const noexcept;
protected:
    virtual OutputValueType & Output(OutputValueType & out) const noexcept;
};

Domain::Domain() noexcept :
    TriggerType(constant::error::logic_domain_id),
    exception::Logic("Domain Logic Exception")
{}

Domain::Domain(const CharType * message) noexcept :
    TriggerType(constant::error::logic_domain_id),
    exception::Logic(message)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

Domain::Domain(const CharType * message, const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(constant::error::logic_domain_id, file, line),
        exception::Logic(message)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

Domain::Domain(const Domain & cpy) noexcept :
    TriggerType(cpy),
    exception::Logic(cpy)
{}

Domain::Domain(Domain && mov) noexcept :
    TriggerType(std::move(mov)),
    exception::Logic(std::move(mov))
{}

const typename Domain::CharType * Domain::Message() const noexcept
{
    return exception::Logic::Message();
}

typename Domain::OutputValueType & 
Domain::Output(OutputValueType & out) const noexcept
{
    return exception::Logic::Output(out);
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

using Domain = std::domain_error;

#endif //!USING_STANDARD_EXCEPTION

} //!logic

} //!exception

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger>
typename enable_if::tag::Trigger<TTagError>::Type  
Get(const std::domain_error & e)
{
    return Standard(constant::error::logic_domain_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_LOGIC_DOMAIN_H_
