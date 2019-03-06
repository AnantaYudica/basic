#ifndef BASIC_ERROR_EXC_BAD_ALLOCATION_H_
#define BASIC_ERROR_EXC_BAD_ALLOCATION_H_

#include "../Bad.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/func/output/Operator.h"
#include "../../../constant/error/Identification.h"

#include <new>
#include <utility>

namespace basic
{
namespace error
{
namespace exc
{
namespace bad
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class Allocation : public error::exc::Bad
{
public:
    typedef Error<tag::Trigger> TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline Allocation() noexcept;
public:
    inline Allocation(const char * file, const std::size_t & line) noexcept;

#else

public:
    inline Allocation() noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    inline Allocation(const Allocation & cpy) noexcept;
    inline Allocation(Allocation && mov) noexcept;
public:
    inline Allocation & operator=(const Allocation &) = delete;
    inline Allocation & operator=(Allocation &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const error::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

inline Allocation::Allocation() noexcept :
    TriggerType(constant::error::bad_allocation_id)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

inline Allocation::Allocation(const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(constant::error::bad_allocation_id, file, line)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

inline Allocation::Allocation(const Allocation & cpy) noexcept :
    TriggerType(cpy)
{}

inline Allocation::Allocation(Allocation && mov) noexcept :
    TriggerType(std::move(mov))
{}

inline const typename Allocation::CharType * 
Allocation::Message() const noexcept
{
    return "Bad Allocation Exception";
}

inline const error::intf::Output & Allocation::
    operator>>(OutputType & out) const noexcept
{
    error::exc::Bad::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

using Allocation = std::bad_alloc;

#endif //!USING_STANDARD_EXCEPTION

} //!bad

} //!exc

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const std::bad_alloc & e) noexcept
{
    return Standard(constant::error::bad_allocation_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXC_BAD_ALLOCATION_H_
