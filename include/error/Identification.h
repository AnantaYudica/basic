#ifndef BASIC_ERROR_IDENTIFICATION_H_
#define BASIC_ERROR_IDENTIFICATION_H_

#include "../system/defn/type/category/Value.h"
#include "../system/defn/type/code/Value.h"
#include "id/defn/type/Record.h"
#include "id/Flag.h"
#include "id/Size.h"
#include "id/ToBytes.h"

#include <utility>
#include <ostream>
#include <iomanip>

namespace basic
{
namespace error
{

class Identification : public id::Flag
{
public:
    typedef id::Flag FlagType;
public:
    typedef error::code::defn::type::Value CodeValueType;
    typedef error::system::defn::type::category::Value SystemCategoryValueType;
    typedef error::system::defn::type::code::Value SystemCodeValueType;
public:
    typedef id::defn::type::Record RecordType;
    typedef typename RecordType::ErrorType ErrorType;
    typedef typename RecordType::ErrorSystemType ErrorSystemType;
private:
    RecordType m_record;
public:
    constexpr Identification() noexcept;
    constexpr Identification(const CodeValueType& code_val) noexcept;
    constexpr Identification(const id::flag::Standard&, 
        const CodeValueType& code_val) noexcept;
    constexpr Identification(const id::flag::System&, 
        const SystemCategoryValueType& category_val, 
        const SystemCodeValueType& code_val) noexcept;
    constexpr Identification(const id::flag::System&, 
        const id::flag::Standard&, const SystemCategoryValueType& category_val,
        const SystemCodeValueType& code_val) noexcept;
    constexpr Identification(const id::flag::Catch&, 
        const CodeValueType& code_val) noexcept;
    constexpr Identification(const id::flag::Catch&, 
        const id::flag::Standard&, const CodeValueType& code_val) noexcept;
    constexpr Identification(const id::flag::Catch&, const id::flag::System&, 
        const SystemCategoryValueType& category_val,
        const SystemCodeValueType& code_val) noexcept;
    constexpr Identification(const id::flag::Catch&, const id::flag::System&, 
        const id::flag::Standard&,
        const SystemCategoryValueType& category_val,
        const SystemCodeValueType& code_val) noexcept;
    constexpr Identification(const id::flag::Catch&, 
        const Identification& id) noexcept;
    constexpr Identification(const id::flag::Catch&, 
        const id::flag::Standard&, const Identification& id) noexcept;
public:
    Identification(const Identification& cpy) noexcept;
    Identification(Identification&& mov) noexcept;
public:
    ErrorType Error() const noexcept;
    ErrorSystemType ErrorSystem() const noexcept;
};

constexpr Identification::Identification() noexcept :
    id::Flag(),
    m_record()
{}

constexpr Identification::Identification(const CodeValueType& code_val) 
    noexcept :
        id::Flag(id::flag::Error()),
        m_record(code_val)
{}

constexpr Identification::Identification(const id::flag::Standard& standard, 
    const CodeValueType& code_val) noexcept :
        id::Flag(id::flag::Error(), standard),
        m_record(code_val)
{}

constexpr Identification::Identification(const id::flag::System& system, 
    const SystemCategoryValueType& category_val, 
    const SystemCodeValueType& code_val) noexcept :
        id::Flag(system),
        m_record(system, category_val, code_val)
{}

constexpr Identification::Identification(const id::flag::System& system, 
    const id::flag::Standard& standard, 
    const SystemCategoryValueType& category_val, 
    const SystemCodeValueType& code_val) noexcept :
        id::Flag(system, standard),
        m_record(system, category_val, code_val)
{}

constexpr Identification::Identification(const id::flag::Catch& catch_, 
    const id::flag::System& system, 
    const SystemCategoryValueType& category_val,
    const SystemCodeValueType& code_val) noexcept :
        id::Flag(catch_, system),
        m_record(system, category_val, code_val)
{}

constexpr Identification::Identification(const id::flag::Catch& catch_, 
    const id::flag::System& system, const id::flag::Standard& standard,
    const SystemCategoryValueType& category_val,
    const SystemCodeValueType& code_val) noexcept :
        id::Flag(catch_, system, standard),
        m_record(system, category_val, code_val)
{}

constexpr Identification::Identification(const id::flag::Catch& catch_, 
    const CodeValueType& code_val) noexcept :
        id::Flag(catch_),
        m_record(code_val)
{}

constexpr Identification::Identification(const id::flag::Catch& catch_, 
    const id::flag::Standard& standard, const CodeValueType& code_val) 
    noexcept :
        id::Flag(catch_, standard),
        m_record(code_val)
{}

constexpr Identification::Identification(const id::flag::Catch& catch_, 
    const Identification& id) noexcept :
        id::Flag(catch_, id),
        m_record(id.m_record)
{}

constexpr Identification::Identification(const id::flag::Catch& catch_, 
    const id::flag::Standard& standard, const Identification& id) noexcept :
        id::Flag(catch_, standard, id),
        m_record(id.m_record)
{}

Identification::Identification(const Identification& cpy) noexcept :
    id::Flag(cpy),
    m_record(cpy.m_record)
{}

Identification::Identification(Identification&& mov) noexcept :
    id::Flag(std::move(mov)),
    m_record(std::move(mov.m_record))
{}

typename Identification::ErrorType 
Identification::Error() const noexcept
{
    return std::move(m_record.Error());
}

typename Identification::ErrorSystemType 
Identification::ErrorSystem() const noexcept
{
    return std::move(m_record.ErrorSystem());
}

} //!error

} //!basic

template<typename TChar, typename TCharTraits>
std::basic_ostream<TChar, TCharTraits>& operator<<(std::basic_ostream<TChar, 
    TCharTraits>& out, const basic::error::Identification& id)
{
    const auto flags = out.flags();
    out << std::hex << std::uppercase;
    out << "0x";
    std::uint8_t bytes[id::Size<basic::error::Identification>()];
    id::ToBytes(id, bytes);
    for (size_t i = 0; i < id::Size<basic::error::Identification>(); i++)
    {
        out << std::setfill('0') << std::setw(2);
        out << (int)bytes[i];
    }
    out.setf(flags);
}

#endif //!BASIC_ERROR_IDENTIFICATION_H_
