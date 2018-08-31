#ifndef BASIC_TYPE_NAME_SPECIFIER_H_
#define BASIC_TYPE_NAME_SPECIFIER_H_

#include <ostream>

namespace basic
{
namespace type
{
namespace name
{
namespace specifier
{

static const char NoPostfix[] = "";
static const char Postfix[] = " ";
static const char Empty[] = "";
static const char Const[] = "const";
static const char Volatile[] = "volatile";
static const char ConstVolatile[] = "const volatile";

}
    
template<typename T>
struct Specifier
{
    typedef T RemovedType;
};

template<typename T>
struct Specifier<const T>
{
    typedef T RemovedType;
};

template<typename T>
struct Specifier<volatile T>
{
    typedef T RemovedType;
};

template<typename T>
struct Specifier<const volatile T>
{
    typedef T RemovedType;
};

template<typename T, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Specifier<T>&&)
{
    o << specifier::Empty << specifier::NoPostfix;
    return o;
}

template<typename T, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Specifier<const T>&&)
{
    o << specifier::Const << specifier::Postfix;
    return o;
}

template<typename T, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Specifier<volatile T>&&)
{
    o << specifier::Volatile << specifier::Postfix;
    return o;
}

template<typename T, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, 
        Specifier<const volatile T>&&)
{
    o << specifier::ConstVolatile << specifier::Postfix;
    return o;
}

} //!name

} //!type

} //!basic

#endif //!BASIC_TYPE_NAME_SPECIFIER_H_
