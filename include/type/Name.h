#ifndef BASIC_TYPE_NAME_H_INITIALIZATION_
#define BASIC_TYPE_NAME_H_INITIALIZATION_

#include <string>
#include <stack>

namespace basic
{
namespace type
{

template<typename T>
struct Name
{
    static std::string ToString();
};

} //!type

} //!basic

namespace _helper
{
namespace _basic
{
namespace _type
{
namespace _name
{

void ToString(std::string& str, std::stack<std::string>& str_stack, 
    const char* prefix_cstr = "", const char *postfix_cstr = "")
{
    if (!str_stack.empty())
    {
        str += prefix_cstr;
        while(!str_stack.empty())
        {
            str += str_stack.top();
            str_stack.pop();
        }
        str += postfix_cstr;
    }
}

} //!_name

} //!_type

} //!_basic

} //!_helper

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

template<typename T>
std::string Name<T>::ToString()
{
    typedef name::Declarator<T> DeclaratorType;
    typedef name::Specifier<typename DeclaratorType::
        RemovedType> SpecifierType;
    typedef typename SpecifierType::RemovedType SimpleType;
    std::string declarator_str;
    std::stack<std::string> str_stack;
    std::string str;
    SpecifierType::ToString(str);
    name::Type<SimpleType>::ToString(str, str_stack);
    DeclaratorType::ToString(declarator_str, str_stack);
    _helper::_basic::_type::_name::ToString(str, str_stack);
    str += declarator_str;
    return str;
}

} //!type

} //!basic

#endif //!BASIC_TYPE_NAME_H_

#endif //!BASIC_TYPE_NAME_H_INITIALIZATION_
