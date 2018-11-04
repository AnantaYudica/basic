#ifndef BASIC_ERROR_EXCEPTION_LOGIC_OUTOFRANGE_H_
#define BASIC_ERROR_EXCEPTION_LOGIC_OUTOFRANGE_H_

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

class OutOfRange : public exception::Logic
{
public:
    typedef typename exception::Logic::ErrorType ErrorType;
protected:
    OutOfRange();
public:
    OutOfRange(const char* file, const std::size_t& line);
public:
    OutOfRange(const OutOfRange& cpy);
    OutOfRange(OutOfRange&& mov);
public:
    ~OutOfRange();
public:
    OutOfRange& operator=(const OutOfRange&) = delete;
    OutOfRange& operator=(OutOfRange&&) = delete;
};

OutOfRange::OutOfRange()
{}

OutOfRange::OutOfRange(const char* file, const std::size_t& line) :
    ErrorType(constant::error::logic_outofrange_id, file, line)
{}

OutOfRange::OutOfRange(const OutOfRange& cpy) :
    exception::Logic(cpy)
{}

OutOfRange::OutOfRange(OutOfRange&& mov) :
    exception::Logic(std::move(mov))
{}

OutOfRange::~OutOfRange()
{}

#elif USING_STANDARD_EXCEPTION

typedef std::out_of_range OutOfRange;

#endif

} //!logic

} //!exception

#ifndef USING_STANDARD_EXCEPTION

constexpr Identification id::Get(const exception::logic::OutOfRange& e)
{
    return Identification(constant::error::logic_outofrange_id);
};

#endif

constexpr Identification id::Get(const std::out_of_range& e)
{
    return id::Standard(Identification(constant::error::logic_outofrange_id));
};

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_LOGIC_OUTOFRANGE_H_
