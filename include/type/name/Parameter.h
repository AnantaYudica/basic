#ifndef BASIC_TYPE_NAME_PARAMETER_H_
#define BASIC_TYPE_NAME_PARAMETER_H_

#include <string>
#include <stack>

namespace basic
{
namespace type
{
namespace name
{

template<typename... Targs>
struct Parameter final
{
    Parameter() = delete;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack, bool first = true);
};

template<typename Targ, typename... Targs>
struct Parameter<Targ, Targs...> final
{
    Parameter() = delete;
    static void ToString(std::string& str, 
        std::stack<std::string>& str_stack, bool first = true);
};

template<typename... Targs>
void Parameter<Targs...>::ToString(std::string& str, 
    std::stack<std::string>& str_stack, bool first)
{}

template<typename Targ, typename... Targs>
void Parameter<Targ, Targs...>::ToString(std::string& str, 
    std::stack<std::string>& str_stack, bool first)
{
    if (!first)
        str += ", ";
    str += Name<Targ>::ToString();
    Parameter<Targs...>::ToString(str, str_stack, false);
}

} //!name

} //!type

} //!basic

#endif //!BASIC_TYPE_NAME_PARAMETER_H_
