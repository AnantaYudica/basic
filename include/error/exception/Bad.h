#ifndef BASIC_ERROR_EXCEPTION_BAD_H_
#define BASIC_ERROR_EXCEPTION_BAD_H_

#include "../../Error.h"
#include "../tag/Trigger.h"
#include "../Identification.h"
#include "../id/Get.h"
#include "../id/Standard.h"
#include "../defn/type/Char.h"
#include "../defn/type/Output.h"
#include "../defn/func/output/Operator.h"
#include "../constant/error/Identification.h"

#include <exception>
#include <utility>

namespace basic
{
namespace error
{
namespace exception
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class Bad : public error::Exception
{
public:
    typedef Error<tag::Trigger> TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline Bad() noexcept;
public:
    inline Bad(const char * file, const std::size_t & line) noexcept;

#else

public:
    inline Bad() noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    inline Bad(const Bad & cpy) noexcept;
    inline Bad(Bad && mov) noexcept;
public:
    inline Bad & operator=(const Bad &) = delete;
    inline Bad & operator=(Bad &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const error::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

inline Bad::Bad() noexcept :
    TriggerType(constant::error::bad_id)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

inline Bad::Bad(const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(constant::error::bad_id, file, line)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

inline Bad::Bad(const Bad & cpy) noexcept :
    TriggerType(cpy)
{}

inline Bad::Bad(Bad && mov) noexcept :
    TriggerType(std::move(mov))
{}

inline const typename Bad::CharType * Bad::Message() const noexcept
{
    return "Bad Exception";
}

inline const error::intf::Output & Bad::
    operator>>(OutputType & out) const noexcept
{
    error::Exception::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

class Bad : public std::exception
{

};

#endif //!USING_STANDARD_EXCEPTION

} //!exception

namespace id
{

#ifdef USING_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const exception::Bad & e) noexcept
{
    return Standard(constant::error::bad_id);
}

#endif //!USING_STANDARD_EXCEPTION

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_BAD_H_
