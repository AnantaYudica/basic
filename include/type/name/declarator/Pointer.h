#ifndef BASIC_TYPE_NAME_DECLARATOR_POINTER_H_
#define BASIC_TYPE_NAME_DECLARATOR_POINTER_H_

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
struct Declarator<T*>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T>
struct Declarator<T*const>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T>
struct Declarator<T*volatile>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T>
struct Declarator<T*const volatile>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T, typename To>
struct Declarator<T To::*>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T, typename To>
struct Declarator<T To::*const>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T, typename To>
struct Declarator<T To::*volatile>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T, typename To>
struct Declarator<T To::*const volatile>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T>
void Declarator<T*>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    str_stack.push("*");
    Declarator<T>::ToString(str, str_stack);
}

template<typename T>
void Declarator<T*const>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    str_stack.push("*const");
    Declarator<T>::ToString(str, str_stack);
}

template<typename T>
void Declarator<T*volatile>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    str_stack.push("*volatile");
    Declarator<T>::ToString(str, str_stack);
}

template<typename T>
void Declarator<T*const volatile>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    str_stack.push("*const volatile");
    Declarator<T>::ToString(str, str_stack);
}

template<typename T, typename To>
void Declarator<T To::*>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    str += "(";
    str += Name<To>::ToString();
    str += "::*";
    _helper::_basic::_type::_name::ToString(str, str_stack);
    str += ")";
    Declarator<T>::ToString(str, str_stack);
}
template<typename T, typename To>
void Declarator<T To::*const>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    str += "(";
    str += Name<To>::ToString();
    str += "::*const";
    _helper::_basic::_type::_name::ToString(str, str_stack);
    str += ")";
    Declarator<T>::ToString(str, str_stack);
}

template<typename T, typename To>
void Declarator<T To::*volatile>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    str += "(";
    str += Name<To>::ToString();
    str += "::*volatile";
    _helper::_basic::_type::_name::ToString(str, str_stack);
    str += ")";
    Declarator<T>::ToString(str, str_stack);
}

template<typename T, typename To>
void Declarator<T To::*const volatile>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    str += "(";
    str += Name<To>::ToString();
    str += "::*const volatile";
    _helper::_basic::_type::_name::ToString(str, str_stack);
    str += ")";
    Declarator<T>::ToString(str, str_stack);
}

} //!name

} //!type

} //!basic

#endif //!BASIC_TYPE_NAME_DECLARATOR_POINTER_H_
