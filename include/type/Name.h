#ifndef BASIC_TYPE_NAME_H_INITIALIZATION_
#define BASIC_TYPE_NAME_H_INITIALIZATION_

#include <string>
#include <stack>
#include <ostream>
#include <sstream>

namespace basic
{
namespace type
{

template<typename T>
struct Name
{
    template<typename charT = char,
        typename traits = std::char_traits<charT>, 
        typename Alloc = std::allocator<charT>>
    static std::basic_string<charT, traits, Alloc> ToString();
};

template<typename T, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Name<T>&&);

} //!type

} //!basic

#include "name/Declarator.h"

#else //ELSE BASIC_TYPE_NAME_H_INITIALIZATION_

#ifndef BASIC_TYPE_NAME_H_
#define BASIC_TYPE_NAME_H_

#include <typeinfo>
#include <string>
#include <stack>

#include "name/Type.h"
#include "name/Specifier.h"

namespace basic
{
namespace type
{

template<typename T, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& 
    operator<<(std::basic_ostream<CharT, Traits>& o, Name<T>&&)
{
    typedef name::Declarator<T> DeclaratorType;
    typedef name::Specifier<typename DeclaratorType::
        RemovedType> SpecifierType;
    typedef typename SpecifierType::RemovedType SimpleType;
    o << SpecifierType();
    o << name::Type<SimpleType>();
    o << DeclaratorType();
    return o;
}

template<typename T>
template<typename charT ,typename traits, typename Alloc>
std::basic_string<charT, traits, Alloc> Name<T>::ToString()
{
    std::basic_ostringstream<char, traits, Alloc> ostr;
    ostr << Name<T>();
    return std::move(ostr.str());
}

} //!type

} //!basic

#endif //!BASIC_TYPE_NAME_H_

#endif //!BASIC_TYPE_NAME_H_INITIALIZATION_
