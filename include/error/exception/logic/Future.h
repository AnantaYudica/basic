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
#include "../../system/category/Future.h"
#include "../../system/Category.h"
#include "../../system/tmpl/Category.h"
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
    virtual public basic::Error<basic::error::tag::System>
{
public:
    typedef typename error::Exception::TriggerType TriggerType;
    typedef basic::Error<basic::error::tag::System> SystemType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
public:
    typedef system::tmpl::Category<system::category::Future> 
        FutureCategoryType;
    typedef system::Code CodeType;
    typedef typename FutureCategoryType::CodeSetValueType CodeSetValueType;
private:
    CodeType m_code;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline Future(const CodeSetValueType & code) noexcept;
public:
    inline Future(const CodeSetValueType & code, const char * file, 
        const std::size_t & line) noexcept;

#else

public:
    inline Future(const CodeSetValueType & code) noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    inline Future(const Future & cpy) noexcept;
    inline Future(Future && mov) noexcept;
public:
    inline Future & operator=(const Future &) = delete;
    inline Future & operator=(Future &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
public:
    virtual inline const CodeType & Code() const noexcept;
protected:
    virtual inline const error::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

inline Future::Future(const CodeSetValueType & code) noexcept :
    TriggerType(constant::error::logic_future_id),
    exception::Logic("Future Logic Exception"),
    m_code(code),
    SystemType(error::id::System{m_code.Category().Value(), m_code.Value()})
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

inline Future::Future(const CodeSetValueType & code, const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(constant::error::logic_future_id, file, line),
        exception::Logic("Future Logic Exception"),
        m_code(code),
        SystemType(error::id::System{m_code.Category().Value(), 
            m_code.Value()}, file, line)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

inline Future::Future(const Future & cpy) noexcept :
    TriggerType(cpy),
    SystemType(cpy),
    m_code(cpy.m_code),
    exception::Logic(cpy)
{}

inline Future::Future(Future && mov) noexcept :
    TriggerType(std::move(mov)),
    SystemType(std::move(mov)),
    m_code(std::move(mov.m_code)),
    exception::Logic(std::move(mov))
{}

inline const typename Future::CharType * Future::Message() const noexcept
{
    return exception::Logic::Message();
}

inline const typename Future::CodeType & Future::Code() const noexcept
{
    return m_code;
}

inline const error::intf::Output & 
Future::operator>>(OutputType & out) const noexcept
{
    exception::Logic::operator>>(out);
    return static_cast<const exception::Logic &>(*this);
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
inline typename enable_if::tag::Trigger<TTagError>::Type 
Get(const std::future_error & e) noexcept
{
    return Standard(constant::error::logic_future_id);
}

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::System<TTagError>::Type 
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
