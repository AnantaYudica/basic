#ifndef BASIC_TYPE_NAME_TYPE_H_
#define BASIC_TYPE_NAME_TYPE_H_

#include <cstddef>
#include <string>
#include <stack>
#include <typeinfo>

#include "Parameter.h"

namespace basic
{
namespace type
{
namespace name
{
    
template<typename T>
struct Type
{
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<template<typename...> class T, typename... Targs>
struct Type<T<Targs...>>
{
    static void ToString(std::string& str,
        std::stack<std::string>& str_stack);
};

template<typename T>
void Type<T>::ToString(std::string& str,
    std::stack<std::string>& str_stack)
{
    str += typeid(T).name();
}

template<template<typename...> class T, typename... Targs>
void Type<T<Targs...>>::ToString(std::string& str,
    std::stack<std::string>& str_stack)
{
    str += typeid(T<Targs...>).name();
    str += "<";
    name::Parameter<Targs...>::ToString(str, str_stack);
    str += ">";
};

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

template<>
struct Type<void>
{
    static void ToString(std::string& str, std::stack<std::string>& str_stack)
    {
        str += "void";
    }
};

template<>
struct Type<std::nullptr_t>
{
    static void ToString(std::string& str, std::stack<std::string>& str_stack)
    {
        str += "std::nullptr_t";
    }
};

template<>
struct Type<bool>
{
    static void ToString(std::string& str, std::stack<std::string>& str_stack)
    {
        str += "bool";
    }
};

template<>
struct Type<unsigned char>
{
    static void ToString(std::string& str, std::stack<std::string>& str_stack)
    {
        str += "unsigned char";
    }
};

template<>
struct Type<char>
{
    static void ToString(std::string& str, std::stack<std::string>& str_stack)
    {
        str += "char";
    }
};

template<>
struct Type<unsigned short>
{
    static void ToString(std::string& str, std::stack<std::string>& str_stack)
    {
        str += "unsigned short";
    }
};

template<>
struct Type<short>
{
    static void ToString(std::string& str, std::stack<std::string>& str_stack)
    {
        str += "short";
    }
};

template<>
struct Type<unsigned int>
{
    static void ToString(std::string& str, std::stack<std::string>& str_stack)
    {
        str += "unsigned int";
    }
};

template<>
struct Type<int>
{
    static void ToString(std::string& str, std::stack<std::string>& str_stack)
    {
        str += "int";
    }
};

template<>
struct Type<unsigned long>
{
    static void ToString(std::string& str, std::stack<std::string>& str_stack)
    {
        str += "unsigned long";
    }
};

template<>
struct Type<long>
{
    static void ToString(std::string& str, std::stack<std::string>& str_stack)
    {
        str += "long";
    }
};

template<>
struct Type<unsigned long long>
{
    static void ToString(std::string& str, std::stack<std::string>& str_stack)
    {
        str += "unsigned long long";
    }
};

template<>
struct Type<long long>
{
    static void ToString(std::string& str, std::stack<std::string>& str_stack)
    {
        str += "long long";
    }
};

template<>
struct Type<float>
{
    static void ToString(std::string& str, std::stack<std::string>& str_stack)
    {
        str += "float";
    }
};

template<>
struct Type<double>
{
    static void ToString(std::string& str, std::stack<std::string>& str_stack)
    {
        str += "double";
    }
};

template<>
struct Type<long double>
{
    static void ToString(std::string& str, std::stack<std::string>& str_stack)
    {
        str += "long double";
    }
};

} //!name

} //!type

} //!basic

#endif //!BASIC_TYPE_NAME_TYPE_H_
