#ifndef BASIC_ERROR_EXCEPTION_H_
#define BASIC_ERROR_EXCEPTION_H_

#include "../Error.h"
#include "tag/Trigger.h"
#include "Identification.h"
#include "id/Get.h"
#include "id/Standard.h"
#include "../constant/error/Identification.h"

#include <exception>
#include <utility>

namespace basic
{
namespace error
{

#ifdef USING_BASIC_ERROR_EXCEPTION
class Exception : public virtual Error<tag::Trigger>
{
public:
    typedef Error<tag::Trigger> ErrorType;
protected:
    Exception();
public:
    Exception(const char* file, const std::size_t& line);
public:
    Exception(const Exception& cpy);
    Exception(Exception&& mov);
public:
    ~Exception();
public:
    Exception& operator=(const Exception&) = delete;
    Exception& operator=(Exception&&) = delete;
};

Exception::Exception()
{}

Exception::Exception(const char* file, const std::size_t& line) :
    ErrorType(constant::error::exception_id, file, line)
{}

Exception::Exception(const Exception& cpy) :
    ErrorType(cpy)
{}

Exception::Exception(Exception&& mov) :
    ErrorType(std::move(mov))
{}

Exception::~Exception()
{}

#elif USING_STANDARD_EXCEPTION

typedef std::exception Exception;

#endif

#ifndef USING_STANDARD_EXCEPTION

constexpr Identification id::Get(const Exception& e)
{
    return Identification(constant::error::exception_id);
};

#endif

constexpr Identification id::Get(const std::exception& e)
{
    return id::Standard(Identification(constant::error::exception_id));
};

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_H_
