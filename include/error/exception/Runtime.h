#ifndef BASIC_ERROR_EXCEPTION_RUNTIME_H_
#define BASIC_ERROR_EXCEPTION_RUNTIME_H_

#include "../Exception.h"
#include "../Identification.h"
#include "../id/Get.h"
#include "../id/Standard.h"
#include "../../constant/error/Identification.h"

#include <stdexcept>
#include <utility>

namespace basic
{
namespace error
{
namespace exception
{

#ifdef USING_BASIC_ERROR_EXCEPTION
class Runtime : public error::Exception
{
public:
    typedef typename error::Exception::ErrorType ErrorType;
protected:
    Runtime();
public:
    Runtime(const char* file, const std::size_t& line);
public:
    Runtime(const Runtime& cpy);
    Runtime(Runtime&& mov);
public:
    ~Runtime();
public:
    Runtime& operator=(const Runtime&) = delete;
    Runtime& operator=(Runtime&&) = delete;
};

Runtime::Runtime()
{}

Runtime::Runtime(const char* file, const std::size_t& line) :
    ErrorType(constant::error::runtime_id, file, line)
{}

Runtime::Runtime(const Runtime& cpy) :
    error::Exception(cpy)
{}

Runtime::Runtime(Runtime&& mov) :
    error::Exception(std::move(mov))
{}

Runtime::~Runtime()
{}

#elif USING_STANDARD_EXCEPTION

typedef std::runtime_error Runtime;

#endif

} //!exception

#ifndef USING_STANDARD_EXCEPTION

constexpr Identification id::Get(const exception::Runtime& e)
{
    return Identification(constant::error::runtime_id);
};

#endif

constexpr Identification id::Get(const std::runtime_error& e)
{
    return id::Standard(Identification(constant::error::runtime_id));
};

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_RUNTIME_H_
