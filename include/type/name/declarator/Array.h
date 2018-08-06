#ifndef BASIC_TYPE_NAME_DECLARATOR_ARRAY_H_
#define BASIC_TYPE_NAME_DECLARATOR_ARRAY_H_

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
struct Declarator<T[]>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T, std::size_t N>
struct Declarator<T[N]>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T>
void Declarator<T[]>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    _helper::_basic::_type::_name::ToString(str, str_stack, "(", ")");
    str += "[]";
    Declarator<T>::ToString(str, str_stack);
}

template<typename T, std::size_t N>
void Declarator<T[N]>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    _helper::_basic::_type::_name::ToString(str, str_stack, "(", ")");
    str += "[";
    str += std::to_string(N);
    str += "]";
    Declarator<T>::ToString(str, str_stack);
}

} //!name

} //!type

} //!basic

#endif //!BASIC_TYPE_NAME_DECLARATOR_ARRAY_H_
