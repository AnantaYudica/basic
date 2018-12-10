#ifndef BASIC_ERROR_EXCEPTION_RUNTIME_H_
#define BASIC_ERROR_EXCEPTION_RUNTIME_H_

#include "../Exception.h"
#include "../Identification.h"
#include "../id/Get.h"
#include "../id/Standard.h"
#include "../defn/type/Char.h"
#include "../defn/type/Output.h"
#include "../output/Operator.h"
#include "../msg/String.h"
#include "../../constant/error/Identification.h"

#include <stdexcept>
#include <utility>

namespace basic
{
namespace error
{
namespace exception
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class Runtime : public error::Exception
{
public:
    typedef typename error::Exception::TriggerType TriggerType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputValueType;
public:
    typedef msg::String StringType;
private:
    StringType m_message;
protected:
    Runtime() noexcept;

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

protected:
    Runtime(const CharType * message) noexcept;
public:
    Runtime(const CharType * message, const char* file, 
        const std::size_t& line) noexcept;

#else

public:
    Runtime(const CharType * message) noexcept;

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

public:
    Runtime(const Runtime & cpy) noexcept;
    Runtime(Runtime && mov) noexcept;
public:
    Runtime & operator=(const Runtime &) = delete;
    Runtime & operator=(Runtime &&) = delete;
public:
    virtual const CharType * Message() const noexcept;
protected:
    virtual OutputValueType& Output(OutputValueType& out) const noexcept;
};

Runtime::Runtime() noexcept :
    TriggerType(constant::error::runtime_id),
    m_message("Runtime Exception")
{}

Runtime::Runtime(const CharType * message) noexcept :
    TriggerType(constant::error::runtime_id),
    m_message(message)
{}

#ifdef USING_BASIC_ERROR_FILE_AND_LINE

Runtime::Runtime(const CharType * message, const char* file, 
    const std::size_t& line) noexcept :
        TriggerType(constant::error::runtime_id, file, line),
        m_message(message)
{}

#endif //!USING_BASIC_ERROR_FILE_AND_LINE

Runtime::Runtime(const Runtime& cpy) noexcept :
    TriggerType(cpy),
    error::Exception(cpy)
{}

Runtime::Runtime(Runtime&& mov) noexcept :
    TriggerType(std::move(mov)),
    error::Exception(std::move(mov))
{}

const typename Runtime::CharType * Runtime::Message() const noexcept
{
    if (m_message)
        return m_message.Value();
    return "Runtime Exception";
}

typename Runtime::OutputValueType& 
Runtime::Output(OutputValueType& out) const noexcept
{
    error::Exception::Output(out);
    return out;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

typedef std::runtime_error Runtime;

#endif

} //!exception

namespace id
{

#ifdef USING_EXCEPTION

template<typename TTagError = tag::Trigger>
typename enable_if::tag::Trigger<TTagError>::Type 
Get(const std::runtime_error& e) noexcept
{
    return Standard(constant::error::runtime_id);
};

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_RUNTIME_H_
