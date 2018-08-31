#ifndef BASIC_TYPE_NAME_DECLARATOR_ARRAY_H_
#define BASIC_TYPE_NAME_DECLARATOR_ARRAY_H_

#include <string>

#include "../Declarator.h"
#include "Pointer.h"
#include "Reference.h"

namespace basic
{
namespace type
{
namespace name
{
namespace decltor
{
namespace arr
{

static const char OpenBracket[] = "[";
static const char CloseBracket[] = "]";

} //!arr

} //!decltor

template<typename T>
class Declarator<T[]> :
    public Declarator<T>
{
protected:
    typedef typename Declarator<T>::BaseType BaseType;
public:
    typedef typename Declarator<T>::RemovedType RemovedType;
public:
    constexpr Declarator();
protected:
    constexpr Declarator(const decltor::Type& first, const char& flags);
public:
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Backward(std::basic_ostream<CharT, Traits>& o, Td&& d);
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Forward(std::basic_ostream<CharT, Traits>& o, Td&& d);
};

template<typename T, std::size_t N>
class Declarator<T[N]> :
    public Declarator<T>
{
protected:
    typedef typename Declarator<T>::BaseType BaseType;
public:
    typedef typename Declarator<T>::RemovedType RemovedType;
public:
    constexpr Declarator();
protected:
    constexpr Declarator(const decltor::Type& first, const char& flags);
public:
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Backward(std::basic_ostream<CharT, Traits>& o, Td&& d);
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Forward(std::basic_ostream<CharT, Traits>& o, Td&& d);
};

template<typename T>
constexpr Declarator<T[]>::Declarator() :
    Declarator<T>(decltor::Type::array_flag, decltor::Type::array_flag)
{}

template<typename T>
constexpr Declarator<T[]>::Declarator(const decltor::Type& first, 
    const char& flags) :
        Declarator<T>(first, flags | decltor::Type::array_flag)
{}

template<typename T>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& 
    Declarator<T[]>::Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::OpenBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::OpenBracket;
    return o;
}

template<typename T>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& 
    Declarator<T[]>::Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::CloseBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::CloseBracket;
    o << decltor::arr::OpenBracket;
    o << decltor::arr::CloseBracket;
    Declarator<T>::Forward(o, d);
    return o;
}

template<typename T, std::size_t N>
constexpr Declarator<T[N]>::Declarator() :
    Declarator<T>(decltor::Type::array_flag, decltor::Type::array_flag)
{}

template<typename T, std::size_t N>
constexpr Declarator<T[N]>::Declarator(const decltor::Type& first, 
    const char& flags) :
        Declarator<T>(first, flags | decltor::Type::array_flag)
{}

template<typename T, std::size_t N>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& 
    Declarator<T[N]>::Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::OpenBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::OpenBracket;
    return o;
}

template<typename T, std::size_t N>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& 
    Declarator<T[N]>::Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    if (d.IsFirst(decltor::Type::pointer_flag))
        o << decltor::ptr::CloseBracket;
    else if(d.IsFirst(decltor::Type::reference_flag))
        o << decltor::ref::CloseBracket;
    o << decltor::arr::OpenBracket;
    o << N;
    o << decltor::arr::CloseBracket;
    Declarator<T>::Forward(o, d);
    return o;
}

} //!name

} //!type

} //!basic

#endif //!BASIC_TYPE_NAME_DECLARATOR_ARRAY_H_
