#ifndef BASIC_ERROR_EXCEPTION_RUNTIME_SYSTEM_H_
#define BASIC_ERROR_EXCEPTION_RUNTIME_SYSTEM_H_

#include "../Runtime.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/type/system/code/Value.h"
#include "../../output/Operator.h"
#include "../../system/Code.h"
#include "../../system/Category.h"
#include "../../../constant/error/Identification.h"
#include "../../../constant/error/system/Category.h"

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

class System : public exception::Runtime,
    public virtual basic::Error<basic::error::tag::System>
{
public:
    typedef typename error::Exception::TriggerType TriggerType;
    typedef basic::Error<basic::error::tag::System> ErrorSystemType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
    typedef defn::type::system::code::Value CodeValueType;
public:
    typedef system::Code CodeType;
    typedef system::Category CategoryType;
private:
    CodeType m_code;
protected:
    inline System() noexcept;
    
#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    inline System(const CodeType & code) noexcept;
    inline System(const CodeType & code, const CharType * message) noexcept;
    inline System(const CodeValueType & code, 
        const CategoryType & category) noexcept;
    inline System(const CodeValueType & code, const CategoryType & category,
        const CharType * message) noexcept;
public:
    inline System(const CodeType & code, const char * file, 
        const std::size_t & line) noexcept;
    inline System(const CodeType & code, const CharType * message, 
        const char * file, const std::size_t & line) noexcept;
    inline System(const CodeValueType & code, const CategoryType & category,
        const char * file, const std::size_t & line) noexcept;
    inline System(const CodeValueType & code, const CategoryType & category,
        const CharType * message, const char * file, 
        const std::size_t & line) noexcept;
#else

public:
    inline System(const CodeType & code) noexcept;
    inline System(const CodeType & code, const CharType * message) noexcept;
    inline System(const CodeValueType & code, 
        const CategoryType & category) noexcept;
    inline System(const CodeValueType & code, const CategoryType & category,
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
    TriggerType(constant::error::runtime_system_id),
    exception::Runtime("System Runtime Exception"),
{}

inline System::System(const CodeType & code) noexcept :
    TriggerType(constant::error::runtime_system_id),
    exception::Runtime("System Runtime Exception"),
    m_code(code),
    ErrorSystemType(error::id::System{m_code.Category().Value(), 
        m_code.Value()})
{}

inline System::System(const CodeType & code, 
    const CharType * message) noexcept :
        TriggerType(constant::error::runtime_system_id),
        exception::Runtime(message),
        m_code(code),
        ErrorSystemType(error::id::System{m_code.Category().Value(), 
            m_code.Value()})
{}

inline System::System(const CodeValueType & code, 
    const CategoryType & category) noexcept :
        TriggerType(constant::error::runtime_system_id),
        exception::Runtime("System Runtime Exception"),
        m_code(code, category),
        ErrorSystemType(error::id::System{m_code.Category().Value(), 
            m_code.Value()})
{}

inline System::System(const CodeValueType & code, 
    const CategoryType & category, const CharType * message) noexcept :
        TriggerType(constant::error::runtime_system_id),
        exception::Runtime(message),
        m_code(code, category),
        ErrorSystemType(error::id::System{m_code.Category().Value(), 
            m_code.Value()})
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

inline System::System(const CodeType & code, const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(constant::error::runtime_system_id, file, line),
        exception::Runtime("System Runtime Exception"),
        m_code(code),
        ErrorSystemType(error::id::System{m_code.Category().Value(), 
            m_code.Value()}, file, line)
{}

inline System::System(const CodeType & code, const CharType * message, 
    const char * file, const std::size_t & line) noexcept :
        TriggerType(constant::error::runtime_system_id, file, line),
        exception::Runtime(message),
        m_code(code),
        ErrorSystemType(error::id::System{m_code.Category().Value(), 
            m_code.Value()}, file, line)
{}

inline System::System(const CodeValueType & code, const CategoryType & category,
    const char * file, const std::size_t & line) noexcept :
        TriggerType(constant::error::runtime_system_id, file, line),
        exception::Runtime("System Runtime Exception"),
        m_code(code, category),
        ErrorSystemType(error::id::System{m_code.Category().Value(), 
            m_code.Value()}, file, line)
{}

inline System::System(const CodeValueType & code, const CategoryType & category,
    const CharType * message, const char * file, 
    const std::size_t & line) noexcept :
        TriggerType(constant::error::runtime_system_id, file, line),
        exception::Runtime(message),
        m_code(code, category),
        ErrorSystemType(error::id::System{m_code.Category().Value(), 
            m_code.Value()}, file, line)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

inline System::System(const System & cpy) noexcept :
    TriggerType(cpy),
    exception::Runtime(cpy),
    ErrorSystemType(cpy),
    m_code(cpy.m_code)
{}

inline System::System(System && mov) noexcept :
    TriggerType(std::move(mov)),
    exception::Runtime(std::move(mov)),
    ErrorSystemType(std::move(mov)),
    m_code(std::move(mov))
{}

inline const typename System::CharType * System::Message() const noexcept
{
    return exception::Runtime::Message();
}

inline const typename System::CodeType & System::Code() const noexcept
{
    return m_code;
}

inline const error::intf::Output & 
System::operator>>(OutputType & out) const noexcept
{
    exception::Runtime::operator>>(out);
    return static_cast<const exception::Runtime &>(*this);
}

#elif USING_STANDARD_EXCEPTION

typedef std::system_error System;

#endif

} //!runtime

} //!exception

namespace id
{

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::Trigger<TTagError>::Type
Get(const std::system_error & e)
{
    return Standard(constant::error::runtime_system_id);
}

template<typename TTagError = tag::Trigger>
inline typename enable_if::tag::System<TTagError>::Type 
Get(const std::system_error & e) noexcept
{
    return System(id::flag::Standard{}, 
        constant::error::system::system_category, e.code().value());
}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_RUNTIME_SYSTEM_H_
