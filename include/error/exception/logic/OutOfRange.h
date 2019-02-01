#ifndef BASIC_ERROR_EXCEPTION_LOGIC_OUTOFRANGE_H_
#define BASIC_ERROR_EXCEPTION_LOGIC_OUTOFRANGE_H_

#include "../Logic.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/func/output/Operator.h"
#include "../../../constant/error/Identification.h"

#include <stdexcept>
#include <utility>

namespace basic
{
namespace error
{
namespace exception
{
namespace logic
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class OutOfRange : public exception::Logic
{
public:
    typedef typename exception::Logic::TriggerType TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputValueType;
protected:
    inline OutOfRange() noexcept;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline OutOfRange(const CharType * message) noexcept;
public:
    inline OutOfRange(const CharType * message, const char * file, 
        const std::size_t& line) noexcept;

#else

public:
    inline OutOfRange(const CharType * message) noexcept;

#endif //USING_BASIC_ERROR_FILE_AND_LINE

public:
    inline OutOfRange(const OutOfRange& cpy) noexcept;
    inline OutOfRange(OutOfRange&& mov) noexcept;
public:
    inline OutOfRange & operator=(const OutOfRange&) = delete;
    inline OutOfRange & operator=(OutOfRange&&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const error::intf::Output & 
    operator>>(OutputType & out) const noexcept;
};

inline OutOfRange::OutOfRange() noexcept :
    TriggerType(constant::error::logic_outofrange_id),
    exception::Logic("Domain Logic Out of Range")
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

inline OutOfRange::OutOfRange(const CharType * message, const char * file, 
    const std::size_t & line) noexcept :
        ErrorType(constant::error::logic_outofrange_id, file, line),
        exception::Logic(message)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

inline OutOfRange::OutOfRange(const OutOfRange & cpy) noexcept :
    TriggerType(cpy),
    exception::Logic(cpy)
{}

inline OutOfRange::OutOfRange(OutOfRange && mov) noexcept :
    TriggerType(std::move(mov)),
    exception::Logic(std::move(mov))
{}

inline const typename OutOfRange::CharType * 
OutOfRange::Message() const noexcept
{
    return exception::Logic::Message();
}

inline const error::intf::Output & 
OutOfRange::operator>>(OutputType & out) const noexcept
{
    exception::Logic::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

typedef std::out_of_range OutOfRange;

#endif //!USING_STANDARD_EXCEPTION

} //!logic

} //!exception

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const std::out_of_range & e) noexcept
{
    return Standard(constant::error::logic_outofrange_id);
}

#endif //!USING_EXCEPTION

}

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_LOGIC_OUTOFRANGE_H_
