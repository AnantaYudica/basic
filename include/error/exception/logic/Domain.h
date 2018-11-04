#ifndef BASIC_ERROR_EXCEPTION_LOGIC_DOMAIN_H_
#define BASIC_ERROR_EXCEPTION_LOGIC_DOMAIN_H_

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

class Domain : public exception::Logic
{
public:
    typedef typename exception::Logic::ErrorType ErrorType;
protected:
    Domain();
public:
    Domain(const char* file, const std::size_t& line);
public:
    Domain(const Domain& cpy);
    Domain(Domain&& mov);
public:
    ~Domain();
public:
    Domain& operator=(const Domain&) = delete;
    Domain& operator=(Domain&&) = delete;
};

Domain::Domain()
{}

Domain::Domain(const char* file, const std::size_t& line) :
    ErrorType(constant::error::logic_domain_id, file, line)
{}

Domain::Domain(const Domain& cpy) :
    exception::Logic(cpy)
{}

Domain::Domain(Domain&& mov) :
    exception::Logic(std::move(mov))
{}

Domain::~Domain()
{}

#elif USING_STANDARD_EXCEPTION

typedef std::domain_error Domain;

#endif

} //!logic

} //!exception

#ifndef USING_STANDARD_EXCEPTION

constexpr Identification id::Get(const exception::logic::Domain& e)
{
    return Identification(constant::error::logic_domain_id);
};

#endif

constexpr Identification id::Get(const std::domain_error& e)
{
    return id::Standard(Identification(constant::error::logic_domain_id));
};

} //!error

} //!basic

#endif //!BASIC_ERROR_EXCEPTION_LOGIC_DOMAIN_H_
