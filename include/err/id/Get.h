#ifndef BASIC_ERR_ID_GET_H_
#define BASIC_ERR_ID_GET_H_

#include "../../macro/IsBaseOf.h"
#include "../../macro/IsSameWith.h"
#include "../../macro/EnableIf.h"
#include "../Identification.h"
#include "../../Error.h"

#include <type_traits>

namespace _helper
{
namespace _basic
{
namespace _err
{
namespace _id
{
namespace _is
{
namespace _base_of
{
namespace _tag
{
    
__DEFINE_IS_BASE_OF_(_Trigger, __Trigger, T,, T_NAME_,,,,,
    PROTO_FUNC_T_NAME_,, basic::Error<basic::err::tag::Trigger>);

__DEFINE_IS_BASE_OF_(_System, __System, T,, T_NAME_,,,,,
    PROTO_FUNC_T_NAME_,, basic::Error<basic::err::tag::System>);

} //!_tag

} //!_base_of

namespace _same_with
{
namespace _tag
{

__DEFINE_IS_SAME_WITH_(_Trigger, T,,, 
    basic::Error<basic::err::tag::Trigger>);

__DEFINE_IS_SAME_WITH_(_System, T,,, 
    basic::Error<basic::err::tag::System>);

} //!_tag

} //!_same_with

} //!_is

namespace _enable_if
{
namespace _tag
{
    
__DEFINE_ENABLE_IF_(_Trigger, BoolTest, T, To,,,, T_OUT_NAME_,,
    ALIAS_TYPE_,, std::is_same<T, basic::err::tag::Trigger>::value);

__DEFINE_ENABLE_IF_(_System, BoolTest, T, To,,,, T_OUT_NAME_,,
    ALIAS_TYPE_,, std::is_same<T, basic::err::tag::System>::value);

} //!_tag

} //!_enable_if

} //!_id

} //!_err

} //!_basic

} //!_helper

namespace basic
{
namespace err
{
namespace id
{
namespace enable_if
{
namespace tag
{

template<typename TTagError, bool BoolTest = true>
using Trigger = _helper::_basic::_err::_id::_enable_if::_tag::
    _Trigger<BoolTest, TTagError, Identification>;

template<typename TTagError, bool BoolTest = true>
using System = _helper::_basic::_err::_id::_enable_if::_tag::
    _System<BoolTest, TTagError, Identification>;

} //!tag

} //!enable_if

template<typename TTagError = tag::Trigger, typename TException>
typename id::enable_if::tag::Trigger<TTagError, 
    _helper::_basic::_err::_id::_is::_base_of::_tag::
        _Trigger<TException>::Value || 
    _helper::_basic::_err::_id::_is::_same_with::_tag::
        _Trigger<TException>::Value>::Type 
Get(const TException& e) noexcept
{
    return static_cast<const Error<tag::Trigger>&>(e).Identification();
}


template<typename TTagError = tag::Trigger, typename TException>
typename id::enable_if::tag::System<TTagError, 
    _helper::_basic::_err::_id::_is::_base_of::_tag::
        _System<TException>::Value || 
    _helper::_basic::_err::_id::_is::_same_with::_tag::
        _System<TException>::Value>::Type 
Get(const TException& e) noexcept
{
    return static_cast<const Error<tag::System>&>(e).Identification();
}

} //!id

} //!err

} //!basic

#endif //!BASIC_ERR_ID_GET_H_
