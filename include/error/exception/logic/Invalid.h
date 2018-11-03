#ifndef BASIC_ERROR_EXCEPTION_LOGIC_INVALID_H_
#define BASIC_ERROR_EXCEPTION_LOGIC_INVALID_H_

#include "../Logic.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../../constant/error/Identification.h"

#include <stdexcept>
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

class Invalid : public exception::Logic
{
public:
    typedef typename exception::Logic::ErrorType ErrorType;
protected:
    Invalid();
public:
    Invalid(const char* file, const std::size_t& line);
public:
    Invalid(const Invalid& cpy);
    Invalid(Invalid&& mov);
public:
    ~Invalid();
public:
    Invalid& operator=(const Invalid&) = delete;
    Invalid& operator=(Invalid&&) = delete;
};

Invalid::Invalid()
{}

Invalid::Invalid(const char* file, const std::size_t& line) :
    ErrorType(constant::error::logic_invalid_id, file, line)
{}

Invalid::Invalid(const Invalid& cpy) :
    exception::Logic(cpy)
{}

Invalid::Invalid(Invalid&& mov) :
    exception::Logic(std::move(mov))
{}

Invalid::~Invalid()
{}

#elif USING_STANDARD_EXCEPTION

typedef std::logic_error Invalid;

#endif

} //!logic

} //!exception

#ifndef USING_STANDARD_EXCEPTION

constexpr Identification id::Get(const exception::logic::Invalid& e)
{
    return Identification(constant::error::logic_invalid_id);
};

#endif

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_LOGIC_INVALID_H_
