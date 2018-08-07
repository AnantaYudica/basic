#ifndef BASIC_TYPE_NAME_DECLARATOR_FUNCTION_H_
#define BASIC_TYPE_NAME_DECLARATOR_FUNCTION_H_

#include <string>
#include <stack>

#include "../Declarator.h"
#include "../Parameter.h"

namespace basic
{
namespace type
{
namespace name
{

template<typename T, typename... Targs>
struct Declarator<T(Targs...)>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T, typename... Targs>
struct Declarator<T(Targs...) &>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T, typename... Targs>
struct Declarator<T(Targs...) &&>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T, typename... Targs>
struct Declarator<T(Targs...) const>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T, typename... Targs>
struct Declarator<T(Targs...) const &>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T, typename... Targs>
struct Declarator<T(Targs...) const &&>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T, typename... Targs>
struct Declarator<T(Targs...) volatile>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T, typename... Targs>
struct Declarator<T(Targs...) volatile &>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T, typename... Targs>
struct Declarator<T(Targs...) volatile &&>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T, typename... Targs>
struct Declarator<T(Targs...) const volatile>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T, typename... Targs>
struct Declarator<T(Targs...) const volatile &>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T, typename... Targs>
struct Declarator<T(Targs...) const volatile &&>
{
    typedef typename Declarator<T>::RemovedType RemovedType;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack);
};

template<typename T, typename... Targs>
void Declarator<T(Targs...)>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    _helper::_basic::_type::_name::ToString(str, str_stack, "(", ")");
    str += "(";
    name::Parameter<Targs...>::ToString(str, str_stack);
    str += ")";
    Declarator<T>::ToString(str, str_stack);
}

template<typename T, typename... Targs>
void Declarator<T(Targs...) &>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    _helper::_basic::_type::_name::ToString(str, str_stack, "(", ")");
    str += "(";
    name::Parameter<Targs...>::ToString(str, str_stack);
    str += ") &";
    Declarator<T>::ToString(str, str_stack);
}

template<typename T, typename... Targs>
void Declarator<T(Targs...) &&>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    _helper::_basic::_type::_name::ToString(str, str_stack, "(", ")");
    str += "(";
    name::Parameter<Targs...>::ToString(str, str_stack);
    str += ") &&";
    Declarator<T>::ToString(str, str_stack);
}

template<typename T, typename... Targs>
void Declarator<T(Targs...) const>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    _helper::_basic::_type::_name::ToString(str, str_stack, "(", ")");
    str += "(";
    name::Parameter<Targs...>::ToString(str, str_stack);
    str += ") const";
    Declarator<T>::ToString(str, str_stack);
}

template<typename T, typename... Targs>
void Declarator<T(Targs...) const &>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    _helper::_basic::_type::_name::ToString(str, str_stack, "(", ")");
    str += "(";
    name::Parameter<Targs...>::ToString(str, str_stack);
    str += ") const &";
    Declarator<T>::ToString(str, str_stack);
}

template<typename T, typename... Targs>
void Declarator<T(Targs...) const &&>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    _helper::_basic::_type::_name::ToString(str, str_stack, "(", ")");
    str += "(";
    name::Parameter<Targs...>::ToString(str, str_stack);
    str += ") const &&";
    Declarator<T>::ToString(str, str_stack);
}

template<typename T, typename... Targs>
void Declarator<T(Targs...) volatile>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    _helper::_basic::_type::_name::ToString(str, str_stack, "(", ")");
    str += "(";
    name::Parameter<Targs...>::ToString(str, str_stack);
    str += ") volatile";
    Declarator<T>::ToString(str, str_stack);
}

template<typename T, typename... Targs>
void Declarator<T(Targs...) volatile &>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    _helper::_basic::_type::_name::ToString(str, str_stack, "(", ")");
    str += "(";
    name::Parameter<Targs...>::ToString(str, str_stack);
    str += ") volatile &";
    Declarator<T>::ToString(str, str_stack);
}

template<typename T, typename... Targs>
void Declarator<T(Targs...) volatile &&>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    _helper::_basic::_type::_name::ToString(str, str_stack, "(", ")");
    str += "(";
    name::Parameter<Targs...>::ToString(str, str_stack);
    str += ") volatile &&";
    Declarator<T>::ToString(str, str_stack);
}

template<typename T, typename... Targs>
void Declarator<T(Targs...) const volatile>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    _helper::_basic::_type::_name::ToString(str, str_stack, "(", ")");
    str += "(";
    name::Parameter<Targs...>::ToString(str, str_stack);
    str += ") const volatile";
    Declarator<T>::ToString(str, str_stack);
}

template<typename T, typename... Targs>
void Declarator<T(Targs...) const volatile &>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    _helper::_basic::_type::_name::ToString(str, str_stack, "(", ")");
    str += "(";
    name::Parameter<Targs...>::ToString(str, str_stack);
    str += ") const volatile &";
    Declarator<T>::ToString(str, str_stack);
}

template<typename T, typename... Targs>
void Declarator<T(Targs...) const volatile &&>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{
    _helper::_basic::_type::_name::ToString(str, str_stack, "(", ")");
    str += "(";
    name::Parameter<Targs...>::ToString(str, str_stack);
    str += ") const volatile &&";
    Declarator<T>::ToString(str, str_stack);
}

} //!name

} //!type

} //!basic

#endif //!BASIC_TYPE_NAME_DECLARATOR_FUNCTION_H_
