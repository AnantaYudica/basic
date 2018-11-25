#ifndef BASIC_ERROR_ID_CATCH_H_
#define BASIC_ERROR_ID_CATCH_H_

#include "../defn/type/code/Value.h"
#include "../defn/type/system/category/Value.h"
#include "../defn/type/system/code/Value.h"
#include "../Identification.h"
#include "../id/Flag.h"

#include <utility>

namespace basic
{
namespace error
{
namespace id
{

class Catch : public Identification
{
public:
    typedef defn::type::code::Value CodeValueType;
    typedef defn::type::system::category::Value SystemCategoryValueType;
    typedef defn::type::system::code::Value SystemCodeValueType;
public:
    constexpr Catch() noexcept;
    constexpr Catch(const CodeValueType& code_val) noexcept;
    constexpr Catch(const flag::Standard&, 
        const CodeValueType& code_val) noexcept;
    constexpr Catch(const flag::System&, 
        const SystemCategoryValueType& system_category_val,
        const SystemCodeValueType& system_code_val) noexcept;
    constexpr Catch(const flag::System&, const flag::Standard&, 
        const SystemCategoryValueType& system_category_val,
        const SystemCodeValueType& system_code_val) noexcept;
    constexpr Catch(const Identification& id) noexcept;
    constexpr Catch(const flag::Standard&, const Identification& id) noexcept;
public:
    Catch(const Catch& cpy) noexcept;
    Catch(Catch&& mov) noexcept;
public:
    Catch& operator=(const Catch&) = delete;
    Catch& operator=(Catch&&) = delete;
};

constexpr Catch::Catch() noexcept :
    Identification()
{}

constexpr Catch::Catch(const CodeValueType& code_val) noexcept :
    Identification(flag::Catch(), code_val)
{}

constexpr Catch::Catch(const flag::Standard& standard, 
    const CodeValueType& code_val) noexcept :
        Identification(flag::Catch(), standard, code_val)
{}

constexpr Catch::Catch(const flag::System& system, 
    const SystemCategoryValueType& system_category_val,
    const SystemCodeValueType& system_code_val) noexcept :
        Identification(flag::Catch(), system, system_category_val, 
            system_code_val)
{}

constexpr Catch::Catch(const flag::System& system, 
    const flag::Standard& standard, 
    const SystemCategoryValueType& system_category_val,
    const SystemCodeValueType& system_code_val) noexcept :
        Identification(flag::Catch(), system, standard,  
            system_category_val, system_code_val)
{}

constexpr Catch::Catch(const Identification& id) noexcept :
    Identification(flag::Catch(), id)
{}

constexpr Catch::Catch(const flag::Standard& standard, 
    const Identification& id) noexcept :
        Identification(flag::Catch(), standard, id)
{}

Catch::Catch(const Catch& cpy) noexcept :
    Identification(cpy)
{}

Catch::Catch(Catch&& mov) noexcept :
    Identification(std::move(mov))
{}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_CATCH_H_
