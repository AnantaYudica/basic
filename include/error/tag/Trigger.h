#ifndef BASIC_ERROR_H__FORWARD_DECLARATION_

#include "../../Error.h"

#else //else BASIC_ERROR_H__FORWARD_DECLARATION_

#ifndef BASIC_ERROR_TAG_TRIGGER_H_
#define BASIC_ERROR_TAG_TRIGGER_H_

#include "../Identification.h"
#include "../id/Catch.h"
#include "../id/Standard.h"
#include "../Information.h"

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
    typedef error::Information InfoType;
private:
    const InfoType m_info;
public:
    Error();
    Error(const IdType& id, const char* file, 
        const std::size_t& line);
protected:
    Error(const error::id::Catch& id,
        const char* file, const std::size_t& line);
    Error(const error::id::Standard& id,
        const char* file, const std::size_t& line);
public:
    Error(const Error<error::tag::Trigger>& cpy);
    Error(Error<error::tag::Trigger>&& mov);
public:
    ~Error();
public:
    Error<error::tag::Trigger>& 
        operator=(const Error<error::tag::Trigger>&) = delete;
    Error<error::tag::Trigger>& 
        operator=(Error<error::tag::Trigger>&&) = delete;
public:
    OutputType& Message(OutputType& out) const;
public:
    const InfoType& GetInformation() const;
};

Error<error::tag::Trigger>::Error() :
    m_info()
{}

Error<error::tag::Trigger>::Error(const IdType& id, const char* file, 
    const std::size_t& line) :
        m_info(id, file, line)
{}

Error<error::tag::Trigger>::Error(const error::id::Catch& id,
    const char* file, const std::size_t& line) :
        m_info(id, file, line)
{}

Error<error::tag::Trigger>::Error(const error::id::Standard& id,
    const char* file, const std::size_t& line) :
        m_info(id, file, line)
{}

Error<error::tag::Trigger>::Error(const Error<error::tag::Trigger>& cpy) :
    m_info(cpy.m_info)
{}

Error<error::tag::Trigger>::Error(Error<error::tag::Trigger>&& mov) :
    m_info(std::move(mov.m_info))
{}

Error<error::tag::Trigger>::~Error()
{}

typename Error<error::tag::Trigger>::OutputType& 
    Error<error::tag::Trigger>::Message(OutputType& out) const
{
    BASIC_ERROR_OUTPUT_OPERATOR(out, this->GetInformation());
    return out;
}

const typename Error<error::tag::Trigger>::InfoType& 
    Error<error::tag::Trigger>::GetInformation() const
{
    return m_info;
}

} //!basic

template<typename TChar, typename TCharTraits>
std::basic_ostream<TChar, TCharTraits>& operator<<(std::basic_ostream<TChar, 
    TCharTraits>& out, const basic::Error<basic::error::tag::Trigger>& err)
{
    out << "error : ";
    err.Message(out);
    return out;
}

#endif //!BASIC_ERROR_TAG_TRIGGER_H_

#endif //!BASIC_ERROR_H__FORWARD_DECLARATION_
