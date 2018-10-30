#ifndef BASIC_ERROR_H__FORWARD_DECLARATION_

#include "../../Error.h"

#else //else BASIC_ERROR_H__FORWARD_DECLARATION_

#ifndef BASIC_ERROR_TAG_CATCH_H_
#define BASIC_ERROR_TAG_CATCH_H_

#include "Trigger.h"
#include "../Identification.h"

#include <ostream>
#include <exception>

namespace basic
{
namespace error
{
namespace tag
{

struct Catch {};

} //!tag

} //!error

template<>
class Error<error::tag::Catch> : public Error<error::tag::Trigger>
{
public:
    typedef Error<error::tag::Trigger> BaseType;
public:
    typedef BASIC_ERROR_CHAR_TYPE CharType;
    typedef BASIC_ERROR_CHARTRAIT_TYPE CharTraitType;
    typedef BASIC_ERROR_OUTPUT_TYPE OutputType;
public:
    typedef error::Identification IdType;
    typedef error::id::NumberType IdNumberType;
public:
    Error();
    Error(const Error<error::tag::Catch>& err,
        const char* file, const int& line);
    Error(const Error<error::tag::Trigger>& err, 
        const char* file, const int& line);
    Error(const std::exception& err, 
        const char* file, const int& line);
public:
    ~Error();
public:
    Error<error::tag::Catch>& 
        operator=(const Error<error::tag::Catch>&) = delete;
    Error<error::tag::Catch>& 
        operator=(Error<error::tag::Catch>&&) = delete;
public:
    OutputType& Message(OutputType& out) const;
};

Error<error::tag::Catch>::Error() :
    BaseType()
{}

Error<error::tag::Catch>::Error(const Error<error::tag::Trigger>& err,
    const char* file, const int& line) :
        BaseType(err.GetIdentification(), file, line)
{
    BASIC_ERROR_OUTPUT_OPERATOR(BASIC_ERROR_OUTPUT, err);
}

Error<error::tag::Catch>::Error(const Error<error::tag::Catch>& err, 
    const char* file, const int& line) :
        BaseType(err.GetIdentification(), file, line)
{
    BASIC_ERROR_OUTPUT_OPERATOR(BASIC_ERROR_OUTPUT, err);
}

Error<error::tag::Catch>::Error(const std::exception& err, 
    const char* file, const int& line) :
        BaseType(error::id::Get(err), file, line)
{
    BASIC_ERROR_OUTPUT_OPERATOR(BASIC_ERROR_OUTPUT, "error : ");
    BASIC_ERROR_OUTPUT_OPERATOR(BASIC_ERROR_OUTPUT, err.what());
}

Error<error::tag::Catch>::~Error()
{}

typename Error<error::tag::Catch>::OutputType& 
    Error<error::tag::Catch>::Message(OutputType& out) const
{
    BASIC_ERROR_OUTPUT_OPERATOR(BASIC_ERROR_OUTPUT, "\nin catch file ");
    BASIC_ERROR_OUTPUT_OPERATOR(BASIC_ERROR_OUTPUT, this->GetFile());
    BASIC_ERROR_OUTPUT_OPERATOR(BASIC_ERROR_OUTPUT, " line ");
    BASIC_ERROR_OUTPUT_OPERATOR(BASIC_ERROR_OUTPUT, this->GetLine());
}

} //!basic

template<typename TChar, typename TCharTraits>
std::basic_ostream<TChar, TCharTraits>& operator<<(std::basic_ostream<TChar, 
    TCharTraits>& out, const basic::Error<basic::error::tag::Catch>& err)
{
    out << err.Message;
    return out;
}

#endif //!BASIC_ERROR_TAG_CATCH_H_

#endif //!BASIC_ERROR_H__FORWARD_DECLARATION_
