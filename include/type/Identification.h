#ifndef BASIC_TYPE_IDENTIFICATION_H_
#define BASIC_TYPE_IDENTIFICATION_H_

#include <type_traits>

#include "type/logic/And.h"

namespace basic
{
namespace type
{

template<typename T>
struct Identification {};

} //!type

} //!basic

namespace _helper
{
namespace _basic
{
namespace _type
{
namespace _id
{

template<typename T1, typename T2>
auto _IsSame(const basic::type::Identification<T2>&) ->
    decltype(std::integral_constant<bool, 
        std::is_same<basic::type::Identification<T2>, T1>::value>());

std::false_type _IsSame(...);

} //!_id

template<typename Tid, bool = 
    decltype(_id::_IsSame<Tid>(std::declval<Tid>()))::value>
struct _IsIdentification
{
    typedef bool ValueType;
    typedef typename _IsIdentification<Tid, true>::ValueType value_type;
    static constexpr ValueType Value = true;
    static constexpr ValueType value = _IsIdentification<Tid, true>::Value;
};

template<typename Tid>
struct _IsIdentification<Tid, false>
{
    typedef bool ValueType;
    typedef typename _IsIdentification<Tid, false>::ValueType value_type;
    static constexpr ValueType Value = false;
    static constexpr ValueType value = _IsIdentification<Tid, false>::Value;
};

template<typename Tid, bool C>
struct _Validation
{
    typedef bool ValueType;
    typedef typename _Validation<Tid, C>::ValueType value_type;
    typedef Tid Type;
    typedef typename _Validation<Tid, C>::Type type;
    static constexpr ValueType Value = C;
    static constexpr ValueType value = _Validation<Tid, C>::Value;
};

template<typename Tid>
struct _Validation<Tid, false>
{
    typedef bool ValueType;
    typedef typename _Validation<Tid, false>::ValueType value_type;
    static constexpr ValueType Value = false;
    static constexpr ValueType value = _Validation<Tid, false>::Value;
};

} //!_type

} //!_basic

} //!_helper

namespace basic
{
namespace type
{

template<typename Tc>
using IsIdentification = _helper::_basic::_type::
    _IsIdentification<Tc>;

template<typename Tid, typename... Targs>
using Validation = _helper::_basic::_type::_Validation<Tid, 
    logic::And<std::integral_constant<bool, true>,
        std::integral_constant<bool, IsIdentification<Tid>::Value>,
        std::integral_constant<bool, std::is_base_of<Targs, Tid>::value
    >...>::Value>;
    
} //!type

} //!basic

#endif //!BASIC_TYPE_IDENTIFICATION_H_
