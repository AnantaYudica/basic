#ifndef BASIC_TYPE_LOGIC_XOR_H_
#define BASIC_TYPE_LOGIC_XOR_H_

#include "And.h"
#include "Or.h"

namespace basic
{
namespace type
{
namespace logic
{

template<typename Tt, typename Targ, typename... Targs>
struct Xor 
{
    static constexpr bool Value =
        Or<Tt, Targ, Targs...>::Value && 
        !And<Tt, Targ, Targs...>::Value;
    static constexpr bool value = Xor<Tt, Targ, Targs...>::Value;
};

} //!logic

} //!type

} //!basic

#endif //!BASIC_TYPE_LOGIC_XOR_H_
