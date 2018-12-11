#ifndef BASIC_ERROR_EXCEPTION_RUNTIME_RANGE_H_
#define BASIC_ERROR_EXCEPTION_RUNTIME_RANGE_H_

#include "../Runtime.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../output/Operator.h"
#include "../../../constant/error/Identification.h"

#include <stdexcept>
#include <utility>

namespace basic
{
namespace error
{
namespace exception
{
namespace runtime
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class Range : public exception::Runtime
{
public:
    typedef typename error::Exception::TriggerType TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputValueType;
protected:
    Range() noexcept;
    
#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    Range(const CharType * message) noexcept;
public:
    Range(const CharType * message, const char * file, 
        const std::size_t & line) noexcept;

#else

public:
    Range(const CharType * message) noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    Range(const Range & cpy) noexcept;
    Range(Range && mov) noexcept;
public:
    Range & operator=(const Range &) = delete;
    Range & operator=(Range &&) = delete;
public:
    virtual const CharType * Message() const noexcept;
protected:
    virtual OutputValueType & Output(OutputValueType & out) const noexcept;
};

Range::Range() noexcept : 
    TriggerType(constant::error::runtime_range_id),
    exception::Runtime("Range Runtime Exception")
{}

Range::Range(const CharType * message) noexcept : 
    TriggerType(constant::error::runtime_range_id),
    exception::Runtime(message)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

Range::Range(const CharType * message, const char* file, 
    const std::size_t & line) noexcept :
        TriggerType(constant::error::runtime_range_id, file, line),
        exception::Runtime(message)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

Range::Range(const Range & cpy) noexcept :
    TriggerType(cpy),
    exception::Runtime(cpy)
{}

Range::Range(Range && mov) noexcept :
    TriggerType(std::move(mov)),
    exception::Runtime(std::move(mov))
{}

const typename Range::CharType * Range::Message() const noexcept
{
    return exception::Runtime::Message();
}

typename Range::OutputValueType & 
Range::Output(OutputValueType & out) const noexcept
{
    return exception::Runtime::Output(out);
}

#elif USING_STANDARD_EXCEPTION

typedef std::range_error Range;

#endif

} //!runtime

} //!exception

namespace id
{

template<typename TTagError = tag::Trigger>
typename enable_if::tag::Trigger<TTagError>::Type
Get(const std::range_error & e)
{
    return Standard(constant::error::runtime_range_id);
}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_RUNTIME_RANGE_H_
