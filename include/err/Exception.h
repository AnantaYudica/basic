#ifndef BASIC_ERR_EXCEPTION_H_
#define BASIC_ERR_EXCEPTION_H_

#include "../Error.h"
#include "tag/Trigger.h"
#include "Identification.h"
#include "id/Get.h"
#include "id/Standard.h"
#include "defn/type/Char.h"
#include "defn/type/Output.h"
#include "defn/func/output/Operator.h"
#include "../defn/err/Identification.h"

#include <exception>
#include <type_traits>
#include <utility>

namespace basic
{
namespace err
{

#ifdef USING_BASIC_ERR_EXCEPTION

class Exception : public virtual Error<tag::Trigger>
{
public:
    typedef Error<tag::Trigger> TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;

#ifdef USING_BASIC_ERR_FILE_AND_LINE

protected:
    inline Exception() noexcept;
public:
    inline Exception(const char * file, const std::size_t & line) noexcept;

#else

public:
    inline Exception() noexcept;

#endif //!USING_BASIC_ERR_FILE_AND_LINE

public:
    inline Exception(const Exception & cpy) noexcept;
    inline Exception(Exception && mov) noexcept;
public:
    Exception & operator=(const Exception &) = delete;
    Exception & operator=(Exception &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const err::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

inline Exception::Exception() noexcept :
#ifdef USING_BASIC_ERR_FILE_AND_LINE
    TriggerType(basic::defn::err::exception_id,
        "unknown", static_cast<std::size_t>(-1))
#else
    TriggerType(basic::defn::err::exception_id)
#endif //!USING_BASIC_ERR_FILE_AND_LINE
{}

#ifdef USING_BASIC_ERR_FILE_AND_LINE

inline Exception::Exception(const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(basic::defn::err::exception_id, file, line)
{}

#endif //!USING_BASIC_ERR_FILE_AND_LINE

inline Exception::Exception(const Exception & cpy) noexcept :
    TriggerType(cpy)
{}

inline Exception::Exception(Exception && mov) noexcept :
    TriggerType(std::move(mov))
{}

inline const typename Exception::CharType * Exception::Message() const noexcept
{
    return "Exception";
}

inline const err::intf::Output & Exception::
    operator>>(OutputType & out) const noexcept
{
    defn::func::output::Operator(out, this->Message(), " ");
    TriggerType::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

using Exception = std::exception;

#endif //!USING_STANDARD_EXCEPTION

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger, 
    typename TException>
inline typename enable_if::tag::Trigger<TTagError,
    std::is_same<TException, std::exception>::value>::Type 
Get(const TException & e) noexcept
{
    return Standard(basic::defn::err::exception_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!err

} //!basic

#endif //!BASIC_ERR_EXCEPTION_H_
