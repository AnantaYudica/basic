#ifndef BASIC_ERR_EXC_BAD_H_
#define BASIC_ERR_EXC_BAD_H_

#include "../../Error.h"
#include "../tag/Trigger.h"
#include "../Identification.h"
#include "../id/Get.h"
#include "../id/Standard.h"
#include "../defn/type/Char.h"
#include "../defn/type/Output.h"
#include "../defn/func/output/Operator.h"
#include "../../defn/err/Identification.h"

#include <exception>
#include <utility>

namespace basic
{
namespace err
{
namespace exc
{

#ifdef USING_BASIC_ERR_EXCEPTION

class Bad : public err::Exception
{
public:
    typedef Error<tag::Trigger> TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;

#ifdef USING_BASIC_ERR_FILE_AND_LINE

protected:
    inline Bad() noexcept;
public:
    inline Bad(const char * file, const std::size_t & line) noexcept;

#else

public:
    inline Bad() noexcept;

#endif //!USING_BASIC_ERR_FILE_AND_LINE

public:
    inline Bad(const Bad & cpy) noexcept;
    inline Bad(Bad && mov) noexcept;
public:
    inline Bad & operator=(const Bad &) = delete;
    inline Bad & operator=(Bad &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const err::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

inline Bad::Bad() noexcept :
    TriggerType(basic::defn::err::bad_id)
{}

#ifdef USING_BASIC_ERR_FILE_AND_LINE

inline Bad::Bad(const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(basic::defn::err::bad_id, file, line)
{}

#endif //!USING_BASIC_ERR_FILE_AND_LINE

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

inline const err::intf::Output & Bad::
    operator>>(OutputType & out) const noexcept
{
    err::Exception::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

class Bad : public std::exception
{

};

#endif //!USING_STANDARD_EXCEPTION

} //!exc

namespace id
{

#ifdef USING_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const exc::Bad & e) noexcept
{
    return Standard(basic::defn::err::bad_id);
}

#endif //!USING_STANDARD_EXCEPTION

#endif //!USING_EXCEPTION

} //!id

} //!err

} //!basic

#endif //!BASIC_ERR_EXC_BAD_H_
