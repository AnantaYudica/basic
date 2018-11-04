#ifndef BASIC_ERROR_EXCEPTION_LOGIC_FUTURE_H_
#define BASIC_ERROR_EXCEPTION_LOGIC_FUTURE_H_

#include "../Logic.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
#include "../../../constant/error/Identification.h"

#include <future>
#include <utility>

namespace basic
{
namespace error
{
namespace exception
{
namespace logic
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class Future : public exception::Logic
{
public:
    typedef typename exception::Logic::ErrorType ErrorType;
protected:
    Future();
public:
    Future(const char* file, const std::size_t& line);
public:
    Future(const Future& cpy);
    Future(Future&& mov);
public:
    ~Future();
public:
    Future& operator=(const Future&) = delete;
    Future& operator=(Future&&) = delete;
};

Future::Future()
{}

Future::Future(const char* file, const std::size_t& line) :
    ErrorType(constant::error::logic_future_id, file, line)
{}

Future::Future(const Future& cpy) :
    exception::Logic(cpy)
{}

Future::Future(Future&& mov) :
    exception::Logic(std::move(mov))
{}

Future::~Future()
{}

#elif USING_STANDARD_EXCEPTION

typedef std::future_error Future;

#endif

} //!logic

} //!exception

#ifndef USING_STANDARD_EXCEPTION

constexpr Identification id::Get(const exception::logic::Future& e)
{
    return Identification(constant::error::logic_future_id);
};

#endif

constexpr Identification id::Get(const std::future_error& e)
{
    return id::Standard(Identification(constant::error::logic_future_id));
};

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_LOGIC_FUTURE_H_
