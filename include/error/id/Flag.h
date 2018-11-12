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
public:
    constexpr Flag();
    constexpr Flag(const flag::Standard&);
    constexpr Flag(const flag::Catch&);
    constexpr Flag(const flag::Catch&, const flag::Standard&);
    constexpr Flag(const flag::System&);
    constexpr Flag(const flag::System&, const flag::Standard&);
public:
    constexpr Flag(const Flag& cpy);
    constexpr Flag(Flag&& mov);
public:
    Flag& operator=(const Flag& cpy) = delete;
    Flag& operator=(Flag&& mov) = delete;
public:
    Flag& operator=(const flag::Catch&);
public:
    bool IsDefault() const;
    bool IsBad() const;
    bool IsStandard() const;
    bool IsCatch() const;
    bool IsSystem() const;
};

constexpr Flag::Flag() :
    m_default(1),
    m_bad(0),
    m_standard(0),
    m_catch(0),
    m_system(0)
{}

constexpr Flag::Flag(const flag::Standard&) :
    m_default(0),
    m_bad(0),
    m_standard(1),
    m_catch(0),
    m_system(0)
{}

constexpr Flag::Flag(const flag::Catch&) :
    m_default(0),
    m_bad(0),
    m_standard(0),
    m_catch(1),
    m_system(0)
{}

constexpr Flag::Flag(const flag::Catch&, const flag::Standard&) :
    m_default(0),
    m_bad(0),
    m_standard(1),
    m_catch(1),
    m_system(0)
{}

constexpr Flag::Flag(const flag::System&) :
    m_default(0),
    m_bad(0),
    m_standard(0),
    m_catch(0),
    m_system(1)
{}

constexpr Flag::Flag(const flag::System&, const flag::Standard&):
    m_default(0),
    m_bad(0),
    m_standard(1),
    m_catch(0),
    m_system(1)
{}

constexpr Flag::Flag(const Flag& cpy) :
    m_default(cpy.m_default),
    m_bad(cpy.m_bad),
    m_standard(cpy.m_standard),
    m_catch(cpy.m_catch),
    m_system(cpy.m_system)
{}

constexpr Flag::Flag(Flag&& mov) :
    m_default(mov.m_default),
    m_bad(mov.m_bad),
    m_standard(mov.m_standard),
    m_catch(mov.m_catch),
    m_system(mov.m_system)
{
    mov.m_default = 1;
    mov.m_bad = 0;
    mov.m_standard = 0;
    mov.m_catch = 0;
    mov.m_system = 0;
}

Flag& Flag::operator=(const flag::Catch&)
{
    if (IsDefault() || IsBad() || IsSystem())
        this->m_bad = 1; 
    else
        this->m_catch = 1;
    return *this;
}

bool Flag::IsDefault() const
{
    return m_default;
}

bool Flag::IsBad() const
{
    return m_bad;
}

bool Flag::IsStandard() const
{
    return m_standard;
}

bool Flag::IsCatch() const
{
    return m_catch;
}

bool Flag::IsSystem() const
{
    return m_system;
}

} //!id

} //!error

} //!basic

#endif //!BASIC_ERROR_ID_FLAG_H_
