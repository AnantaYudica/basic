#ifndef BASIC_ERROR_IDENTIFICATION_STANDARD_H_
#define BASIC_ERROR_IDENTIFICATION_STANDARD_H_

#include "../Identification.h"
#include "Default.h"

#include <utility>

namespace basic
{
namespace error
{
namespace id
{

class Standard : public Identification
{
public:
    constexpr Standard();
    constexpr Standard(const Identification& id);
public:
    Standard(const Standard& cpy);
    Standard(Standard&& mov);
public:
    ~Standard();
public:
    Standard& operator=(const Standard&) = delete;
    Standard& operator=(Standard&&) = delete;
};

constexpr Standard::Standard() :
    Identification(Default())
{}

constexpr Standard::Standard(const Identification& id) :
    Identification(id.Flag.Default, 1, id.Flag.Catch, id.Error)
{}

Standard::Standard(const Standard& cpy) :
    Identification(cpy)
{}

Standard::Standard(Standard&& mov) :
    Identification(std::move(mov))
{}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_IDENTIFICATION_STANDARD_H_
