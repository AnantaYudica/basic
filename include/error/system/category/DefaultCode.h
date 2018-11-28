#ifndef BASIC_ERROR_SYSTEM_CATEGORY_DEFAULTCODE_H_
#define BASIC_ERROR_SYSTEM_CATEGORY_DEFAULTCODE_H_

#include "has/mmbr/func/DefaultCode.h"
#include "defn/type/code/set/Value.h"
#include "has/mmbr/defn/type/CodeEnum.h"

#include <type_traits>

namespace basic
{
namespace error
{
namespace system
{
namespace category
{

template<typename TCategoryTrait>
typename std::enable_if<has::mmbr::func::DefaultCode<TCategoryTrait,
    typename defn::type::code::set::Value<TCategoryTrait>::Type>::Value, 
    typename defn::type::code::set::Value<TCategoryTrait>::Type>::type  
DefaultCode(const TCategoryTrait& category_trait) noexcept
{
    return category_trait.DefaultCode();
}

template<typename TCategoryTrait>
typename std::enable_if<!has::mmbr::func::DefaultCode<TCategoryTrait,
    typename defn::type::code::set::Value<TCategoryTrait>::Type>::Value &&
    !has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value, 
    typename defn::type::code::set::Value<TCategoryTrait>::Type>::type  
DefaultCode(const TCategoryTrait& category_trait) noexcept
{
    return 0;
}

} //!category

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_CATEGORY_DEFAULTCODE_H_
