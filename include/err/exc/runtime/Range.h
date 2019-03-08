#ifndef BASIC_ERR_EXC_RUNTIME_RANGE_H_
#define BASIC_ERR_EXC_RUNTIME_RANGE_H_

#include "../Runtime.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/func/output/Operator.h"
#include "../../../defn/err/Identification.h"

#include <stdexcept>
#include <utility>

namespace basic
{
namespace err
{
namespace exc
{
namespace runtime
{

#ifdef USING_BASIC_ERR_EXCEPTION

class Range : public exc::Runtime
{
public:
    typedef typename err::Exception::TriggerType TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
protected:
    inline Range() noexcept;
    
#ifdef USING_BASIC_ERR_FILE_AND_LINE

protected:
    inline Range(const CharType * message) noexcept;
public:
    inline Range(const CharType * message, const char * file, 
        const std::size_t & line) noexcept;

#else

public:
    inline Range(const CharType * message) noexcept;

#endif //!USING_BASIC_ERR_FILE_AND_LINE

public:
    inline Range(const Range & cpy) noexcept;
    inline Range(Range && mov) noexcept;
public:
    inline Range & operator=(const Range &) = delete;
    inline Range & operator=(Range &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const err::intf::Output & 
    operator>>(OutputType & out) const noexcept;
};

inline Range::Range() noexcept : 
    TriggerType(basic::defn::err::runtime_range_id),
    exc::Runtime("Range Runtime Exception")
{}

inline Range::Range(const CharType * message) noexcept : 
    TriggerType(basic::defn::err::runtime_range_id),
    exc::Runtime(message)
{}

#ifdef USING_BASIC_ERR_FILE_AND_LINE

inline Range::Range(const CharType * message, const char* file, 
    const std::size_t & line) noexcept :
        TriggerType(basic::defn::err::runtime_range_id, file, line),
        exc::Runtime(message)
{}

#endif //!USING_BASIC_ERR_FILE_AND_LINE

inline Range::Range(const Range & cpy) noexcept :
    TriggerType(cpy),
    exc::Runtime(cpy)
{}

inline Range::Range(Range && mov) noexcept :
    TriggerType(std::move(mov)),
    exc::Runtime(std::move(mov))
{}

inline const typename Range::CharType * Range::Message() const noexcept
{
    return exc::Runtime::Message();
}

inline const err::intf::Output & 
Range::operator>>(OutputType & out) const noexcept
{
    exc::Runtime::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

typedef std::range_error Range;

#endif //!USING_STANDARD_EXCEPTION

} //!runtime

} //!exc

namespace id
{

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type
Get(const std::range_error & e)
{
    return Standard(basic::defn::err::runtime_range_id);
}

} //!id

} //!err

} //!basic

#endif //!BASIC_ERR_EXC_RUNTIME_RANGE_H_
