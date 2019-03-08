#ifndef BASIC_ERR_OUTPUT_H_
#define BASIC_ERR_OUTPUT_H_

#include "defn/type/Output.h"
#include "defn/func/output/Operator.h"
#include "intf/Output.h"
#include "Message.h"

namespace basic
{
namespace err
{

defn::type::Output& Output(defn::type::Output & out,
    const intf::Output & val)
{
    val >> out;
    return out;
}

template<typename T>
defn::type::Output& Output(defn::type::Output & out,
    const T & val)
{
    defn::func::output::Operator(out, Message(val));
    return out;
}

} //!err

} //!basic

#endif //!BASIC_ERR_OUTPUT_H_