#ifndef BASIC_TYPE_NAME_SPECIFIER_H_
#define BASIC_TYPE_NAME_SPECIFIER_H_

#include <string>

namespace basic
{
namespace type
{
namespace name
{
    
template<typename T>
struct Specifier
{
    typedef T RemovedType;
    static void ToString(std::string& str);
};

template<typename T>
struct Specifier<const T>
{
    typedef T RemovedType;
    static void ToString(std::string& str);
};

template<typename T>
struct Specifier<volatile T>
{
    typedef T RemovedType;
    static void ToString(std::string& str);
};

template<typename T>
struct Specifier<const volatile T>
{
    typedef T RemovedType;
    static void ToString(std::string& str);
};

template<typename T>
void Specifier<T>::ToString(std::string& str)
{}

template<typename T>
void Specifier<const T>::ToString(std::string& str)
{
    str += "const ";
}

template<typename T>
void Specifier<volatile T>::ToString(std::string& str)
{
    str += "volatile ";
}

template<typename T>
void Specifier<const volatile T>::ToString(std::string& str)
{
    str += "const volatile ";
}

} //!name

} //!type

} //!basic

#endif //!BASIC_TYPE_NAME_SPECIFIER_H_
