#ifndef BASIC_ERR_EXC_BAD_TYPEID_H_
#define BASIC_ERR_EXC_BAD_TYPEID_H_

#include "../Bad.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/func/output/Operator.h"
#include "../../../defn/err/Identification.h"

#include <typeinfo>
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

class Typeid : public err::exc::Bad
{
public:
    typedef Error<tag::Trigger> TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;

#ifdef USING_BASIC_ERR_FILE_AND_LINE

protected:
    inline Typeid() noexcept;
public:
    inline Typeid(const char * file, const std::size_t & line) noexcept;

#else

public:
    inline Typeid() noexcept;

#endif //!USING_BASIC_ERR_FILE_AND_LINE

public:
    inline Typeid(const Typeid & cpy) noexcept;
    inline Typeid(Typeid && mov) noexcept;
public:
    inline Typeid & operator=(const Typeid &) = delete;
    inline Typeid & operator=(Typeid &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const err::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

inline Typeid::Typeid() noexcept :
#ifdef USING_BASIC_ERR_FILE_AND_LINE
    TriggerType(basic::defn::err::bad_typeid_id,
        "unknown", static_cast<std::size_t>(-1))
#else
    TriggerType(basic::defn::err::bad_typeid_id)
#endif //!USING_BASIC_ERR_FILE_AND_LINE
{}

#ifdef USING_BASIC_ERR_FILE_AND_LINE

inline Typeid::Typeid(const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(basic::defn::err::bad_typeid_id, file, line)
{}

#endif //!USING_BASIC_ERR_FILE_AND_LINE

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

inline const err::intf::Output & Typeid::
    operator>>(OutputType & out) const noexcept
{
    err::exc::Bad::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

using Typeid = std::bad_typeid;

#endif //!USING_STANDARD_EXCEPTION

} //!bad

} //!exc

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger,
    typename TException>
inline typename enable_if::tag::Trigger<TTagError,
    std::is_same<TException, std::bad_typeid>::value>::Type 
Get(const TException & e) noexcept
{
    return Standard(basic::defn::err::bad_typeid_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!err

} //!basic

#endif //!BASIC_ERR_EXC_BAD_TYPEID_H_
