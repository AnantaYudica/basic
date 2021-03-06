#ifndef BASIC_ERR_EXC_LOGIC_FUTURE_H_
#define BASIC_ERR_EXC_LOGIC_FUTURE_H_

#include "../Logic.h"
#include "../../tag/System.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/func/output/Operator.h"
#include "../../msg/String.h"
#include "../../sys/categ/Future.h"
#include "../../sys/Category.h"
#include "../../sys/tmpl/Category.h"
#include "../../sys/Code.h"
#include "../../../defn/err/Identification.h"
#include "../../../defn/err/sys/Category.h"

#include <future>
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

class Future : public exc::Logic,
    virtual public basic::Error<basic::err::tag::System>
{
public:
    typedef typename err::Exception::TriggerType TriggerType;
    typedef basic::Error<basic::err::tag::System> ErrorSystemType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
public:
    typedef sys::tmpl::Category<sys::categ::Future> 
        FutureCategoryType;
    typedef sys::Code CodeType;
    typedef typename FutureCategoryType::CodeSetValueType CodeSetValueType;
private:
    CodeType m_code;

#ifdef USING_BASIC_ERR_FILE_AND_LINE

protected:
    inline Future(const CodeSetValueType & code) noexcept;
public:
    inline Future(const CodeSetValueType & code, const char * file, 
        const std::size_t & line) noexcept;

#else

public:
    inline Future(const CodeSetValueType & code) noexcept;

#endif //!USING_BASIC_ERR_FILE_AND_LINE

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
    virtual inline const err::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

inline Future::Future(const CodeSetValueType & code) noexcept :
#ifdef USING_BASIC_ERR_FILE_AND_LINE
    TriggerType(basic::defn::err::logic_future_id,
        "unknown", static_cast<std::size_t>(-1)),
#else
    TriggerType(basic::defn::err::logic_future_id),
#endif //!USING_BASIC_ERR_FILE_AND_LINE
    exc::Logic("Future Logic Exception"),
    m_code(code),
    ErrorSystemType(err::id::System{m_code.Category().Value(), 
        m_code.Value()})
{}

#ifdef USING_BASIC_ERR_FILE_AND_LINE

inline Future::Future(const CodeSetValueType & code, const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(basic::defn::err::logic_future_id, file, line),
        exc::Logic("Future Logic Exception"),
        m_code(code),
        ErrorSystemType(err::id::System{m_code.Category().Value(), 
            m_code.Value()}, file, line)
{}

#endif //!USING_BASIC_ERR_FILE_AND_LINE

inline Future::Future(const Future & cpy) noexcept :
    TriggerType(cpy),
    ErrorSystemType(cpy),
    m_code(cpy.m_code),
    __ExceptionPtrCopyException::Logic(cpy)
{}

inline Future::Future(Future && mov) noexcept :
    TriggerType(std::move(mov)),
    ErrorSystemType(std::move(mov)),
    m_code(std::move(mov.m_code)),
    exc::Logic(std::move(mov))
{}

inline const typename Future::CharType * Future::Message() const noexcept
{
    return exc::Logic::Message();
}

inline const typename Future::CodeType & Future::Code() const noexcept
{
    return m_code;
}

inline const err::intf::Output & 
Future::operator>>(OutputType & out) const noexcept
{
    exc::Logic::operator>>(out);
    return static_cast<const exc::Logic &>(*this);
}


#endif //!USING_BASIC_ERR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

using Future = std::future_error;

#endif //!USING_STANDARD_EXCEPTION

} //!logic

} //!exc

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger,
    typename TException>
inline typename enable_if::tag::Trigger<TTagError,
    std::is_same<TException, std::future_error>::value>::Type 
Get(const TException & e) noexcept
{
    return Standard(basic::defn::err::logic_future_id);
}

template<typename TTagError = tag::Trigger,
    typename TException>
inline typename enable_if::tag::System<TTagError,
    std::is_same<TException, std::future_error>::value>::Type 
Get(const TException & e) noexcept
{
    return System(id::flag::Standard{}, 
        basic::defn::err::sys::future_category, e.code().value());
}

#endif //!USING_EXCEPTION

} //!id

} //!err

} //!basic

#endif //!BASIC_ERR_EXC_LOGIC_FUTURE_H_
