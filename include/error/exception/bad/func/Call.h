#ifndef BASIC_ERROR_EXCEPTION_BAD_FUNC_CALL_H_
#define BASIC_ERROR_EXCEPTION_BAD_FUNC_CALL_H_

#include "../Function.h"
#include "../../../Identification.h"
#include "../../../id/Get.h"
#include "../../../id/Standard.h"
#include "../../../defn/type/Char.h"
#include "../../../defn/type/Output.h"
#include "../../../output/Operator.h"
#include "../../../../constant/error/Identification.h"

#include <functional>
#include <utility>

namespace basic
{
namespace error
{
namespace exception
{
namespace bad
{
namespace func
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class Call : public error::exception::bad::Function
{
public:
    typedef Error<tag::Trigger> TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline Call() noexcept;
public:
    inline Call(const char * file, const std::size_t & line) noexcept;

#else

public:
    inline Call() noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    inline Call(const Call & cpy) noexcept;
    inline Call(Call && mov) noexcept;
public:
    inline Call & operator=(const Call &) = delete;
    inline Call & operator=(Call &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
protected:
    virtual inline const error::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

inline Call::Call() noexcept :
    TriggerType(constant::error::bad_function_call_id)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

inline Call::Call(const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(constant::error::bad_function_call_id, file, line)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

inline Call::Call(const Call & cpy) noexcept :
    TriggerType(cpy)
{}

inline Call::Call(Call && mov) noexcept :
    TriggerType(std::move(mov))
{}

inline const typename Call::CharType * 
Call::Message() const noexcept
{
    return "Bad Function Call Exception";
}

inline const error::intf::Output & Call::
    operator>>(OutputType & out) const noexcept
{
    error::exception::bad::Function::operator>>(out);
    return *this;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

using Call = std::bad_function_call;

#endif //!USING_STANDARD_EXCEPTION

} //!func

} //!bad

} //!exception

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const std::bad_function_call & e) noexcept
{
    return Standard(constant::error::bad_function_call_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_BAD_FUNC_CALL_H_
