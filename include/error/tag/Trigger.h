#ifndef BASIC_ERROR_H__FORWARD_DECLARATION_

#include "../../Error.h"

#else //else BASIC_ERROR_H__FORWARD_DECLARATION_

#ifndef BASIC_ERROR_TAG_TRIGGER_H_
#define BASIC_ERROR_TAG_TRIGGER_H_

#include "../Identification.h"
#include "../Information.h"
#include "../output/Interface.h"
#include "../output/Operator.h"
#include "../defn/type/Output.h"
#include "../defn/type/code/Value.h"

namespace basic
{
namespace error
{
namespace tag
{

struct Trigger {};

} //!tag

} //!error

template<>
class Error<error::tag::Trigger> :
    public error::Information
{
public:
    typedef error::defn::type::Output OutputValueType;
public:
    typedef error::Identification IdType;
public:
    typedef error::defn::type::code::Value CodeValueType;
public:
    typedef error::Information InfoType;
public:
    Error() noexcept;
    Error(const IdType& id, const char* file, 
        const std::size_t& line) noexcept;
public:
    Error(const Error<error::tag::Trigger>& cpy) noexcept;
    Error(Error<error::tag::Trigger>&& mov) noexcept;
public:
    Error<error::tag::Trigger>& 
        operator=(const Error<error::tag::Trigger>&) = delete;
    Error<error::tag::Trigger>& 
        operator=(Error<error::tag::Trigger>&&) = delete;
public:
    virtual const char* Message() const noexcept;
public:
    const InfoType& Information() const noexcept;
    CodeValueType Code() const noexcept;
protected:
    virtual OutputValueType& Output(OutputValueType& out) const noexcept;
};

Error<error::tag::Trigger>::Error() noexcept :
    InfoType()
{}

Error<error::tag::Trigger>::Error(const IdType& id, const char* file, 
    const std::size_t& line) noexcept :
        InfoType(id, file, line)
{}

Error<error::tag::Trigger>::Error(const Error<error::tag::Trigger>& cpy) 
    noexcept :
        InfoType(cpy)
{}

Error<error::tag::Trigger>::Error(Error<error::tag::Trigger>&& mov) noexcept :
    InfoType(std::move(mov))
{}

const char * Error<error::tag::Trigger>::Message() const noexcept
{
    return "";
}

const typename Error<error::tag::Trigger>::InfoType& 
    Error<error::tag::Trigger>::Information() const noexcept
{
    return *this;
}

typename Error<error::tag::Trigger>::CodeValueType
    Error<error::tag::Trigger>::Code() const noexcept
{
    return this->Identification().Error().Code();
}

typename Error<error::tag::Trigger>::OutputValueType& 
Error<error::tag::Trigger>::Output(OutputValueType& out) const noexcept
{
    error::Information::Output(out);
    return out;
}

} //!basic

template<typename TChar, typename TCharTraits>
std::basic_ostream<TChar, TCharTraits>& operator<<(std::basic_ostream<TChar, 
    TCharTraits>& out, const basic::Error<basic::error::tag::Trigger>& err)
{
    static_cast<const basic::error::output::Interface&>(err).Output(out);
    return out;
}

#endif //!BASIC_ERROR_TAG_TRIGGER_H_

#endif //!BASIC_ERROR_H__FORWARD_DECLARATION_
