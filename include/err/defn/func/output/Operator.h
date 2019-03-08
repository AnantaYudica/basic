#ifndef BASIC_ERR_DEFN_FUNC_OUTPUT_OPERATOR_H_
#define BASIC_ERR_DEFN_FUNC_OUTPUT_OPERATOR_H_

#include "../../type/Output.h"
#include "../../../Definition.h"

#include <utility>

namespace basic
{
namespace err
{
namespace defn
{
namespace func
{
namespace output
{

template<typename TArg>
defn::type::Output& Operator(defn::type::Output& out, TArg&& arg) noexcept
{
    BASIC_ERR_OUTPUT_OPERATOR(out, std::forward<TArg>(arg));
    return out;
}

template<typename TArg, typename... TArgs>
defn::type::Output& Operator(defn::type::Output& out, TArg&& arg, 
    TArgs... args) noexcept
{
    BASIC_ERR_OUTPUT_OPERATOR(out, std::forward<TArg>(arg));
    return Operator(out, std::forward<TArgs>(args)...);
}

} //!output

} //!func

} //!defn

} //!err

} //!basic

#endif //!BASIC_ERR_DEFN_FUNC_OUTPUT_OPERATOR_H_
