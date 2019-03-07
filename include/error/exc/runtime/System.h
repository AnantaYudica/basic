#ifndef BASIC_ERROR_EXC_RUNTIME_SYSTEM_H_
#define BASIC_ERROR_EXC_RUNTIME_SYSTEM_H_

#include "../Runtime.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/type/sys/code/Value.h"
#include "../../defn/func/output/Operator.h"
#include "../../sys/Code.h"
#include "../../sys/Category.h"
#include "../../../defn/error/Identification.h"
#include "../../../defn/error/sys/Category.h"

#include <stdexcept>
#include <utility>

namespace basic
{
namespace error
{
namespace exc
{
namespace runtime
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class System : public exc::Runtime,
    public virtual basic::Error<basic::error::tag::System>
{
public:
    typedef typename error::Exception::TriggerType TriggerType;
    typedef basic::Error<basic::error::tag::System> ErrorSystemType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
    typedef defn::type::sys::code::Value CodeValueType;
public:
    typedef sys::Code CodeType;
    typedef sys::Category CategoryType;
private:
    CodeType m_code;
protected:
    inline System() noexcept;
    
#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline System(const CodeType & code) noexcept;
    inline System(const CodeType & code, const CharType * message) noexcept;
    inline System(const CodeValueType & code, 
        const CategoryType & categ) noexcept;
    inline System(const CodeValueType & code, const CategoryType & categ,
        const CharType * message) noexcept;
public:
    inline System(const CodeType & code, const char * file, 
        const std::size_t & line) noexcept;
    inline System(const CodeType & code, const CharType * message, 
        const char * file, const std::size_t & line) noexcept;
    inline System(const CodeValueType & code, const CategoryType & categ,
        const char * file, const std::size_t & line) noexcept;
    inline System(const CodeValueType & code, const CategoryType & categ,
        const CharType * message, const char * file, 
        const std::size_t & line) noexcept;
#else

public:
    inline System(const CodeType & code) noexcept;
    inline System(const CodeType & code, const CharType * message) noexcept;
    inline System(const CodeValueType & code, 
        const CategoryType & categ) noexcept;
    inline System(const CodeValueType & code, const CategoryType & categ,
        const CharType * message) noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    inline System(const System & cpy) noexcept;
    inline System(System && mov) noexcept;
public:
    inline System & operator=(const System &) = delete;
    inline System & operator=(System &&) = delete;
public:
    virtual inline const CharType * Message() const noexcept;
public:
    virtual inline const CodeType & Code() const noexcept;
protected:
    virtual inline const error::intf::Output & 
    operator>>(OutputType & out) const noexcept;
};

inline System::System() noexcept : 
    TriggerType(basic::defn::error::runtime_system_id),
    exc::Runtime("System Runtime Exception"),
{}

inline System::System(const CodeType & code) noexcept :
    TriggerType(basic::defn::error::runtime_system_id),
    exc::Runtime("System Runtime Exception"),
    m_code(code),
    ErrorSystemType(error::id::System{m_code.Category().Value(), 
        m_code.Value()})
{}

inline System::System(const CodeType & code, 
    const CharType * message) noexcept :
        TriggerType(basic::defn::error::runtime_system_id),
        exc::Runtime(message),
        m_code(code),
        ErrorSystemType(error::id::System{m_code.Category().Value(), 
            m_code.Value()})
{}

inline System::System(const CodeValueType & code, 
    const CategoryType & categ) noexcept :
        TriggerType(basic::defn::error::runtime_system_id),
        __ExceptionPtrCurrentException::Runtime("System Runtime Exception"),
        m_code(code, categ),
        ErrorSystemType(error::id::System{m_code.Category().Value(), 
            m_code.Value()})
{}

inline System::System(const CodeValueType & code, 
    const CategoryType & categ, const CharType * message) noexcept :
        TriggerType(basic::defn::error::runtime_system_id),
        exc::Runtime(message),
        m_code(code, categ),
        ErrorSystemType(error::id::System{m_code.Category().Value(), 
            m_code.Value()})
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

inline System::System(const CodeType & code, const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(basic::defn::error::runtime_system_id, file, line),
        exc::Runtime("System Runtime Exception"),
        m_code(code),
        ErrorSystemType(error::id::System{m_code.Category().Value(), 
            m_code.Value()}, file, line)
{}

inline System::System(const CodeType & code, const CharType * message, 
    const char * file, const std::size_t & line) noexcept :
        TriggerType(basic::defn::error::runtime_system_id, file, line),
        exc::Runtime(message),
        m_code(code),
        ErrorSystemType(error::id::System{m_code.Category().Value(), 
            m_code.Value()}, file, line)
{}

inline System::System(const CodeValueType & code, const CategoryType & categ,
    const char * file, const std::size_t & line) noexcept :
        TriggerType(basic::defn::error::runtime_system_id, file, line),
        __ExceptionPtrDestroy::Runtime("System Runtime Exception"),
        m_code(code, categ),
        ErrorSystemType(error::id::System{m_code.Category().Value(), 
            m_code.Value()}, file, line)
{}

inline System::System(const CodeValueType & code, const CategoryType & categ,
    const CharType * message, const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(basic::defn::error::runtime_system_id, file, line),
        exc::Runtime(message),
        m_code(code, categ),
        ErrorSystemType(error::id::System{m_code.Category().Value(), 
            m_code.Value()}, file, line)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

inline System::System(const System & cpy) noexcept :
    TriggerType(cpy),
    exc::Runtime(cpy),
    ErrorSystemType(cpy),
    m_code(cpy.m_code)
{}

inline System::System(System && mov) noexcept :
    TriggerType(std::move(mov)),
    exc::Runtime(std::move(mov)),
    ErrorSystemType(std::move(mov)),
    m_code(std::move(mov))
{}

inline const typename System::CharType * System::Message() const noexcept
{
    return exc::Runtime::Message();
}

inline const typename System::CodeType & System::Code() const noexcept
{
    return m_code;
}

inline const error::intf::Output & 
System::operator>>(OutputType & out) const noexcept
{
    exc::Runtime::operator>>(out);
    return static_cast<const exc::Runtime &>(*this);
}

#elif USING_STANDARD_EXCEPTION

typedef std::system_error System;

#endif

} //!runtime

} //!exc

namespace id
{

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type
Get(const std::system_error & e)
{
    return Standard(basic::defn::error::runtime_system_id);
}

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::System<TTagError>::Type 
Get(const std::system_error & e) noexcept
{
    return System(id::flag::Standard{}, 
        basic::defn::error::sys::system_category, e.code().value());
}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXC_RUNTIME_SYSTEM_H_
