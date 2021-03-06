#ifndef BASIC_ERR_EXC_BAD_ALLOCATION_H_
#define BASIC_ERR_EXC_BAD_ALLOCATION_H_

#include "../Bad.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/func/output/Operator.h"
#include "../../../defn/err/Identification.h"

#include <new>
#include <type_traits>
#include <utility>

namespace basic
{
namespace err
{
namespace exc
{
namespace bad
{

#ifdef USING_BASIC_ERR_EXCEPTION

class Allocation : public err::exc::Bad
{
public:
    typedef Error<tag::Trigger> TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;

#ifdef USING_BASIC_ERR_FILE_AND_LINE

protected:
    inline Allocation() noexcept;
public:
    inline Allocation(const char * file, const std::size_t & line) noexcept;

#else

public:
    inline Allocation() noexcept;

#endif //!USING_BASIC_ERR_FILE_AND_LINE

public:
    inline Allocation(const Allocation & cpy) noexcept;
    inline Allocation(Allocation && mov) noexcept;
public:
    inline Allocation & operator=(const Allocation &) = delete;
    inline Allocation & operator=(Allocation &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const err::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

inline Allocation::Allocation() noexcept :
#ifdef USING_BASIC_ERR_FILE_AND_LINE
    TriggerType(basic::defn::err::bad_allocation_id,
        "unknown", static_cast<std::size_t>(-1))
#else
    TriggerType(basic::defn::err::bad_allocation_id)
#endif //!USING_BASIC_ERR_FILE_AND_LINE
{}

#ifdef USING_BASIC_ERR_FILE_AND_LINE

inline Allocation::Allocation(const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(basic::defn::err::bad_allocation_id, file, line)
{}

#endif //!USING_BASIC_ERR_FILE_AND_LINE

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

inline const err::intf::Output & Allocation::
    operator>>(OutputType & out) const noexcept
{
    err::exc::Bad::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

using Allocation = std::bad_alloc;

#endif //!USING_STANDARD_EXCEPTION

} //!bad

} //!exc

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger,
    typename TException>
inline typename enable_if::tag::Trigger<TTagError,
    std::is_same<TException, std::bad_alloc>::value>::Type 
Get(const TException & e) noexcept
{
    return Standard(basic::defn::err::bad_allocation_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!err

} //!basic

#endif //!BASIC_ERR_EXC_BAD_ALLOCATION_H_
