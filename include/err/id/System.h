#ifndef BASIC_ERR_ID_SYSTEM_H_
#define BASIC_ERR_ID_SYSTEM_H_

#include "../Identification.h"
#include "../defn/type/sys/categ/Value.h"
#include "../defn/type/sys/code/Value.h"
#include "Flag.h"

#include <utility>

namespace basic
{
namespace err
{
namespace id
{

class System : public Identification
{
public:
    typedef defn::type::sys::categ::Value CategoryValueType;
    typedef defn::type::sys::code::Value CodeValueType;
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

} //!err

} //!basic

#endif //!BASIC_ERR_ID_SYSTEM_H_
