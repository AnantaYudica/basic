#ifndef BASIC_ERROR_H__FORWARD_DECLARATION_

#include "../../Error.h"

#else //else BASIC_ERROR_H__FORWARD_DECLARATION_

#ifndef BASIC_ERROR_TAG_CATCH_H_
#define BASIC_ERROR_TAG_CATCH_H_

#include "Trigger.h"
#include "../id/Catch.h"

#include <ostream>
#include <exception>

namespace basic
{
namespace error
{
namespace tag
{

template<typename TTrigger = Error<error::tag::Trigger>>
struct Catch {};

} //!tag

} //!error

template<typename TTrigger>
class Error<error::tag::Catch<TTrigger>> : 
    public Error<error::tag::Trigger>
{
public:
    typedef Error<error::tag::Trigger> BaseType;
public:
    typedef BASIC_ERROR_CHAR_TYPE CharType;
    typedef BASIC_ERROR_CHARTRAIT_TYPE CharTraitType;
    typedef BASIC_ERROR_OUTPUT_TYPE OutputType;
private:
    TTrigger m_trigger;
public:
    Error() noexcept;
    Error(const TTrigger& trigger, const error::id::Catch& id, 
        const char* file, const std::size_t& line) noexcept;
public:
    Error(const Error<error::tag::Catch<TTrigger>>& cpy) noexcept;
    Error(Error<error::tag::Catch<TTrigger>>&& mov) noexcept;
public:
    Error<error::tag::Catch>& 
        operator=(const Error<error::tag::Catch>&) = delete;
    Error<error::tag::Catch>& 
        operator=(Error<error::tag::Catch>&&) = delete;
public:
    OutputType& Message(OutputType& out) const noexcept;
public:
    const TTrigger& Trigger() const noexcept;
};

template<typename TTrigger>
Error<error::tag::Catch<TTrigger>>::Error() noexcept :
    BaseType(),
    m_trigger()
{}

template<typename TTrigger>
Error<error::tag::Catch<TTrigger>>::Error(const TTrigger& trigger, 
    const error::id::Catch& id, const char* file, const std::size_t& line) 
        noexcept :
            m_trigger(err),
            BaseType(id, file, line),
{}

template<typename TTrigger>
typename Error<error::tag::Catch<TTrigger>>::OutputType& 
    Error<error::tag::Catch<TTrigger>>::Message(OutputType& out) const noexcept
{
    BASIC_ERROR_OUTPUT_OPERATOR(out, "in catch ");
    BASIC_ERROR_OUTPUT_OPERATOR(out, this->GetInformation());
    return out;
}

template<typename TTrigger>
const TTrigger& Error<error::tag::Catch<TTrigger>>::Trigger() const noexcept
{
    return m_trigger;
}

} //!basic

#endif //!BASIC_ERROR_TAG_CATCH_H_

#endif //!BASIC_ERROR_H__FORWARD_DECLARATION_
