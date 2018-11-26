#ifndef BASIC_ERROR_OUTPUT_OPERATOR_H_
#define BASIC_ERROR_OUTPUT_OPERATOR_H_

#include "../defn/type/Output.h"
#include "../Definition.h"

#include <utility>

namespace basic
{
namespace error
{
namespace output
{

template<typename TArg>
defn::type::Output& Operator(defn::type::Output& out, TArg&& arg) noexcept
{
    BASIC_ERROR_OUTPUT_OPERATOR(out, std::forward<TArg>(arg));
    return out;
}

} //!output

} //!error

} //!basic

#endif //!BASIC_ERROR_OUTPUT_OPERATOR_H_
