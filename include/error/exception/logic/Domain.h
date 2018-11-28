#ifndef BASIC_ERROR_EXCEPTION_LOGIC_DOMAIN_H_
#define BASIC_ERROR_EXCEPTION_LOGIC_DOMAIN_H_

#include "../Logic.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../defn/type/Output.h"
#include "../../output/Operator.h"
#include "../../../constant/error/Identification.h"

#include <stdexcept>
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

class Domain : public exception::Logic
{
public:
    typedef typename error::Exception::TriggerType TriggerType;
public:
    typedef defn::type::Output OutputValueType;
protected:
    Domain() noexcept;
    Domain(const char * message) noexcept;
public:
    Domain(const char* file, const std::size_t& line) noexcept;
    Domain(const char * message, const char* file, 
        const std::size_t& line) noexcept;
public:
    Domain(const Domain& cpy) noexcept;
    Domain(Domain&& mov) noexcept;
public:
    Domain& operator=(const Domain&) = delete;
    Domain& operator=(Domain&&) = delete;
public:
    virtual const char* Message() const noexcept;
protected:
    virtual OutputValueType& Output(OutputValueType& out) const noexcept;
};

Domain::Domain() noexcept :
    exception::Logic("Domain Logic Exception")
{}

Domain::Domain(const char * message) noexcept :
    exception::Logic(message)
{}

Domain::Domain(const char* file, const std::size_t& line) noexcept :
    TriggerType(constant::error::logic_domain_id, file, line),
    exception::Logic("Domain Logic Exception")
{}

Domain::Domain(const char * message, const char* file, 
    const std::size_t& line) noexcept :
        TriggerType(constant::error::logic_domain_id, file, line),
        exception::Logic(message)
{}

Domain::Domain(const Domain& cpy) noexcept :
    TriggerType(cpy),
    exception::Logic(cpy)
{}

Domain::Domain(Domain&& mov) noexcept :
    TriggerType(std::move(mov)),
    exception::Logic(std::move(mov))
{}

const char* Domain::Message() const noexcept
{
    return exception::Logic::Message();
}

typename Domain::OutputValueType& 
Domain::Output(OutputValueType& out) const noexcept
{
    return exception::Logic::Output(out);
}

#endif //!USING_BASIC_ERROR_EXCEPTION

#ifdef USING_STANDARD_EXCEPTION

class Domain : public std::domain_error
{
public:
    Domain(const char* file, const std::size_t& line) noexcept;
    Domain(const char * what_arg, const char* file, 
        const std::size_t& line) noexcept;
public:
    Domain(const Domain& cpy) noexcept;
    Domain(Domain&& mov) noexcept;
public:
    virtual ~Domain() noexcept;
public:
    Domain& operator=(const Domain&) = delete;
    Domain& operator=(Domain&)& = delete;
public:
    virtual const char * what() const noexcept;
};

Domain::Domain(const char* file, const std::size_t& line) noexcept :
    std::domain_error("Domain Logic Exception")
{}

Domain::Domain(const char * what_arg, const char* file, 
    const std::size_t& line) noexcept :
        std::domain_error(what_arg)
{}

Domain::Domain(const Domain& cpy) noexcept :
    std::domain_error(cpy)
{}

Domain::Domain(Domain&& mov) noexcept :
    std::domain_error(mov)
{}

Domain::~Domain() noexcept
{}

const char * Domain::what() const noexcept
{
    return std::domain_error::what();
}

#endif //!USING_STANDARD_EXCEPTION

} //!logic

} //!exception

namespace id
{

#ifdef USING_EXCEPTION

#ifndef USING_STANDARD_EXCEPTION


constexpr Identification Get(const exception::logic::Domain& e)
{
    return Identification(constant::error::logic_domain_id);
};

#endif //!USING_STANDARD_EXCEPTION

constexpr Identification Get(const std::domain_error& e)
{
    return Standard(constant::error::logic_domain_id);
};

#endif //!USING_EXCEPTION

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_LOGIC_DOMAIN_H_
