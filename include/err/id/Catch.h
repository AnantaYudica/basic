#ifndef BASIC_ERR_ID_CATCH_H_
#define BASIC_ERR_ID_CATCH_H_

#include "../defn/type/code/Value.h"
#include "../defn/type/sys/categ/Value.h"
#include "../defn/type/sys/code/Value.h"
#include "../Identification.h"
#include "../id/Flag.h"

#include <utility>

namespace basic
{
namespace err
{
namespace id
{

class Catch : public Identification
{
public:
    typedef defn::type::code::Value CodeValueType;
    typedef defn::type::sys::categ::Value SystemCategoryValueType;
    typedef defn::type::sys::code::Value SystemCodeValueType;
public:
    constexpr Catch() noexcept;
    constexpr Catch(const CodeValueType& code_val) noexcept;
    constexpr Catch(const flag::Standard&, 
        const CodeValueType& code_val) noexcept;
    constexpr Catch(const flag::System&, 
        const SystemCategoryValueType& sys_categ_val,
        const SystemCodeValueType& sys_code_val) noexcept;
    constexpr Catch(const flag::System&, const flag::Standard&, 
        const SystemCategoryValueType& sys_categ_val,
        const SystemCodeValueType& sys_code_val) noexcept;
    constexpr Catch(const Identification& id) noexcept;
    constexpr Catch(const flag::Standard&, const Identification& id) noexcept;
public:
    constexpr Catch(const Catch& cpy) noexcept;
    inline Catch(Catch&& mov) noexcept;
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

constexpr Catch::Catch(const flag::System& sys, 
    const SystemCategoryValueType& sys_categ_val,
    const SystemCodeValueType& sys_code_val) noexcept :
        Identification(flag::Catch(), sys, sys_categ_val, 
            sys_code_val)
{}

constexpr Catch::Catch(const flag::System& sys, 
    const flag::Standard& standard, 
    const SystemCategoryValueType& sys_categ_val,
    const SystemCodeValueType& sys_code_val) noexcept :
        Identification(flag::Catch(), sys, standard,  
            sys_categ_val, sys_code_val)
{}

constexpr Catch::Catch(const Identification& id) noexcept :
    Identification(flag::Catch(), id)
{}

constexpr Catch::Catch(const flag::Standard& standard, 
    const Identification& id) noexcept :
        Identification(flag::Catch(), standard, id)
{}

constexpr Catch::Catch(const Catch& cpy) noexcept :
    Identification(cpy)
{}

inline Catch::Catch(Catch&& mov) noexcept :
    Identification(std::move(mov))
{}

} //!id

} //!err

} //!basic

#endif //!BASIC_ERR_ID_CATCH_H_
