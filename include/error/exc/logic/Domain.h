#ifndef BASIC_ERROR_EXC_LOGIC_DOMAIN_H_
#define BASIC_ERROR_EXC_LOGIC_DOMAIN_H_

#include "../Logic.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/func/output/Operator.h"
#include "../../msg/String.h"
#include "../../../constant/error/Identification.h"

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

#ifdef USING_BASIC_ERROR_EXCEPTION

class Domain : public exc::Logic
{
public:
    typedef typename error::Exception::TriggerType TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
protected:
    inline Domain() noexcept;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline Domain(const CharType * message) noexcept;
public:
    inline Domain(const CharType * message, const char * file, 
        const std::size_t & line) noexcept;

#else

public:
    inline Domain(const CharType * message) noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    inline Domain(const Domain & cpy) noexcept;
    inline Domain(Domain && mov) noexcept;
public:
    Domain & operator=(const Domain &) = delete;
    Domain & operator=(Domain &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const error::intf::Output & 
    operator>>(OutputType & out) const noexcept;
};

inline Domain::Domain() noexcept :
    TriggerType(constant::error::logic_domain_id),
    exc::Logic("Domain Logic Exception")
{}

inline Domain::Domain(const CharType * message) noexcept :
    TriggerType(constant::error::logic_domain_id),
    exc::Logic(message)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

inline Domain::Domain(const CharType * message, const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(constant::error::logic_domain_id, file, line),
        exc::Logic(message)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

inline Domain::Domain(const Domain & cpy) noexcept :
    TriggerType(cpy),
    exc::Logic(cpy)
{}

inline Domain::Domain(Domain && mov) noexcept :
    TriggerType(std::move(mov)),
    exc::Logic(std::move(mov))
{}

inline const typename Domain::CharType * Domain::Message() const noexcept
{
    return exc::Logic::Message();
}

inline const error::intf::Output & 
Domain::operator>>(OutputType & out) const noexcept
{
    exc::Logic::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

using Domain = std::domain_error;

#endif //!USING_STANDARD_EXCEPTION

} //!logic

} //!exc

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type  
Get(const std::domain_error & e) noexcept
{
    return Standard(constant::error::logic_domain_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXC_LOGIC_DOMAIN_H_
