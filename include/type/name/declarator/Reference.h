#ifndef BASIC_TYPE_NAME_DECLARATOR_REFERENCE_H_
#define BASIC_TYPE_NAME_DECLARATOR_REFERENCE_H_

#include <string>
#include <ostream>

#include "../Declarator.h"

namespace basic
{
namespace type
{
namespace name
{
namespace decltor
{
namespace ref
{

static const char LValue[] = "&";
static const char RValue[] = "&&";
static const char OpenBracket[] = "(";
static const char CloseBracket[] = ")";

} //!ref

} //!decltor

template<typename T>
class Declarator<T&> :
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
class Declarator<T&&> :
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
constexpr Declarator<T&>::Declarator() :
    Declarator<T>(decltor::Type::reference_flag, decltor::Type::reference_flag)
{}

template<typename T>
constexpr Declarator<T&>::Declarator(const decltor::Type& first, 
     const char& flags) :
        Declarator<T>(first, flags | decltor::Type::reference_flag)
{}

template<typename T>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& 
    Declarator<T&>::Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    o << decltor::ref::LValue;
    return o;
}

template<typename T>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& 
    Declarator<T&>::Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Forward(o, d);
    return o;
}

template<typename T>
constexpr Declarator<T&&>::Declarator() :
    Declarator<T>(decltor::Type::reference_flag, decltor::Type::reference_flag)
{}

template<typename T>
constexpr Declarator<T&&>::Declarator(const decltor::Type& first, 
     const char& flags) :
        Declarator<T>(first, flags | decltor::Type::reference_flag)
{}

template<typename T>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& 
    Declarator<T&&>::Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Backward(o, d);
    o << decltor::ref::RValue;
    return o;
}

template<typename T>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& 
    Declarator<T&&>::Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    Declarator<T>::Forward(o, d);
    return o;
}

} //!name

} //!type

} //!basic

#endif //!BASIC_TYPE_NAME_DECLARATOR_REFERENCE_H_
