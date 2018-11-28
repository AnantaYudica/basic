#ifndef BASIC_ERROR_EXCEPTION_H_
#define BASIC_ERROR_EXCEPTION_H_

#include "../Error.h"
#include "tag/Trigger.h"
#include "Identification.h"
#include "id/Get.h"
#include "id/Standard.h"
#include "defn/type/Output.h"
#include "output/Operator.h"
#include "../constant/error/Identification.h"

#include <exception>
#include <utility>

namespace basic
{
namespace error
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class Exception : public virtual Error<tag::Trigger>
{
public:
    typedef Error<tag::Trigger> TriggerType;
public:
    typedef defn::type::Output OutputValueType;
protected:
    Exception() noexcept;
public:
    Exception(const char* file, const std::size_t& line) noexcept;
public:
    Exception(const Exception& cpy) noexcept;
    Exception(Exception&& mov) noexcept;
public:
    Exception& operator=(const Exception&) = delete;
    Exception& operator=(Exception&&) = delete;
public:
    virtual const char* Message() const noexcept;
protected:
    virtual OutputValueType& Output(OutputValueType& out) const noexcept;
};

Exception::Exception() noexcept
{}

Exception::Exception(const char* file, const std::size_t& line) noexcept :
    TriggerType(constant::error::exception_id, file, line)
{}

Exception::Exception(const Exception& cpy) noexcept :
    TriggerType(cpy)
{}

Exception::Exception(Exception&& mov) noexcept :
    TriggerType(std::move(mov))
{}

const char* Exception::Message() const noexcept
{
    return "Exception";
}

typename Exception::OutputValueType& 
Exception::Output(OutputValueType& out) const noexcept
{
    output::Operator(out, this->Message(), " ");
    TriggerType::Output(out);
    return out;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

class Exception : public std::exception
{
protected:
    Exception() noexcept;
public:
    Exception(const char* file, const std::size_t& line) noexcept;
public:
    Exception(const Exception& cpy) noexcept;
    Exception(Exception&& mov) noexcept;
public:
    virtual ~Exception() noexcept;
public:
    Exception& operator=(const Exception&) = delete;
    Exception& operator=(Exception&)& = delete;
public:
    virtual const char * what() const noexcept;
};

Exception::Exception() noexcept
{}

Exception::Exception(const char* file, const std::size_t& line) noexcept
{}

Exception::Exception(const Exception& cpy) noexcept :
    std::exception(cpy)
{}

Exception::Exception(Exception&& mov) noexcept :
    std::exception(mov)
{}

Exception::~Exception() noexcept
{}

const char * Exception::what() const noexcept
{
    return std::exception::what();
}

#endif //!USING_STANDARD_EXCEPTION

namespace id
{

#ifdef USING_EXCEPTION

#ifndef USING_STANDARD_EXCEPTION

constexpr Identification Get(const Exception& e) noexcept
{
    return Identification(constant::error::exception_id);
}

#endif //!USING_STANDARD_EXCEPTION

constexpr Identification Get(const std::exception& e) noexcept
{
    return Standard(constant::error::exception_id);
}

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_H_
