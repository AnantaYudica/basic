#ifndef BASIC_ERROR_EXCEPTION_LOGIC_INVALID_ARGUMENT_H_
#define BASIC_ERROR_EXCEPTION_LOGIC_INVALID_ARGUMENT_H_

#include "../Invalid.h"
#include "../../../Identification.h"
#include "../../../id/Get.h"
#include "../../../id/Standard.h"
#include "../../../../constant/error/Identification.h"

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
namespace invalid
{

#ifdef USING_BASIC_ERROR_EXCEPTION

class Argument : public logic::Invalid
{
public:
    typedef typename logic::Invalid::ErrorType ErrorType;
protected:
    Argument();
public:
    Argument(const char* file, const std::size_t& line);
public:
    Argument(const Argument& cpy);
    Argument(Argument&& mov);
public:
    ~Argument();
public:
    Argument& operator=(const Argument&) = delete;
    Argument& operator=(Argument&&) = delete;  
};

Argument::Argument()
{}

Argument::Argument(const char* file, const std::size_t& line) :
    ErrorType(constant::error::logic_invalid_argument_id, file, line)
{}

Argument::Argument(const Argument& cpy) :
    logic::Invalid(cpy)
{}

Argument::Argument(Argument&& mov) :
    logic::Invalid(std::move(mov))
{}

Argument::~Argument()
{}

#elif USING_STANDARD_EXCEPTION

typedef std::invalid_argument Invalid;

#endif

} //!invalid

} //!logic

} //!exception

#ifndef USING_STANDARD_EXCEPTION

constexpr Identification id::Get(const exception::logic::invalid::Argument& e)
{
    return Identification(constant::error::logic_invalid_argument_id);
};

#endif

constexpr Identification id::Get(const std::logic_error& e)
{
    return id::Standard(Identification(constant::error::
        logic_invalid_argument_id));
};

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_LOGIC_INVALID_ARGUMENT_H_
