#ifndef BASIC_ERROR_EXC_BAD_ALLOC_ARRAY_H_
#define BASIC_ERROR_EXC_BAD_ALLOC_ARRAY_H_

#include "../Allocation.h"
#include "../../../Identification.h"
#include "../../../id/Get.h"
#include "../../../id/Standard.h"
#include "../../../defn/type/Char.h"
#include "../../../defn/type/Output.h"
#include "../../../defn/func/output/Operator.h"
#include "../../../../defn/error/Identification.h"

#include <utility>

namespace basic
{
namespace error
{
namespace exc
{
namespace bad
{
namespace alloc
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class Array : public error::exc::bad::Allocation
{
public:
    typedef Error<tag::Trigger> TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline Array() noexcept;
public:
    inline Array(const char * file, const std::size_t & line) noexcept;

#else

public:
    inline Array() noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    inline Array(const Array & cpy) noexcept;
    inline Array(Array && mov) noexcept;
public:
    inline Array & operator=(const Array &) = delete;
    inline Array & operator=(Array &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const error::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

inline Array::Array() noexcept :
    TriggerType(basic::defn::error::bad_allocation_array_id)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

inline Array::Array(const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(basic::defn::error::bad_allocation_array_id, file, line)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

inline Array::Array(const Array & cpy) noexcept :
    TriggerType(cpy)
{}

inline Array::Array(Array && mov) noexcept :
    TriggerType(std::move(mov))
{}

inline const typename Array::CharType * 
Array::Message() const noexcept
{
    return "Bad Allocation Array Exception";
}

inline const error::intf::Output & Array::
    operator>>(OutputType & out) const noexcept
{
    error::exc::bad::Allocation::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

class Array : public error::exc::bad::Allocation
{

};

#endif //!USING_STANDARD_EXCEPTION

} //!alloc

} //!bad

} //!exc

namespace id
{

#ifdef USING_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const error::exc::bad::alloc::Array & e) noexcept
{
    return Standard(basic::defn::error::bad_allocation_array_id);
}

#endif //!USING_STANDARD_EXCEPTION

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXC_BAD_ALLOC_ARRAY_H_
