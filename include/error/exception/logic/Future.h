#ifndef BASIC_ERROR_EXCEPTION_LOGIC_FUTURE_H_
#define BASIC_ERROR_EXCEPTION_LOGIC_FUTURE_H_

#include "../Logic.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Output.h"
#include "../../output/Operator.h"
#include "../../system/category/trait/Future.h"
#include "../../system/Category.h"
#include "../../system/Code.h"
#include "../../../constant/error/Identification.h"

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

class Future : public exception::Logic
{
public:
    typedef typename error::Exception::TriggerType TriggerType;
public:
    typedef defn::type::Output OutputValueType;
public:
    typedef system::Category<system::category::trait::Future> 
        FutureCategoryType;
    typedef system::Code<system::category::trait::Future> CodeType;
    typedef typename FutureCategoryType::CodeSetValueType CodeSetValueType;
private:
    CodeType m_code;
protected:
    Future(const CodeSetValueType& code) noexcept;
public:
    Future(const CodeSetValueType& code, const char* file, 
        const std::size_t& line) noexcept;
public:
    Future(const Future& cpy) noexcept;
    Future(Future&& mov) noexcept;
public:
    virtual ~Future() noexcept;
public:
    Future& operator=(const Future&) = delete;
    Future& operator=(Future&&) = delete;
public:
    virtual const char* Message() const noexcept;
protected:
    virtual OutputValueType& Output(OutputValueType& out) const noexcept;
public:
    const CodeType& Code() const noexcept;
};

Future::Future(const CodeSetValueType& code) noexcept :
    m_code(code),
    exception::Logic(this->m_code.Message())
{}

Future::Future(const CodeSetValueType& code, const char* file, 
    const std::size_t& line) noexcept :
        TriggerType(constant::error::logic_future_id, file, line),
        m_code(code),
        exception::Logic(this->m_code.Message())
{}

Future::Future(const Future& cpy) noexcept :
    TriggerType(cpy),
    m_code(cpy.m_code),
    exception::Logic(this->m_code.Message())
{}

Future::Future(Future&& mov) noexcept :
    TriggerType(std::move(mov)),
    m_code(std::move(mov.m_code)),
    exception::Logic(this->m_code.Message())
{}

Future::~Future() noexcept
{}

const char* Future::Message() const noexcept
{
    return exception::Logic::Message();
}

typename Future::OutputValueType& 
Future::Output(OutputValueType& out) const noexcept
{
    return exception::Logic::Output(out);
}

const typename Future::CodeType & Future::Code() const noexcept
{
    return m_code;
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

class Future : public std::future_error
{
protected:
    Future(const std::future_errc& code) noexcept;
public:
    Future(const std::future_errc& code, const char* file, 
        const std::size_t& line) noexcept;
public:
    Future(const Future& cpy) noexcept;
    Future(Future&& mov) noexcept;
public:
    virtual ~Future() noexcept;
public:
    Future& operator=(const Future&) = delete;
    Future& operator=(Future&)& = delete;
public:
    virtual const char * what() const noexcept;
public:
    const std::error_code& code() const noexcept;
};

Future::Future(const std::future_errc& code) noexcept :
    std::future_error(code)
{}

Future::Future(const std::future_errc& code, const char* file, 
    const std::size_t& line) noexcept :
        std::future_error(code)
{}

Future::Future(const Future& cpy) noexcept :
    std::future_error(cpy)
{}

Future::Future(Future&& mov) noexcept :
    std::future_error(std::move(mov))
{}

Future::~Future() noexcept
{}

const char * Future::what() const noexcept
{
    return std::future_error::what();
}

const std::error_code& Future::code() const noexcept
{
    return std::future_error::code();
}

#endif //!USING_STANDARD_EXCEPTION

} //!logic

} //!exception

namespace id
{

#ifdef USING_EXCEPTION

#ifndef USING_STANDARD_EXCEPTION

constexpr Identification Get(const exception::logic::Future& e)
{
    return Identification(constant::error::logic_future_id);
};

#endif //!USING_STANDARD_EXCEPTION

constexpr Identification Get(const std::future_error& e)
{
    return Standard(constant::error::logic_future_id);
};

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_LOGIC_FUTURE_H_
