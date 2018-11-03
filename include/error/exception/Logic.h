#ifndef BASIC_ERROR_EXCEPTION_LOGIC_H_
#define BASIC_ERROR_EXCEPTION_LOGIC_H_

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
class Logic : public error::Exception
{
public:
    typedef typename error::Exception::ErrorType ErrorType;
protected:
    Logic();
public:
    Logic(const char* file, const std::size_t& line);
public:
    Logic(const Logic& cpy);
    Logic(Logic&& mov);
public:
    ~Logic();
public:
    Logic& operator=(const Logic&) = delete;
    Logic& operator=(Logic&&) = delete;
};

Logic::Logic()
{}

Logic::Logic(const char* file, const std::size_t& line) :
    ErrorType(constant::error::logic_id, file, line)
{}

Logic::Logic(const Logic& cpy) :
    error::Exception(cpy)
{}

Logic::Logic(Logic&& mov) :
    error::Exception(std::move(mov))
{}

Logic::~Logic()
{}

#elif USING_STANDARD_EXCEPTION

typedef std::logic_error Logic;

#endif

} //!exception

#ifndef USING_STANDARD_EXCEPTION

constexpr Identification id::Get(const exception::Logic& e)
{
    return Identification(constant::error::logic_id);
};

#endif

constexpr Identification id::Get(const std::logic_error& e)
{
    return id::Standard(Identification(constant::error::logic_id));
};

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_LOGIC_H_
