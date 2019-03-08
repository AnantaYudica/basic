#ifndef BASIC_ERR_MSG_STRING_H_
#define BASIC_ERR_MSG_STRING_H_

#include "../defn/type/Char.h"
#include "../defn/type/msg/str/Storage.h"
#include "../intf/Exit.h"
#include "str/Default.h"
#include "str/Allocate.h"
#include "str/Copy.h"
#include "str/Move.h"
#include "str/Value.h"
#include "str/Capacity.h"

#include <cstddef>

namespace basic
{
namespace err
{
namespace msg
{

class String :
    public err::intf::Exit
{
public:
    typedef defn::type::Char CharType;
    typedef defn::type::msg::str::Storage StorageType;
private:
    StorageType m_storage;
public:
    constexpr String() noexcept;
    template<std::size_t N>
    inline String(const CharType (& cstr)[N]) noexcept;
    inline String(const CharType * cstr) noexcept;
    template<typename TString>
    inline String(const TString & str) noexcept;
public:
    inline String(const String & cpy) noexcept;
    inline String(String && mov) noexcept;
public:
    inline ~String() noexcept;
public:
    inline String & operator=(const String & cpy) noexcept;
    inline String & operator=(String && mov) noexcept;
public:
    inline const CharType * Value() const noexcept;
public:
    inline operator bool() const noexcept;
private:
    inline void Cleanup(int sig) noexcept;
};

constexpr String::String() noexcept :
    m_storage{0}
{}

template<std::size_t N>
inline String::String(const CharType (& cstr)[N]) noexcept :
    m_storage{0}
{
    msg::str::Default(m_storage);
    msg::str::Allocate(m_storage, N);
    msg::str::Copy(m_storage, N, cstr);
}

inline String::String(const CharType * cstr) noexcept :
    m_storage{0}
{
    msg::str::Default(m_storage);
    const std::size_t size = msg::str::Capacity(cstr);
    if (size > 0)
    {
        msg::str::Allocate(m_storage, size);
        msg::str::Copy(m_storage, size, cstr);
    }
}

template<typename TString>
inline String::String(const TString & str) noexcept :
    m_storage{0}
{
    msg::str::Default(m_storage);
    const std::size_t size = msg::str::Capacity(str);
    if (size > 0)
    {
        msg::str::Allocate(m_storage, size);
        msg::str::Copy(m_storage, size, str);
    }
}

inline String::String(const String & cpy) noexcept :
    m_storage{0}
{
    msg::str::Default(m_storage);
    const std::size_t size = msg::str::Capacity(cpy.m_storage);
    if (size > 0)
    {
        msg::str::Allocate(m_storage, size);
        msg::str::Copy(m_storage, size, cpy.m_storage);
    }

}

inline String::String(String && mov) noexcept :
    m_storage{0}
{
    msg::str::Default(m_storage);
    msg::str::Move(m_storage, std::move(mov.m_storage));
}

inline String::~String() noexcept
{
    msg::str::Deallocate(m_storage);
}

inline String & String::operator=(const String & cpy) noexcept
{
    msg::str::Deallocate(m_storage);
    const std::size_t size = msg::str::Capacity(cpy.m_storage);
    if (size > 0)
    {
        msg::str::Allocate(m_storage, size);
        msg::str::Copy(m_storage, size, cpy.m_storage);
    }
    return *this;
}

inline String & String::operator=(String && mov) noexcept
{
    msg::str::Deallocate(m_storage);
    msg::str::Move(m_storage, std::move(mov.m_storage));
    return *this;
}

inline const typename String::CharType * String::Value() const noexcept
{
    return msg::str::Value(m_storage);
}

inline String::operator bool() const noexcept
{
    return !msg::str::IsDefault(m_storage);
}

inline void String::Cleanup(int sig) noexcept
{
    msg::str::Deallocate(m_storage);
}

} //!msg

} //!err

} //!basic

#endif //!BASIC_ERR_MSG_STRING_H_
