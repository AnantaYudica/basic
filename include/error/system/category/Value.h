#ifndef BASIC_ERROR_SYSTEM_CATEGORY_VALUE_H_
#define BASIC_ERROR_SYSTEM_CATEGORY_VALUE_H_

#include "has/mmbr/func/Value.h"
#include "../../defn/type/system/category/Value.h"

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
typename std::enable_if<has::mmbr::func::Value<TCategoryTrait, 
    error::defn::type::system::category::Value>::Value,
    error::defn::type::system::category::Value>::type  
Value(const TCategoryTrait& category_trait) noexcept
{
    return category_trait.Value();
}

template<typename TCategoryTrait>
typename std::enable_if<!has::mmbr::func::Value<TCategoryTrait, 
    error::defn::type::system::category::Value>::Value,
    error::defn::type::system::category::Value>::type  
Value(const TCategoryTrait& category_trait) noexcept
{
    return 0;
}

} //!category

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_CATEGORY_VALUE_H_
