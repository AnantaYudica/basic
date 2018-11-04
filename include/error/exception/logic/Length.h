#ifndef BASIC_ERROR_EXCEPTION_LOGIC_LENGTH_H_
#define BASIC_ERROR_EXCEPTION_LOGIC_LENGTH_H_

#include "../Logic.h"
#include "../../Identification.h"
#include "../../id/Get.h"
#include "../../id/Standard.h"
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

class Length : public exception::Logic
{
public:
    typedef typename exception::Logic::ErrorType ErrorType;
protected:
    Length();
public:
    Length(const char* file, const std::size_t& line);
public:
    Length(const Length& cpy);
    Length(Length&& mov);
public:
    ~Length();
public:
    Length& operator=(const Length&) = delete;
    Length& operator=(Length&&) = delete;
};

Length::Length()
{}

Length::Length(const char* file, const std::size_t& line) :
    ErrorType(constant::error::logic_length_id, file, line)
{}

Length::Length(const Length& cpy) :
    exception::Logic(cpy)
{}

Length::Length(Length&& mov) :
    exception::Logic(std::move(mov))
{}

Length::~Length()
{}

#elif USING_STANDARD_EXCEPTION

typedef std::length_error Length;

#endif

} //!logic

} //!exception

#ifndef USING_STANDARD_EXCEPTION

constexpr Identification id::Get(const exception::logic::Length& e)
{
    return Identification(constant::error::logic_length_id);
};

#endif

constexpr Identification id::Get(const std::length_error& e)
{
    return id::Standard(Identification(constant::error::logic_length_id));
};

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_LOGIC_LENGTH_H_
