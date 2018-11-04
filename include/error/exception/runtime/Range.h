#ifndef BASIC_ERROR_EXCEPTION_RUNTIME_RANGE_H_
#define BASIC_ERROR_EXCEPTION_RUNTIME_RANGE_H_

#include "../../Runtime.h"
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
namespace runtime
{

#ifdef USING_BASIC_ERROR_EXCEPTION
class Range : public exception::Runtime
{
public:
    typedef typename error::exception::Runtime::ErrorType ErrorType;
protected:
    Range();
public:
    Range(const char* file, const std::size_t& line);
public:
    Range(const Range& cpy);
    Range(Range&& mov);
public:
    ~Range();
public:
    Range& operator=(const Range&) = delete;
    Range& operator=(Range&&) = delete;
};

Range::Range()
{}

Range::Range(const char* file, const std::size_t& line) :
    ErrorType(constant::error::runtime_range_id, file, line)
{}

Range::Range(const Range& cpy) :
    exception::Runtime(cpy)
{}

Range::Range(Range&& mov) :
    exception::Runtime(std::move(mov))
{}

Range::~Range()
{}

#elif USING_STANDARD_EXCEPTION

typedef std::range_error Range;

#endif

} //!runtime

} //!exception

#ifndef USING_STANDARD_EXCEPTION

constexpr Identification id::Get(const exception::runtime::Range& e)
{
    return Identification(constant::error::runtime_range_id);
};

#endif

constexpr Identification id::Get(const std::range_error& e)
{
    return id::Standard(Identification(constant::error::runtime_range_id));
};

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_RUNTIME_RANGE_H_
