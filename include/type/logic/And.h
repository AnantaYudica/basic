#ifndef BASIC_TYPE_LOGIC_AND_H_
#define BASIC_TYPE_LOGIC_AND_H_

#include <type_traits>

namespace _helper
{
namespace _basic
{
namespace _type
{
namespace _logic
{

template<typename Tt, typename Tc, typename... Targs>
struct _And
{
    static constexpr bool Value = std::is_same<Tt, Tc>::value
        && sizeof...(Targs) == 0;
};

template<typename Tt, typename Targ, typename... Targs>
struct _And<Tt, Tt, Targ, Targs...> : _And<Tt, Targ, Targs...>
{
    static constexpr bool Value = 
        _And<Tt, Targ, Targs...>::Value;
};

} //!_logic

} //!_type

} //!_basic

} //!_helper

namespace basic
{
namespace type
{
namespace logic
{

template<typename Tt, typename Targ, typename... Targs>
struct And 
{
    static constexpr bool Value =
        _helper::_basic::_type::_logic::_And<Tt, Targ, Targs...>::Value;
    static constexpr bool value = And<Tt, Targ, Targs...>::Value;
};

} //!logic

} //!type

} //!basic

#endif //!BASIC_TYPE_LOGIC_AND_H_
