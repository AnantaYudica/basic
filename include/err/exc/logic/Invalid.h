#ifndef BASIC_ERR_EXC_LOGIC_INVALID_H_
#define BASIC_ERR_EXC_LOGIC_INVALID_H_

#include "../Logic.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/func/output/Operator.h"
#include "../../../defn/err/Identification.h"

#include <type_traits>
#include <utility>

namespace basic
{
namespace err
{
namespace exc
{
namespace logic
{

#ifdef USING_BASIC_ERR_EXCEPTION

class Invalid : public exc::Logic
{
public:
    typedef typename err::Exception::TriggerType TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
protected:
    inline Invalid() noexcept;

#ifdef USING_BASIC_ERR_FILE_AND_LINE

protected:
    inline Invalid(const CharType * message) noexcept;
public:
    inline Invalid(const CharType * message, const char * file, 
        const std::size_t & line) noexcept;

#else

public:
    inline Invalid(const CharType * message) noexcept;

#endif //!USING_BASIC_ERR_FILE_AND_LINE

public:
    inline Invalid(const Invalid & cpy) noexcept;
    inline Invalid(Invalid && mov) noexcept;
public:
    inline Invalid & operator=(const Invalid &) = delete;
    inline Invalid & operator=(Invalid &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const err::intf::Output & 
    operator>>(OutputType & out) const noexcept;
};

inline Invalid::Invalid() noexcept :
#ifdef USING_BASIC_ERR_FILE_AND_LINE
    TriggerType(basic::defn::err::logic_invalid_id,
        "unknown", static_cast<std::size_t>(-1)),
#else
    TriggerType(basic::defn::err::logic_invalid_id),
#endif //!USING_BASIC_ERR_FILE_AND_LINE
    exc::Logic("Domain Logic Invalid")
{}

inline Invalid::Invalid(const CharType * message) noexcept :
    TriggerType(basic::defn::err::logic_invalid_id),
    exc::Logic(message)
{}

#ifdef USING_BASIC_ERR_FILE_AND_LINE

inline Invalid::Invalid(const CharType * message, const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(basic::defn::err::logic_invalid_id, file, line),
        exc::Logic(message)
{}

#endif //!USING_BASIC_ERR_FILE_AND_LINE

inline Invalid::Invalid(const Invalid & cpy) noexcept :
    TriggerType(cpy),
    exc::Logic(cpy)
{}

inline Invalid::Invalid(Invalid && mov) noexcept :
    TriggerType(std::move(mov)),
    exc::Logic(std::move(mov))
{}

inline const typename Invalid::CharType * Invalid::Message() const noexcept
{
    return exc::Logic::Message();
}

inline const err::intf::Output & 
Invalid::operator>>(OutputType & out) const noexcept
{
    exc::Logic::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

class Invalid : public std::logic_error
{

};

#endif //!USING_STANDARD_EXCEPTION

} //!logic

} //!exc

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger,
    typename TException>
inline typename enable_if::tag::Trigger<TTagError,
    std::is_same<TException, basic::err::exc::logic::Invalid>::value>::Type  
Get(const TException & e) noexcept
{
    return Standard(basic::defn::err::logic_invalid_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!err

} //!basic

#endif //!BASIC_ERR_EXC_LOGIC_INVALID_H_
