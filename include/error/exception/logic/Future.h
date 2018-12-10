#ifndef BASIC_ERROR_EXCEPTION_LOGIC_FUTURE_H_
#define BASIC_ERROR_EXCEPTION_LOGIC_FUTURE_H_

#include "../Logic.h"
#include "../../tag/System.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../output/Operator.h"
#include "../../msg/String.h"
#include "../../system/category/trait/Future.h"
#include "../../system/category/Message.h"
#include "../../system/Category.h"
#include "../../system/Code.h"
#include "../../../constant/error/Identification.h"
#include "../../../constant/error/system/Category.h"

#include <future>
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

class Future : public exception::Logic,
    public virtual basic::Error<basic::error::tag::System>
{
public:
    typedef typename error::Exception::TriggerType TriggerType;
    typedef basic::Error<basic::error::tag::System> SystemType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputValueType;
public:
    typedef system::Category<system::category::trait::Future> 
        FutureCategoryType;
    typedef system::Code<system::category::trait::Future> CodeType;
    typedef typename FutureCategoryType::CodeSetValueType CodeSetValueType;
private:
    CodeSetValueType m_code;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    Future(const CodeSetValueType & code) noexcept;
public:
    Future(const CodeSetValueType & code, const char * file, 
        const std::size_t & line) noexcept;

#else

public:
    Future(const CodeSetValueType & code) noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    Future(const Future & cpy) noexcept;
    Future(Future && mov) noexcept;
public:
    Future & operator=(const Future &) = delete;
    Future & operator=(Future &&) = delete;
public:
    virtual const CharType * Message() const noexcept;
protected:
    virtual OutputValueType & Output(OutputValueType & out) const noexcept;
public:
    CodeType Code() const noexcept;
};

Future::Future(const CodeSetValueType & code) noexcept :
    TriggerType(constant::error::logic_future_id),
    SystemType(),
    m_code(code),
    exception::Logic(std::move(FutureCategoryType().Message(CodeType(code))))
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

Future::Future(const CodeSetValueType & code, const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(constant::error::logic_future_id, file, line),
        m_code(code),
        exception::Logic(std::move(FutureCategoryType().
            Message(CodeType(code))))
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

Future::Future(const Future & cpy) noexcept :
    TriggerType(cpy),
    SystemType(cpy),
    m_code(cpy.m_code),
    exception::Logic(cpy)
{}

Future::Future(Future && mov) noexcept :
    TriggerType(std::move(mov)),
    SystemType(std::move(mov)),
    m_code(std::move(mov.m_code)),
    exception::Logic(std::move(mov))
{}

const typename Future::CharType * Future::Message() const noexcept
{
    return exception::Logic::Message();
}

typename Future::OutputValueType & 
Future::Output(OutputValueType & out) const noexcept
{
    return exception::Logic::Output(out);
}

typename Future::CodeType Future::Code() const noexcept
{
    return {m_code};
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

using Future = std::future_error;

#endif //!USING_STANDARD_EXCEPTION

} //!logic

} //!exception

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger>
typename enable_if::tag::Trigger<TTagError>::Type 
Get(const std::future_error & e) noexcept
{
    return Standard(constant::error::logic_future_id);
}

template<typename TTagError = tag::Trigger>
typename enable_if::tag::System<TTagError>::Type 
Get(const std::future_error & e) noexcept
{
    return System(id::flag::Standard{}, 
        constant::error::system::future_category, e.code().value());
}

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_LOGIC_FUTURE_H_
