#ifndef BASIC_ERROR_EXCEPTION_BAD_CAST_H_
#define BASIC_ERROR_EXCEPTION_BAD_CAST_H_

#include "../Bad.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/func/output/Operator.h"
#include "../../../constant/error/Identification.h"

#include <typeinfo>
#include <utility>

namespace basic
{
namespace error
{
namespace exception
{
namespace bad
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class Cast : public error::exception::Bad
{
public:
    typedef Error<tag::Trigger> TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline Cast() noexcept;
public:
    inline Cast(const char * file, const std::size_t & line) noexcept;

#else

public:
    inline Cast() noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    inline Cast(const Cast & cpy) noexcept;
    inline Cast(Cast && mov) noexcept;
public:
    inline Cast & operator=(const Cast &) = delete;
    inline Cast & operator=(Cast &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const error::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

inline Cast::Cast() noexcept :
    TriggerType(constant::error::bad_cast_id)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

inline Cast::Cast(const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(constant::error::bad_cast_id, file, line)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

inline Cast::Cast(const Cast & cpy) noexcept :
    TriggerType(cpy)
{}

inline Cast::Cast(Cast && mov) noexcept :
    TriggerType(std::move(mov))
{}

inline const typename Cast::CharType * 
Cast::Message() const noexcept
{
    return "Bad Cast Exception";
}

inline const error::intf::Output & Cast::
    operator>>(OutputType & out) const noexcept
{
    error::exception::Bad::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

using Cast = std::bad_cast;

#endif //!USING_STANDARD_EXCEPTION

} //!bad

} //!exception

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const std::bad_cast & e) noexcept
{
    return Standard(constant::error::bad_cast_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_BAD_CAST_H_
