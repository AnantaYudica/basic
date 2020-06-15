#ifndef BASIC_ERR_IDENTIFICATION_H_
#define BASIC_ERR_IDENTIFICATION_H_

#include "defn/type/code/Value.h"
#include "defn/type/sys/categ/Value.h"
#include "defn/type/sys/code/Value.h"
#include "defn/type/id/Record.h"
#include "id/Flag.h"
#include "id/rec/ToBytes.h"

#include <utility>
#include <ostream>
#include <iomanip>

namespace basic
{
namespace err
{

class Identification
{
public:
    typedef id::Flag FlagType;
public:
    typedef defn::type::code::Value CodeValueType;
    typedef defn::type::sys::categ::Value SystemCategoryValueType;
    typedef defn::type::sys::code::Value SystemCodeValueType;
public:
    typedef defn::type::id::Record RecordType;
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
        const SystemCategoryValueType& categ_val, 
        const SystemCodeValueType& code_val) noexcept;
    constexpr Identification(const id::flag::System&, 
        const id::flag::Standard&, const SystemCategoryValueType& categ_val,
        const SystemCodeValueType& code_val) noexcept;
    constexpr Identification(const id::flag::Catch&, 
        const CodeValueType& code_val) noexcept;
    constexpr Identification(const id::flag::Catch&, 
        const id::flag::Standard&, const CodeValueType& code_val) noexcept;
    constexpr Identification(const id::flag::Catch&, const id::flag::System&, 
        const SystemCategoryValueType& categ_val,
        const SystemCodeValueType& code_val) noexcept;
    constexpr Identification(const id::flag::Catch&, const id::flag::System&, 
        const id::flag::Standard&,
        const SystemCategoryValueType& categ_val,
        const SystemCodeValueType& code_val) noexcept;
    constexpr Identification(const id::flag::Catch&, 
        const Identification& id) noexcept;
    constexpr Identification(const id::flag::Catch&, 
        const id::flag::Standard&, const Identification& id) noexcept;
public:
    constexpr Identification(const Identification& cpy) noexcept;
    inline Identification(Identification&& mov) noexcept;
public:
    Identification & operator=(const Identification &) = delete;
    Identification & operator=(Identification &&) = delete;
public:
    constexpr bool IsDefault() const noexcept;
    constexpr bool IsBad() const noexcept;
    constexpr bool IsStandard() const noexcept;
    constexpr bool IsCatch() const noexcept;
    constexpr bool IsSystem() const noexcept;
public:
    constexpr const FlagType & Flag() const noexcept;
    constexpr ErrorType Error() const noexcept;
    constexpr ErrorSystemType ErrorSystem() const noexcept;
public:
    constexpr operator const defn::type::id::Record &() const noexcept;
};

constexpr Identification::Identification() noexcept :
    m_record(FlagType{})
{}

constexpr Identification::Identification(const CodeValueType& code_val) 
    noexcept :
        m_record(FlagType{id::flag::Error{}}, code_val)
{}

constexpr Identification::Identification(const id::flag::Standard& standard, 
    const CodeValueType& code_val) noexcept :
        m_record(FlagType{id::flag::Error{}, standard}, code_val)
{}

constexpr Identification::Identification(const id::flag::System& sys, 
    const SystemCategoryValueType& categ_val, 
    const SystemCodeValueType& code_val) noexcept :
        m_record(FlagType{sys}, categ_val, code_val)
{}

constexpr Identification::Identification(const id::flag::System& sys, 
    const id::flag::Standard& standard, 
    const SystemCategoryValueType& categ_val, 
    const SystemCodeValueType& code_val) noexcept :
        m_record(FlagType{sys, standard}, categ_val, code_val)
{}

constexpr Identification::Identification(const id::flag::Catch& catch_, 
    const id::flag::System& sys, 
    const SystemCategoryValueType& categ_val,
    const SystemCodeValueType& code_val) noexcept :
        m_record(FlagType{catch_, sys}, categ_val, code_val)
{}

constexpr Identification::Identification(const id::flag::Catch& catch_, 
    const id::flag::System& sys, const id::flag::Standard& standard,
    const SystemCategoryValueType& categ_val,
    const SystemCodeValueType& code_val) noexcept :
        m_record(FlagType{catch_, sys, standard}, categ_val, code_val)
{}

constexpr Identification::Identification(const id::flag::Catch& catch_, 
    const CodeValueType& code_val) noexcept :
        m_record(FlagType{catch_}, code_val)
{}

constexpr Identification::Identification(const id::flag::Catch& catch_, 
    const id::flag::Standard& standard, const CodeValueType& code_val) 
    noexcept :
        m_record(FlagType{catch_, standard}, code_val)
{}

constexpr Identification::Identification(const id::flag::Catch& catch_, 
    const Identification& id) noexcept :
        m_record(FlagType{catch_, id.m_record.Flag()}, id.m_record)
{}

constexpr Identification::Identification(const id::flag::Catch& catch_, 
    const id::flag::Standard& standard, const Identification& id) noexcept :
        m_record(FlagType{catch_, standard, id.m_record.Flag()}, id.m_record)
{}

constexpr Identification::Identification(const Identification& cpy) noexcept :
    m_record(cpy.m_record)
{}

inline Identification::Identification(Identification&& mov) noexcept :
    m_record(std::move(mov.m_record))
{}

constexpr bool Identification::IsDefault() const noexcept
{
    return m_record.Flag().IsDefault();
}

constexpr bool Identification::IsBad() const noexcept
{
    return m_record.Flag().IsBad();
}

constexpr bool Identification::IsStandard() const noexcept
{
    return m_record.Flag().IsStandard();
}

constexpr bool Identification::IsCatch() const noexcept
{
    return m_record.Flag().IsCatch();
}

constexpr bool Identification::IsSystem() const noexcept
{
    return m_record.Flag().IsSystem();
}

constexpr const typename Identification::FlagType &
Identification::Flag() const noexcept
{
    return m_record.Flag();
}

constexpr typename Identification::ErrorType
Identification::Error() const noexcept
{
    return m_record.Error();
}

constexpr typename Identification::ErrorSystemType
Identification::ErrorSystem() const noexcept
{
    return m_record.ErrorSystem();
}

constexpr Identification::operator 
    const defn::type::id::Record &() const noexcept
{
    return m_record;
}

} //!err

} //!basic

template<typename TChar, typename TCharTraits>
inline std::basic_ostream<TChar, TCharTraits> & 
operator<<(std::basic_ostream<TChar, TCharTraits> & out, 
    const basic::err::Identification & id)
{
    typedef typename basic::err::
        Identification::RecordType RecordType;
    const auto flags = out.flags();
    out << std::hex << std::uppercase;
    out << "0x";
    std::uint8_t bytes[RecordType::MaximumAllocation() + 1];
    std::size_t size = basic::err::id::rec::
        ToBytes(static_cast<const RecordType &>(id), bytes, sizeof(bytes));
    for (size_t i = 0; i < size; i++)
    {
        out << std::setfill('0') << std::setw(2);
        out << (int)bytes[i];
    }
    out.setf(flags);
    return out;
}

#endif //!BASIC_ERR_IDENTIFICATION_H_
