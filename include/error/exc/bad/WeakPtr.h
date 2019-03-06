#ifndef BASIC_ERROR_EXC_BAD_WEAKPTR_H_
#define BASIC_ERROR_EXC_BAD_WEAKPTR_H_

#include "../Bad.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/func/output/Operator.h"
#include "../../../constant/error/Identification.h"

#include <memory>
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

class WeakPtr : public error::exc::Bad
{
public:
    typedef Error<tag::Trigger> TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline WeakPtr() noexcept;
public:
    inline WeakPtr(const char * file, const std::size_t & line) noexcept;

#else

public:
    inline WeakPtr() noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    inline WeakPtr(const WeakPtr & cpy) noexcept;
    inline WeakPtr(WeakPtr && mov) noexcept;
public:
    inline WeakPtr & operator=(const WeakPtr &) = delete;
    inline WeakPtr & operator=(WeakPtr &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const error::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

inline WeakPtr::WeakPtr() noexcept :
    TriggerType(constant::error::bad_weakptr_id)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

inline WeakPtr::WeakPtr(const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(constant::error::bad_weakptr_id, file, line)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

inline WeakPtr::WeakPtr(const WeakPtr & cpy) noexcept :
    TriggerType(cpy)
{}

inline WeakPtr::WeakPtr(WeakPtr && mov) noexcept :
    TriggerType(std::move(mov))
{}

inline const typename WeakPtr::CharType * 
WeakPtr::Message() const noexcept
{
    return "Bad WeakPtr Exception";
}

inline const error::intf::Output & WeakPtr::
    operator>>(OutputType & out) const noexcept
{
    error::exc::Bad::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

using WeakPtr = std::bad_weak_ptr;

#endif //!USING_STANDARD_EXCEPTION

} //!bad

} //!exc

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const std::bad_weak_ptr & e) noexcept
{
    return Standard(constant::error::bad_weakptr_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXC_BAD_WEAKPTR_H_
