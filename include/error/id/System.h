#ifndef BASIC_ERROR_ID_SYSTEM_H_
#define BASIC_ERROR_ID_SYSTEM_H_

#include "../Identification.h"
#include "../defn/type/system/categ/Value.h"
#include "../defn/type/system/code/Value.h"
#include "Flag.h"

#include <utility>

namespace basic
{
namespace error
{
namespace id
{

class System : public Identification
{
public:
    typedef defn::type::system::categ::Value CategoryValueType;
    typedef defn::type::system::code::Value CodeValueType;
public:
    constexpr System() noexcept;
    constexpr System(const CategoryValueType& categ_val,
        const CodeValueType& code_val) noexcept;
    constexpr System(const flag::Standard&, 
        const CategoryValueType& categ_val,
        const CodeValueType& code_val) noexcept;
public:
    constexpr System(const System& cpy) noexcept;
    inline System(System&& mov) noexcept;
public:
    System& operator=(const System&) = delete;
    System& operator=(System&&) = delete;
};

constexpr System::System() noexcept
{}

constexpr System::System(const CategoryValueType& categ_val,
    const CodeValueType& code_val) noexcept :
        Identification(flag::System(), categ_val, code_val)
{}

constexpr System::System(const flag::Standard& standard, 
    const CategoryValueType& categ_val, const 
    CodeValueType& code_val) noexcept :
        Identification(flag::System(), standard, categ_val, code_val)
{}

constexpr System::System(const System& cpy) noexcept :
    Identification(cpy)
{}

inline System::System(System&& mov) noexcept :
    Identification(std::move(mov))
{}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_SYSTEM_H_
