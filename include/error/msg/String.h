#ifndef BASIC_ERROR_MSG_STRING_H_
#define BASIC_ERROR_MSG_STRING_H_

#include "../defn/type/Char.h"
#include "../defn/type/msg/str/Storage.h"
#include "str/Default.h"
#include "str/Allocate.h"
#include "str/Size.h"
#include "str/Copy.h"
#include "str/Move.h"
#include "str/Value.h"

#include <cstddef>

namespace basic
{
namespace error
{
namespace msg
{

class String
{
public:
    typedef defn::type::Char CharType;
    typedef defn::type::msg::str::Storage StorageType;
private:
    StorageType m_storage;
public:
    constexpr String() noexcept;
    template<std::size_t N>
    String(const CharType (&cstr)[N]) noexcept;
    String(const CharType *cstr) noexcept;
    template<typename TString>
    String(const TString &str) noexcept;
public:
    String(const String &cpy) noexcept;
    String(String &&mov) noexcept;
public:
    ~String() noexcept;
public:
    String & operator=(const String &cpy) noexcept;
    String & operator=(String &&mov) noexcept;
public:
    const CharType *Value() const noexcept;
public:
    operator bool() const noexcept;
};

constexpr String::String() noexcept :
    m_storage{0}
{}

template<std::size_t N>
String::String(const CharType (&cstr)[N]) noexcept :
    m_storage{0}
{
    msg::str::Default(m_storage);
    msg::str::Allocate(m_storage, N);
    msg::str::Copy(m_storage, N, cstr);
}

String::String(const CharType *cstr) noexcept :
    m_storage{0}
{
    msg::str::Default(m_storage);
    const std::size_t size = msg::str::Size(cstr);
    msg::str::Allocate(m_storage, size);
    msg::str::Copy(m_storage, size, cstr);
}

template<typename TString>
String::String(const TString &str) noexcept :
    m_storage{0}
{
    msg::str::Default(m_storage);
    const std::size_t size = msg::str::Size(str);
    msg::str::Allocate(m_storage, size);
    msg::str::Copy(m_storage, size, str);
}

String::String(const String &cpy) noexcept :
    m_storage{0}
{
    msg::str::Default(m_storage);
    const std::size_t size = msg::str::Size(cpy.m_storage);
    msg::str::Allocate(m_storage, size);
    msg::str::Copy(m_storage, size, cpy.m_storage);

}

String::String(String &&mov) noexcept :
    m_storage{0}
{
    msg::str::Default(m_storage);
    msg::str::Move(m_storage, std::move(mov.m_storage));
}

String::~String() noexcept
{
    msg::str::Deallocate(m_storage);
}

String & String::operator=(const String &cpy) noexcept
{
    msg::str::Deallocate(m_storage);
    const std::size_t size = msg::str::Size(cpy.m_storage);
    msg::str::Allocate(m_storage, size);
    msg::str::Copy(m_storage, size, cpy.m_storage);
    return *this;
}

String & String::operator=(String &&mov) noexcept
{
    msg::str::Deallocate(m_storage);
    msg::str::Move(m_storage, std::move(mov.m_storage));
    return *this;
}

const typename String::CharType * String::Value() const noexcept
{
    return msg::str::Value(m_storage);
}

String::operator bool() const noexcept
{
    return !msg::str::IsDefault(m_storage);
}

} //!msg

} //!error

} //!basic

#endif //!BASIC_ERROR_MSG_STRING_H_
