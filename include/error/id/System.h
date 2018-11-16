#ifndef BASIC_ERROR_ID_SYSTEM_H_
#define BASIC_ERROR_ID_SYSTEM_H_

#include "../Identification.h"
#include "../system/defn/type/category/Value.h"
#include "../system/defn/type/code/Value.h"
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
    typedef system::defn::type::category::Value CategoryValueType;
    typedef system::defn::type::code::Value CodeValueType;
public:
    constexpr System() noexcept;
    constexpr System(const CategoryValueType& category_val,
        const CodeValueType& code_val) noexcept;
    constexpr System(const flag::Standard&, 
        const CategoryValueType& category_val,
        const CodeValueType& code_val) noexcept;
public:
    System(const System& cpy) noexcept;
    System(System&& mov) noexcept;
public:
    System& operator=(const System&) = delete;
    System& operator=(System&&) = delete;
};

constexpr System::System() noexcept
{}

constexpr System::System(const CategoryValueType& category_val,
    const CodeValueType& code_val) noexcept :
        Identification(flag::System(), category_val, code_val)
{}

constexpr System::System(const flag::Standard& standard, 
    const CategoryValueType& category_val, const 
    CodeValueType& code_val) noexcept :
        Identification(flag::System(), standard, category_val, code_val)
{}

System::System(const System& cpy) noexcept :
    Identification(cpy)
{}

System::System(System&& mov) noexcept :
    Identification(std::move(mov))
{}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_SYSTEM_H_
