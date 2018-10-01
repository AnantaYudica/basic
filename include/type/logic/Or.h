#ifndef BASIC_TYPE_LOGIC_OR_H_
#define BASIC_TYPE_LOGIC_OR_H_

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
struct _Or : _Or<Tt, Targs...>
{
    static constexpr bool Value = _Or<Tt, Targs...>::Value;
};

template<typename Tt, typename Tc>
struct _Or<Tt, Tc>
{
    static constexpr bool Value = std::is_same<Tt, Tc>::value;
};

template<typename Tt, typename Targ, typename... Targs>
struct _Or<Tt, Tt, Targ, Targs...>
{
    static constexpr bool Value = true;
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
struct Or 
{
    static constexpr bool Value =
        _helper::_basic::_type::_logic::_Or<Tt, Targ, Targs...>::Value;
    static constexpr bool value = Or<Tt, Targ, Targs...>::Value;
};

} //!logic

} //!type

} //!basic

#endif //!BASIC_TYPE_LOGIC_OR_H_
