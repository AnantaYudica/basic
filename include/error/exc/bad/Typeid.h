#ifndef BASIC_ERROR_EXC_BAD_TYPEID_H_
#define BASIC_ERROR_EXC_BAD_TYPEID_H_

#include "../Bad.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/func/output/Operator.h"
#include "../../../defn/error/Identification.h"

#include <typeinfo>
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

class Typeid : public error::exc::Bad
{
public:
    typedef Error<tag::Trigger> TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline Typeid() noexcept;
public:
    inline Typeid(const char * file, const std::size_t & line) noexcept;

#else

public:
    inline Typeid() noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    inline Typeid(const Typeid & cpy) noexcept;
    inline Typeid(Typeid && mov) noexcept;
public:
    inline Typeid & operator=(const Typeid &) = delete;
    inline Typeid & operator=(Typeid &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const error::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

inline Typeid::Typeid() noexcept :
    TriggerType(basic::defn::error::bad_typeid_id)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

inline Typeid::Typeid(const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(basic::defn::error::bad_typeid_id, file, line)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

inline Typeid::Typeid(const Typeid & cpy) noexcept :
    TriggerType(cpy)
{}

inline Typeid::Typeid(Typeid && mov) noexcept :
    TriggerType(std::move(mov))
{}

inline const typename Typeid::CharType * 
Typeid::Message() const noexcept
{
    return "Bad Typeid Exception";
}

inline const error::intf::Output & Typeid::
    operator>>(OutputType & out) const noexcept
{
    error::exc::Bad::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

using Typeid = std::bad_typeid;

#endif //!USING_STANDARD_EXCEPTION

} //!bad

} //!exc

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const std::bad_typeid & e) noexcept
{
    return Standard(basic::defn::error::bad_typeid_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXC_BAD_TYPEID_H_
