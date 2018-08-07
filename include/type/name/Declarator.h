#ifndef BASIC_TYPE_NAME_H_INITIALIZATION_

#include "../Name.h"

#else //ELSE BASIC_TYPE_NAME_H_INITIALIZATION_

#ifndef BASIC_TYPE_NAME_DECLARATOR_H_
#define BASIC_TYPE_NAME_DECLARATOR_H_

#include <string>
#include <stack>

namespace basic
{
namespace type
{
namespace name
{

template<typename T>
struct Declarator
{
    typedef T RemovedType;
    static void ToString(std::string& str, std::stack<std::string>& str_stack);
};

template<typename T>
void Declarator<T>::
    ToString(std::string& str, std::stack<std::string>& str_stack)
{}

} //!name

} //!type

} //!basic

#include "declarator/Array.h"
#include "declarator/Function.h"
#include "declarator/Pointer.h"
#include "declarator/Reference.h"

#include "../Name.h"

#endif //!BASIC_TYPE_NAME_DECLARATOR_H_

#endif //!BASIC_TYPE_NAME_H_INITIALIZATION_
