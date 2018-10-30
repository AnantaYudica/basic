#ifndef BASIC_ERROR_H__FORWARD_DECLARATION_

#include "../../Error.h"

#else //else BASIC_ERROR_H__FORWARD_DECLARATION_

#ifndef BASIC_ERROR_TAG_OUTPUT_H_
#define BASIC_ERROR_TAG_OUTPUT_H_

#include "Trigger.h"
#include "../Identification.h"

#include <exception>

namespace basic
{
namespace error
{
namespace tag
{

struct Output {};

} //!tag

} //!error

template<>
class Error<error::tag::Output>
{
public:
    Error();
    Error(const Error<error::tag::Trigger>& err, 
        const char* file, const int& line);
    Error(const std::exception& err, 
        const char* file, const int& line);
};

Error<error::tag::Output>::Error()
{}

Error<error::tag::Output>::Error(const Error<error::tag::Trigger>& err, 
    const char* file, const int& line)
{
    BASIC_ERROR_OUTPUT_OPERATOR(BASIC_ERROR_OUTPUT, err);
    BASIC_ERROR_OUTPUT_OPERATOR(BASIC_ERROR_OUTPUT, "\nin catch ");
    BASIC_ERROR_OUTPUT_OPERATOR(BASIC_ERROR_OUTPUT, " file ");
    BASIC_ERROR_OUTPUT_OPERATOR(BASIC_ERROR_OUTPUT, file);
    BASIC_ERROR_OUTPUT_OPERATOR(BASIC_ERROR_OUTPUT, " line ");
    BASIC_ERROR_OUTPUT_OPERATOR(BASIC_ERROR_OUTPUT, line);
}

Error<error::tag::Output>::Error(const std::exception& err, 
    const char* file, const int& line)
{
    BASIC_ERROR_OUTPUT_OPERATOR(BASIC_ERROR_OUTPUT, err.what());
    BASIC_ERROR_OUTPUT_OPERATOR(BASIC_ERROR_OUTPUT, "\nin catch ");
    BASIC_ERROR_OUTPUT_OPERATOR(BASIC_ERROR_OUTPUT, " file ");
    BASIC_ERROR_OUTPUT_OPERATOR(BASIC_ERROR_OUTPUT, file);
    BASIC_ERROR_OUTPUT_OPERATOR(BASIC_ERROR_OUTPUT, " line ");
    BASIC_ERROR_OUTPUT_OPERATOR(BASIC_ERROR_OUTPUT, line);
}

} //!basic

#endif //!BASIC_ERROR_TAG_OUTPUT_H_

#endif //!BASIC_ERROR_H__FORWARD_DECLARATION_
