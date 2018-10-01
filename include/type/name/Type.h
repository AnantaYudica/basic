#ifndef BASIC_TYPE_NAME_TYPE_H_
#define BASIC_TYPE_NAME_TYPE_H_

#include <cstddef>
#include <string>
#include <typeinfo>
#include <ostream>

#include "Parameter.h"

namespace basic
{
namespace type
{
namespace name
{
namespace type
{
namespace tmpl
{

static const char OpenBracket[] = "<";
static const char CloseBracket[] = ">";

} //!tmpl

static const char Void[] = "void";
static const char Nullptr[] = "std::nullptr_t";
static const char Bool[] = "bool";
static const char Char[] = "char";
static const char UnsignedChar[] = "unsigned char";
static const char Short[] = "short";
static const char UnsignedShort[] = "unsigned short";
static const char Int[] = "int";
static const char UnsignedInt[] = "unsigned int";
static const char Long[] = "long";
static const char UnsignedLong[] = "unsigned long";
static const char LongLong[] = "long long";
static const char UnsignedLongLong[] = "unsigned long long";
static const char Float[] = "float";
static const char Double[] = "double";
static const char LongDouble[] = "long double";


} //!type

template<typename T>
struct Type
{};

template<typename T, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Type<T>&&)
{
    o << typeid(T).name();
    return o;
}

template<template<typename...> class T, typename CharT, typename Traits,
    typename... Targs>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Type<T<Targs...>>&&)
{
    o << typeid(T<Targs...>).name();
    o << type::tmpl::OpenBracket;
    o << Parameter<Targs...>();
    o << type::tmpl::CloseBracket;
    return o;
}

} //!name

} //!type

} //!basic

#include <cstddef>

namespace basic
{
namespace type
{
namespace name
{

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Type<void>&&)
{
    o << type::Void;
    return o;
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Type<std::nullptr_t>&&)
{
    o << type::Nullptr;
    return o;
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Type<bool>&&)
{
    o << type::Bool;
    return o;
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Type<char>&&)
{
    o << type::Char;
    return o;
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Type<unsigned char>&&)
{
    o << type::UnsignedChar;
    return o;
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Type<short>&&)
{
    o << type::Short;
    return o;
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Type<unsigned short>&&)
{
    o << type::UnsignedShort;
    return o;
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Type<int>&&)
{
    o << type::Int;
    return o;
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Type<unsigned int>&&)
{
    o << type::UnsignedInt;
    return o;
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Type<long>&&)
{
    o << type::Long;
    return o;
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Type<unsigned long>&&)
{
    o << type::UnsignedLong;
    return o;
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Type<long long>&&)
{
    o << type::LongLong;
    return o;
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Type<unsigned long long>&&)
{
    o << type::UnsignedLongLong;
    return o;
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Type<float>&&)
{
    o << type::Float;
    return o;
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Type<double>&&)
{
    o << type::Double;
    return o;
}

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Type<long double>&&)
{
    o << type::LongDouble;
    return o;
}

} //!name

} //!type

} //!basic

#endif //!BASIC_TYPE_NAME_TYPE_H_
