#ifndef BASIC_ERROR_H__FORWARD_DECLARATION_

#include "../../Error.h"

#else //else BASIC_ERROR_H__FORWARD_DECLARATION_

#ifndef BASIC_ERROR_TAG_TRIGGER_H_
#define BASIC_ERROR_TAG_TRIGGER_H_

#include "../Identification.h"

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
    typedef error::id::NumberType IdNumberType;
public:
    typedef OutputType&(MessageFunctionType)(OutputType&,
        const Error<error::tag::Trigger>&);
private:
    IdType m_id;
    const char* m_file;
    const std::size_t& m_line;
    MessageFunctionType* m_msgFuncPtr;
public:
    static OutputType& Message(OutputType& out, 
        const Error<error::tag::Trigger>& err);
public:
    Error();
public:
    Error(const Error<error::tag::Trigger>& cpy);
protected:
    Error(const IdType& id, const char* file, const std::size_t& line);
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
    const error::Identification& GetIdentification() const;
    const char* GetFile() const;
    const std::size_t& GetLine() const;
};

typename Error<error::tag::Trigger>::OutputType& 
    Error<error::tag::Trigger>::Message(OutputType& out, 
        const Error<error::tag::Trigger>& err)
{
    BASIC_ERROR_OUTPUT_OPERATOR(out, " code ");
    BASIC_ERROR_OUTPUT_OPERATOR(out, error::id::Number(err.m_id));
    BASIC_ERROR_OUTPUT_OPERATOR(out, " file ");
    BASIC_ERROR_OUTPUT_OPERATOR(out, err.m_file);
    BASIC_ERROR_OUTPUT_OPERATOR(out, " line ");
    BASIC_ERROR_OUTPUT_OPERATOR(out, err.m_line);
}

Error<error::tag::Trigger>::Error() :
    m_id(error::id::Default()),
    m_file(nullptr),
    m_line(-1),
    m_msgFuncPtr(&Message)
{}

Error<error::tag::Trigger>::Error(const IdType& id, const char* file, 
    const std::size_t& line) :
        m_id(id),
        m_file(file),
        m_line(line),
        m_msgFuncPtr(&Message)
{}

Error<error::tag::Trigger>::Error(const Error<error::tag::Trigger>& cpy) :
    m_id(cpy.m_id),
    m_file(cpy.m_file),
    m_line(cpy.m_line),
    m_msgFuncPtr(cpy.m_msgFuncPtr)
{}

Error<error::tag::Trigger>::~Error()
{}

typename Error<error::tag::Trigger>::OutputType& 
    Error<error::tag::Trigger>::Message(OutputType& out) const
{
    if (m_msgFuncPtr == NULL)
        Message(out, *this);
    else
        m_msgFuncPtr(out, *this);
    return out;
}

const typename Error<error::tag::Trigger>::IdType& 
    Error<error::tag::Trigger>::GetIdentification() const
{
    return m_id;
}

const char* Error<error::tag::Trigger>::GetFile() const
{
    return m_file;
}

const std::size_t& Error<error::tag::Trigger>::GetLine() const
{
    return m_line;
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
