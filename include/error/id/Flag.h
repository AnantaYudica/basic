#ifndef BASIC_ERROR_ID_FLAG_H_
#define BASIC_ERROR_ID_FLAG_H_

#include <cstdint>
#include <utility>

namespace basic
{
namespace error
{
namespace id
{

namespace flag
{

struct Error {};
struct Standard {};
struct Catch {};
struct System {};

}

class Flag
{
private:
    std::uint8_t m_default : 1;
    std::uint8_t m_bad : 1;
    std::uint8_t m_standard : 1;
    std::uint8_t m_catch : 1;
    std::uint8_t m_system : 1;
private:
    static constexpr std::uint8_t IsBadFlag(const Flag& flag);
    static constexpr std::uint8_t IsBadFlag(const flag::Catch&, 
        const Flag& flag);
public:
    constexpr Flag() noexcept;
    constexpr Flag(const flag::Error&) noexcept;
    constexpr Flag(const flag::Error&, const flag::Standard&) noexcept;
    constexpr Flag(const flag::System&) noexcept;
    constexpr Flag(const flag::System&, const flag::Standard&) noexcept;
    constexpr Flag(const flag::Catch&) noexcept;
    constexpr Flag(const flag::Catch&, const flag::Standard&) noexcept;
    constexpr Flag(const flag::Catch&, const flag::System&) noexcept;
    constexpr Flag(const flag::Catch&, const flag::System&, 
        const flag::Standard&) noexcept;
    constexpr Flag(const flag::Catch&, const Flag& flag) noexcept;
    constexpr Flag(const flag::Catch&, const flag::Standard&, 
        const Flag& flag) noexcept;
public:
    constexpr Flag(const Flag& cpy) noexcept;
    inline Flag(Flag&& mov) noexcept;
public:
    Flag& operator=(const Flag& cpy) = delete;
    Flag& operator=(Flag&& mov) = delete;
public:
    inline Flag& operator=(const flag::Catch&) noexcept;
public:
    constexpr bool IsDefault() const noexcept;
    constexpr bool IsBad() const noexcept;
    constexpr bool IsStandard() const noexcept;
    constexpr bool IsCatch() const noexcept;
    constexpr bool IsSystem() const noexcept;
};

constexpr std::uint8_t Flag::IsBadFlag(const Flag& flag)
{
    return flag.IsBad() ? std::uint8_t(1) : 
        (flag.IsDefault() ? (flag.IsStandard() ||
            flag.IsCatch() || flag.IsSystem() ? std::uint8_t(1) : 
                std::uint8_t(0)) : std::uint8_t(0));
}

constexpr std::uint8_t Flag::IsBadFlag(const flag::Catch&, 
    const Flag& flag)
{
    return IsBadFlag(flag) == std::uint8_t(1) ? std::uint8_t(1) :
        flag.IsDefault() ? std::uint8_t(1) : std::uint8_t(0);
}

constexpr Flag::Flag() noexcept :
    m_default(std::uint8_t(1)),
    m_bad(std::uint8_t(0)),
    m_standard(std::uint8_t(0)),
    m_catch(std::uint8_t(0)),
    m_system(std::uint8_t(0))
{}

constexpr Flag::Flag(const flag::Error&) noexcept :
    m_default(std::uint8_t(0)),
    m_bad(std::uint8_t(0)),
    m_standard(std::uint8_t(0)),
    m_catch(std::uint8_t(0)),
    m_system(std::uint8_t(0))
{}

constexpr Flag::Flag(const flag::Error&, const flag::Standard&) noexcept :
    m_default(std::uint8_t(0)),
    m_bad(std::uint8_t(0)),
    m_standard(std::uint8_t(1)),
    m_catch(std::uint8_t(0)),
    m_system(std::uint8_t(0))
{}

constexpr Flag::Flag(const flag::System&) noexcept :
    m_default(std::uint8_t(0)),
    m_bad(std::uint8_t(0)),
    m_standard(std::uint8_t(0)),
    m_catch(std::uint8_t(0)),
    m_system(std::uint8_t(1))
{}

constexpr Flag::Flag(const flag::System&, const flag::Standard&) noexcept :
    m_default(std::uint8_t(0)),
    m_bad(std::uint8_t(0)),
    m_standard(std::uint8_t(1)),
    m_catch(std::uint8_t(0)),
    m_system(std::uint8_t(1))
{}

constexpr Flag::Flag(const flag::Catch&) noexcept :
    m_default(std::uint8_t(0)),
    m_bad(std::uint8_t(0)),
    m_standard(std::uint8_t(0)),
    m_catch(std::uint8_t(1)),
    m_system(std::uint8_t(0))
{}

constexpr Flag::Flag(const flag::Catch&, const flag::Standard&) noexcept :
    m_default(std::uint8_t(0)),
    m_bad(std::uint8_t(0)),
    m_standard(std::uint8_t(1)),
    m_catch(std::uint8_t(1)),
    m_system(std::uint8_t(0))
{}

constexpr Flag::Flag(const flag::Catch&, const flag::System&) noexcept :
    m_default(std::uint8_t(0)),
    m_bad(std::uint8_t(0)),
    m_standard(std::uint8_t(0)),
    m_catch(std::uint8_t(1)),
    m_system(std::uint8_t(1))
{}

constexpr Flag::Flag(const flag::Catch&, const flag::System&, 
    const flag::Standard&) noexcept  :
        m_default(std::uint8_t(0)),
        m_bad(std::uint8_t(0)),
        m_standard(std::uint8_t(1)),
        m_catch(std::uint8_t(1)),
        m_system(std::uint8_t(1))
{}

constexpr Flag::Flag(const flag::Catch& catch_, const Flag& flag) noexcept :
    m_default(flag.m_default),
    m_bad(IsBadFlag(catch_, flag)),
    m_standard(flag.m_standard),
    m_catch(std::uint8_t(1)),
    m_system(flag.m_system)
{}

constexpr Flag::Flag(const flag::Catch& catch_, const flag::Standard&,
    const Flag& flag) noexcept : 
        m_default(flag.m_default),
        m_bad(IsBadFlag(catch_, flag)),
        m_standard(std::uint8_t(1)),
        m_catch(std::uint8_t(1)),
        m_system(flag.m_system)
{}

constexpr Flag::Flag(const Flag& cpy) noexcept :
    m_default(cpy.m_default),
    m_bad(cpy.m_bad),
    m_standard(cpy.m_standard),
    m_catch(cpy.m_catch),
    m_system(cpy.m_system)
{}

inline Flag::Flag(Flag&& mov) noexcept :
    m_default(mov.m_default),
    m_bad(mov.m_bad),
    m_standard(mov.m_standard),
    m_catch(mov.m_catch),
    m_system(mov.m_system)
{
    mov.m_default = Flag{}.m_default;
    mov.m_bad = Flag{}.m_bad;
    mov.m_standard = Flag{}.m_standard;
    mov.m_catch = Flag{}.m_catch;
    mov.m_system = Flag{}.m_system;
}

inline Flag& Flag::operator=(const flag::Catch& catch_) noexcept
{
    this->m_bad = IsBadFlag(catch_, *this);
    this->m_catch = std::uint8_t(1);
    return *this;
}

constexpr bool Flag::IsDefault() const noexcept
{
    return m_default;
}

constexpr bool Flag::IsBad() const noexcept
{
    return m_bad;
}

constexpr bool Flag::IsStandard() const noexcept
{
    return m_standard;
}

constexpr bool Flag::IsCatch() const noexcept
{
    return m_catch;
}

constexpr bool Flag::IsSystem() const noexcept
{
    return m_system;
}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_FLAG_H_
