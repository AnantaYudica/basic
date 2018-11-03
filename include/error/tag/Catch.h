#ifndef BASIC_ERROR_H__FORWARD_DECLARATION_

#include "../../Error.h"

#else //else BASIC_ERROR_H__FORWARD_DECLARATION_

#ifndef BASIC_ERROR_TAG_CATCH_H_
#define BASIC_ERROR_TAG_CATCH_H_

#include "Trigger.h"
#include "Standard.h"
#include "../Identification.h"
#include "../id/Catch.h"
#include "../Information.h"

#include <ostream>
#include <exception>

namespace basic
{
namespace error
{
namespace tag
{

template<typename TError = Error<error::tag::Trigger>>
struct Catch {};

} //!tag

} //!error

template<typename TError>
class Error<error::tag::Catch<TError>> : 
    public Error<error::tag::Trigger>
{
public:
    typedef Error<error::tag::Trigger> BaseType;
public:
    typedef BASIC_ERROR_CHAR_TYPE CharType;
    typedef BASIC_ERROR_CHARTRAIT_TYPE CharTraitType;
    typedef BASIC_ERROR_OUTPUT_TYPE OutputType;
private:
    TError m_error;
public:
    Error();
    Error(const TError& err, const char* file, 
        const std::size_t& line);
public:
    Error(const Error<error::tag::Catch<TError>>& cpy);
    Error(Error<error::tag::Catch<TError>>&& mov);
public:
    ~Error();
public:
    Error<error::tag::Catch>& 
        operator=(const Error<error::tag::Catch>&) = delete;
    Error<error::tag::Catch>& 
        operator=(Error<error::tag::Catch>&&) = delete;
public:
    const TError& GetError() const;
};

template<typename TError>
Error<error::tag::Catch<TError>>::Error() :
    BaseType(),
    m_trigger()
{}

template<typename TError>
Error<error::tag::Catch<TError>>::Error(const TError& err,
    const char* file, const std::size_t& line) :
        m_trigger(err),
        BaseType(error::id::Catch(error::id::Get(err)), file, line),
{}

template<typename TError>
Error<error::tag::Catch<TError>>::~Error()
{}

template<typename TError>
const TError& Error<error::tag::Catch<TError>>::GetError() const
{
    return m_trigger;
}

} //!basic

#endif //!BASIC_ERROR_TAG_CATCH_H_

#endif //!BASIC_ERROR_H__FORWARD_DECLARATION_
