#ifndef BASIC_TYPE_NAME_H_INITIALIZATION_

#include "../Name.h"

#else //ELSE BASIC_TYPE_NAME_H_INITIALIZATION_

#ifndef BASIC_TYPE_NAME_DECLTOR_H_
#define BASIC_TYPE_NAME_DECLTOR_H_

#include <string>
#include <ostream>

namespace basic
{
namespace type
{
namespace name
{
namespace decltor
{

enum Type: char
{
    undefined_flag = 0,
    pointer_flag = 1,
    reference_flag = 2,
    array_flag = 4,
    function_flag = 8
};

} //!decltor

template<typename T>
class Declarator
{
protected:
    typedef Declarator<T> BaseType;
public:
    typedef T RemovedType;
private:
    const decltor::Type m_first;
    const char m_flags;
public:
    constexpr Declarator();
protected:
    constexpr Declarator(const decltor::Type& first, const char& flags);
protected:
    constexpr bool IsFirst(const decltor::Type& type);
    constexpr bool HasFlag(const decltor::Type& type);
public:
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Backward(std::basic_ostream<CharT, Traits>& o, Td&& d);
    template<typename CharT, typename Traits, typename Td>
    static std::basic_ostream<CharT, Traits>& 
        Forward(std::basic_ostream<CharT, Traits>& o, Td&& d);
};

template<typename T>
constexpr Declarator<T>::Declarator() :
    m_first(decltor::Type::undefined_flag),
    m_flags(decltor::Type::undefined_flag)
{}

template<typename T>
constexpr Declarator<T>::Declarator(const decltor::Type& first, 
    const char& flags) :
        m_first(first),
        m_flags(flags)
{}

template<typename T>
constexpr bool Declarator<T>::IsFirst(const decltor::Type& flag)
{
    return m_first == flag;
}

template<typename T>
constexpr bool Declarator<T>::HasFlag(const decltor::Type& flag)
{
    return m_flags & flag;
}

template<typename T>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& 
    Declarator<T>::Backward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    return o;
}

template<typename T>
template<typename CharT, typename Traits, typename Td>
std::basic_ostream<CharT, Traits>& 
    Declarator<T>::Forward(std::basic_ostream<CharT, Traits>& o, Td&& d)
{
    return o;
}

template<typename T, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Declarator<T>&& d)
{
    Declarator<T>::Backward(o, d);
    Declarator<T>::Forward(o, d);
    return o;
}

} //!name

} //!type

} //!basic

#include "decltor/Array.h"
#include "decltor/Function.h"
#include "decltor/Pointer.h"
#include "decltor/Reference.h"

#include "../Name.h"

#endif //!BASIC_TYPE_NAME_DECLTOR_H_

#endif //!BASIC_TYPE_NAME_H_INITIALIZATION_
