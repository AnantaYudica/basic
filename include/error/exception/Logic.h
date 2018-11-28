#ifndef BASIC_ERROR_EXCEPTION_LOGIC_H_
#define BASIC_ERROR_EXCEPTION_LOGIC_H_

#include "../Exception.h"
#include "../Identification.h"
#include "../id/Get.h"
#include "../id/Standard.h"
#include "../defn/type/Output.h"
#include "../output/Operator.h"
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

class Logic : public error::Exception
{
public:
    typedef typename error::Exception::TriggerType TriggerType;
public:
    typedef defn::type::Output OutputValueType;
private:
    const char * m_message;
protected:
    Logic() noexcept;
    Logic(const char * message) noexcept;
public:
    Logic(const char* file, const std::size_t& line) noexcept;
    Logic(const char * message, const char* file, 
        const std::size_t& line) noexcept;
public:
    Logic(const Logic& cpy) noexcept;
    Logic(Logic&& mov) noexcept;
public:
    Logic& operator=(const Logic&) = delete;
    Logic& operator=(Logic&&) = delete;
public:
    virtual const char* Message() const noexcept;
protected:
    virtual OutputValueType& Output(OutputValueType& out) const noexcept;
};

Logic::Logic() noexcept :
    m_message(nullptr)
{}

Logic::Logic(const char * message) noexcept :
    m_message(message)
{}

Logic::Logic(const char* file, const std::size_t& line) noexcept :
    m_message(nullptr),
    TriggerType(constant::error::logic_id, file, line)
{}

Logic::Logic(const char * message, const char* file, 
    const std::size_t& line) noexcept :
        m_message(message),
        TriggerType(constant::error::logic_id, file, line)
{}

Logic::Logic(const Logic& cpy) noexcept :
    m_message(cpy.m_message),
    TriggerType(cpy),
    error::Exception(cpy)
{}

Logic::Logic(Logic&& mov) noexcept :
    m_message(std::move(mov.m_message)),
    TriggerType(std::move(mov)),
    error::Exception(std::move(mov))
{}

const char* Logic::Message() const noexcept
{
    if (m_message != nullptr)
        return m_message;
    return "Logic Exception";
}

typename Logic::OutputValueType& 
Logic::Output(OutputValueType& out) const noexcept
{
    error::Exception::Output(out);
    return out;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

class Logic : public std::logic_error
{
public:
    Logic(const char* file, const std::size_t& line) noexcept;
    Logic(const char * message, const char* file, 
        const std::size_t& line) noexcept;
public:
    Logic(const Logic& cpy) noexcept;
    Logic(Logic&& mov) noexcept;
public:
    virtual ~Logic() noexcept;
public:
    Logic& operator=(const Logic&) = delete;
    Logic& operator=(Logic&)& = delete;
public:
    virtual const char * what() const noexcept;
};

Logic::Logic(const char* file, const std::size_t& line) noexcept :
    std::logic_error("Logic Exception")
{}

Logic::Logic(const char * what_arg, const char* file, 
    const std::size_t& line) noexcept :
        std::logic_error(what_arg)
{}

Logic::Logic(const Logic& cpy) noexcept :
    std::logic_error(cpy)
{}

Logic::Logic(Logic&& mov) noexcept :
    std::logic_error(mov)
{}

Logic::~Logic() noexcept
{}

const char * Logic::what() const noexcept
{
    return std::logic_error::what();
}

#endif //!USING_STANDARD_EXCEPTION

} //!exception

namespace id
{

#ifdef USING_EXCEPTION

#ifndef USING_STANDARD_EXCEPTION

constexpr Identification Get(const exception::Logic& e)
{
    return Identification(constant::error::logic_id);
};

#endif //!USING_STANDARD_EXCEPTION

constexpr Identification Get(const std::logic_error& e)
{
    return Standard(constant::error::logic_id);
};

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_LOGIC_H_
