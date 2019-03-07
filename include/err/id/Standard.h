#ifndef BASIC_ERR_ID_STANDARD_H_
#define BASIC_ERR_ID_STANDARD_H_

#include "../Identification.h"
#include "../defn/type/code/Value.h"
#include "Flag.h"

#include <utility>

namespace basic
{
namespace err
{
namespace id
{

class Standard : public Identification
{
public:
    typedef defn::type::code::Value CodeValueType;
public:
    constexpr Standard() noexcept;
    constexpr Standard(const CodeValueType& code_val) noexcept;
public:
    constexpr Standard(const Standard& cpy) noexcept;
    inline Standard(Standard&& mov) noexcept;
public:
    Standard& operator=(const Standard&) = delete;
    Standard& operator=(Standard&&) = delete;
};

constexpr Standard::Standard() noexcept :
    Identification()
{}

constexpr Standard::Standard(const CodeValueType& code_val) noexcept :
    Identification(flag::Standard(), code_val)
{}

constexpr Standard::Standard(const Standard& cpy) noexcept :
    Identification(cpy)
{}

inline Standard::Standard(Standard&& mov) noexcept :
    Identification(std::move(mov))
{}

} //!id

} //!err

} //!basic

#endif //!BASIC_ERR_ID_STANDARD_H_
