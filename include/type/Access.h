#ifndef BASIC_TYPE_ACCESS_H_
#define BASIC_TYPE_ACCESS_H_

#include <type_traits>
#include "../macro/IsBaseOf.h"
#include "../macro/IsSameWith.h"
#include "../macro/EnableIf.h"

namespace basic
{
namespace type
{

struct Access {};

namespace access
{

struct Public : Access {};

struct Protected : Access {};

struct Private : Access {};

} //!access

} //!type

} //!basic

namespace _helper
{
namespace _basic
{
namespace _type
{
namespace _is_baseof
{

__DEFINE_IS_BASE_OF_DEFAULT_(_Access, __Access, T,  basic::type::Access);

} //!_is_baseof

namespace _access
{
namespace _is_same_with
{

__DEFINE_IS_SAME_WITH_DEFAULT_(_Public, T, basic::type::access::Public);

__DEFINE_IS_SAME_WITH_DEFAULT_(_Protected, T, basic::type::access::Protected);

__DEFINE_IS_SAME_WITH_DEFAULT_(_Private, T, basic::type::access::Private);

} //!_is_same_with

namespace _enable_if
{

__DEFINE_ENABLE_IF_DEFAULT_(_Public, BoolTest, T, To,
    _is_baseof::_Access<T>::value && _is_same_with::_Public<T>::value);

__DEFINE_ENABLE_IF_DEFAULT_(_Protected, BoolTest, T, To,
    _is_baseof::_Access<T>::value && _is_same_with::_Protected<T>::value);

__DEFINE_ENABLE_IF_DEFAULT_(_Private, BoolTest, T, To,
    _is_baseof::_Access<T>::value && _is_same_with::_Private<T>::value);

} //!_enable_if

} //!_access

} //!type

} //!basic

} //!_helper

namespace basic
{
namespace type
{
namespace access
{
namespace enable_if
{

template<typename T, typename To = void, bool BoolOtherTest = true>
using Public = _helper::_basic::_type::_access::
    _enable_if::_Public<BoolOtherTest ,T, To>;

template<typename T, typename To = void, bool BoolOtherTest = true>
using Protected = _helper::_basic::_type::_access::
    _enable_if::_Protected<BoolOtherTest, T, To>;

template<typename T, typename To = void, bool BoolOtherTest = true>
using Private = _helper::_basic::_type::_access::
    _enable_if::_Private<BoolOtherTest, T, To>;

} //!enable_if

} //!access

} //!type

} //!basic

#endif //!BASIC_TYPE_ACCESS_H_
