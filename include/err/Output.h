#ifndef BASIC_ERR_OUTPUT_H_
#define BASIC_ERR_OUTPUT_H_

#include "defn/type/Output.h"
#include "defn/func/output/Operator.h"
#include "intf/Output.h"
#include "Message.h"

#include <type_traits>

namespace basic
{
namespace err
{

template<typename T>
typename std::enable_if<std::is_base_of<basic::err::intf::Output, T>::value, 
    basic::err::defn::type::Output>::type & 
        Output(basic::err::defn::type::Output & out, const T & val)
{
    val >> out;
    return out;
}

template<typename T>
typename std::enable_if<!std::is_base_of<basic::err::intf::Output, T>::value, 
    basic::err::defn::type::Output>::type & 
        Output(basic::err::defn::type::Output & out, const T & val)
{
    basic::err::defn::func::output::Operator(out, Message(val));
    return out;
}

} //!err

} //!basic

#endif //!BASIC_ERR_OUTPUT_H_