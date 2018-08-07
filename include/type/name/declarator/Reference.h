#ifndef BASIC_TYPE_NAME_DECLARATOR_REFERENCE_H_
#define BASIC_TYPE_NAME_DECLARATOR_REFERENCE_H_

#include <string>
#include <stack>

#include "../Declarator.h"

namespace basic
{
namespace type
{
namespace name
{

template<typename T>
struct Declarator<T&>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T>
struct Declarator<T&&>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T>
void Declarator<T&>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    str_stack.push("&");
    Declarator<T>::ToString(str, str_stack);
}

template<typename T>
void Declarator<T&&>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    str_stack.push("&&");
    Declarator<T>::ToString(str, str_stack);
}

} //!name

} //!type

} //!basic

#endif //!BASIC_TYPE_NAME_DECLARATOR_REFERENCE_H_
