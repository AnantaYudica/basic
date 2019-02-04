#ifndef BASIC_ERROR_EXCEPTION_BAD_ALLOC_ARRAY_LENGTH_H_
#define BASIC_ERROR_EXCEPTION_BAD_ALLOC_ARRAY_LENGTH_H_

#include "../Array.h"
#include "../../../../Identification.h"
#include "../../../../id/Get.h"
#include "../../../../id/Standard.h"
#include "../../../../defn/type/Char.h"
#include "../../../../defn/type/Output.h"
#include "../../../../defn/func/output/Operator.h"
#include "../../../../../constant/error/Identification.h"

#include <new>
#include <utility>

namespace basic
{
namespace error
{
namespace exception
{
namespace bad
{
namespace alloc
{
namespace array
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class Length : public error::exception::bad::alloc::Array
{
public:
    typedef Error<tag::Trigger> TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline Length() noexcept;
public:
    inline Length(const char * file, const std::size_t & line) noexcept;

#else

public:
    inline Length() noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    inline Length(const Length & cpy) noexcept;
    inline Length(Length && mov) noexcept;
public:
    inline Length & operator=(const Length &) = delete;
    inline Length & operator=(Length &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const error::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

inline Length::Length() noexcept :
    TriggerType(constant::error::bad_allocation_array_length_id)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

inline Length::Length(const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(constant::error::bad_allocation_array_length_id, 
            file, line)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

inline Length::Length(const Length & cpy) noexcept :
    TriggerType(cpy)
{}

inline Length::Length(Length && mov) noexcept :
    TriggerType(std::move(mov))
{}

inline const typename Length::CharType * 
Length::Message() const noexcept
{
    return "Bad Allocation Array Length Exception";
}

inline const error::intf::Output & Length::
    operator>>(OutputType & out) const noexcept
{
    error::exception::bad::alloc::Array::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

using Length = std::bad_array_new_length;

#endif //!USING_STANDARD_EXCEPTION

} //!array

} //!alloc

} //!bad

} //!exception

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const std::bad_array_new_length & e) noexcept
{
    return Standard(constant::error::bad_allocation_array_length_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_BAD_ALLOC_ARRAY_LENGTH_H_
