#ifndef BASIC_ERROR_SYSTEM_CATEGORY_DEFINITION_H_
#define BASIC_ERROR_SYSTEM_CATEGORY_DEFINITION_H_

#include "../../../macro/HasMemberDefinition.h"
#include "../../../type/conditional/Switch.h"

#include "../../Error.h"

#include <type_traits>

namespace _helper
{
namespace _basic
{
namespace _error
{
namespace _system
{
namespace _category
{
namespace _tag
{
namespace _has
{
namespace _mmbr
{
namespace _defn
{

__DEFINE_HAS_MMBR_DEFN_(_CodeEnumType, __CodeEnumType, T,, 
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, CodeEnumType);

__DEFINE_HAS_MMBR_DEFN_(_ConditionEnumType, __ConditionEnumType, T,, 
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, ConditionEnumType);

} //!_defn

} //!_mmbr

} //!_has

template<typename TCategoryTag, bool = 
    _has::_mmbr::_defn::_CodeEnumType<TCategoryTag>::Value>
struct _CodeEnum
{
    typedef BASIC_ERROR_SYSTEM_CODE_VALUE_TYPE Type;
};

template<typename TCategoryTag>
struct _CodeEnum<TCategoryTag, true>
{
    typedef typename TCategoryTag::CodeEnumType Type;
};

template<typename TCategoryTag, bool = 
    _has::_mmbr::_defn::_ConditionEnumType<TCategoryTag>::Value>
struct _ConditionEnum
{
    typedef BASIC_ERROR_SYSTEM_CONDITION_VALUE_TYPE Type;
};

template<typename TCategoryTag>
struct _ConditionEnum<TCategoryTag, true>
{
    typedef typename TCategoryTag::ConditionEnumType Type;
};

} //!_tag

} //!_category

} //!_system

} //!_error

} //!_basic

} //!_helper

namespace basic
{
namespace error
{
namespace system
{
namespace category
{

template<typename TCategoryTrait>
struct Definition
{
    typedef BASIC_ERROR_SYSTEM_CATEGORY_VALUE_TYPE CategoryValueType;
    typedef BASIC_ERROR_SYSTEM_CODE_VALUE_TYPE CodeValueType;
    typedef BASIC_ERROR_SYSTEM_CONDITION_VALUE_TYPE ConditionValueType;

    typedef typename _helper::_basic::_error::_system::_category::_tag::
        _CodeEnum<TCategoryTrait>::Type CodeEnumType;
    typedef typename _helper::_basic::_error::_system::_category::_tag::
        _ConditionEnum<TCategoryTrait>::Type ConditionEnumType;

    static constexpr bool HasCodeEnum = std::is_enum<CodeEnumType>::value;

    static constexpr bool HasConditionEnum = 
        std::is_enum<ConditionEnumType>::value;

};

} //!category

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_CATEGORY_DEFINITION_H_
