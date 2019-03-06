#ifndef BASIC_TYPE_CONDL_SWITCH_H_
#define BASIC_TYPE_CONDL_SWITCH_H_

#include <type_traits>

namespace _helper
{
namespace _basic
{
namespace _type
{
namespace _condl
{

template<bool, typename Td, typename Tr, 
    std::size_t Idx, typename... Targs>
struct _Switch 
{
    typedef typename std::conditional<
        std::is_same<Td, Tr>::value, Td, Tr>::type Type; 
    static constexpr std::size_t Index =
        std::is_same<Td, Tr>::value ? Idx : Idx - 1;
};

template<typename Td, std::size_t Idx, 
    typename Targ, typename... Targs>
struct _Switch<false, Td, Targ, Idx, Targs...>
{
    typedef Targ Type; 
    static constexpr std::size_t Index = Idx - 1;
};

template<typename Td, std::size_t Idx, 
    typename Targ, typename... Targs>
struct _Switch<true, Td, Td, Idx, Targ, Targs...> :
    _Switch<std::is_same<Td, Targ>::value, 
        Td, Targ, Idx + 1, Targs...>
{
    static constexpr std::size_t Index =
        _Switch<std::is_same<Td, Targ>::value, 
            Td, Targ, Idx + 1, Targs...>::Index;
    typedef typename _Switch<std::is_same<Td, Targ>::value,
        Td, Targ, Idx + 1, Targs...>::Type Type;
};

} //!_condl;

} //!_type

} //!_basic

} //!_helper

namespace basic
{
namespace type
{
namespace condl
{

template<typename Td, typename... Targs>
struct Switch
{
    typedef typename _helper::_basic::_type::_condl::
        template _Switch<true, Td, Td, 0, Targs...>::Type Type;
    typedef typename Switch<Td, Targs...>::Type type;
    static constexpr std::size_t Index =
        _helper::_basic::_type::_condl::_Switch<true, Td,
            Td, 0, Targs...>::Index;
    static constexpr std::size_t index = Switch<Td, Targs...>::Index;
    static constexpr std::size_t Size = sizeof...(Targs);
    static constexpr std::size_t size = Switch<Td, Targs...>::Size;
};

} //!condl

} //!type

} //!basic

#endif //!BASIC_TYPE_CONDL_SWITCH_H_
