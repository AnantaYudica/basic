#ifndef BASIC_ERROR_H__FORWARD_DECLARATION_

#include "../../Error.h"

#else //else BASIC_ERROR_H__FORWARD_DECLARATION_

#ifndef BASIC_ERROR_TAG_TRIGGER_H_
#define BASIC_ERROR_TAG_TRIGGER_H_

#include "../Identification.h"
#include "../Information.h"
#include "../code/defn/type/Value.h"

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
class Error<error::tag::Trigger>
{
public:
    typedef BASIC_ERROR_CHAR_TYPE CharType;
    typedef BASIC_ERROR_CHARTRAIT_TYPE CharTraitType;
    typedef BASIC_ERROR_OUTPUT_TYPE OutputType;
public:
    typedef error::Identification IdType;
public:
    typedef error::code::defn::type::Value CodeValueType;
public:
    typedef error::Information InfoType;
private:
    const InfoType m_info;
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
    OutputType& Message(OutputType& out) const noexcept;
public:
    const InfoType& Information() const noexcept;
    CodeValueType Code() const noexcept;
};

Error<error::tag::Trigger>::Error() noexcept :
    m_info()
{}

Error<error::tag::Trigger>::Error(const IdType& id, const char* file, 
    const std::size_t& line) noexcept :
        m_info(id, file, line)
{}

Error<error::tag::Trigger>::Error(const Error<error::tag::Trigger>& cpy) 
    noexcept :
        m_info(cpy.m_info)
{}

Error<error::tag::Trigger>::Error(Error<error::tag::Trigger>&& mov) noexcept :
    m_info(std::move(mov.m_info))
{}

typename Error<error::tag::Trigger>::OutputType& 
    Error<error::tag::Trigger>::Message(OutputType& out) const noexcept
{
    BASIC_ERROR_OUTPUT_OPERATOR(out, this->Information());
    return out;
}

const typename Error<error::tag::Trigger>::InfoType& 
    Error<error::tag::Trigger>::Information() const noexcept
{
    return this->m_info;
}

typename Error<error::tag::Trigger>::CodeValueType
    Error<error::tag::Trigger>::Code() const noexcept
{
    return this->m_info.GetIdentification().Error().Code();
}

} //!basic

template<typename TChar, typename TCharTraits>
std::basic_ostream<TChar, TCharTraits>& operator<<(std::basic_ostream<TChar, 
    TCharTraits>& out, const basic::Error<basic::error::tag::Trigger>& err)
{
    return err.Message(out);
}

#endif //!BASIC_ERROR_TAG_TRIGGER_H_

#endif //!BASIC_ERROR_H__FORWARD_DECLARATION_
