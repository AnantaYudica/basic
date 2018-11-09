#ifndef BASIC_ERROR_SYSTEM_CATEGORY_VALUE_H_
#define BASIC_ERROR_SYSTEM_CATEGORY_VALUE_H_

#include "has/mmbr/func/Value.h"
#include "../defn/type/category/Value.h"

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
    typename system::defn::type::category::Value>::Value,
    typename system::defn::type::category::Value>::type  
Value(const TCategoryTrait& category_trait) noexcept
{
    return category_trait.Value();
}

template<typename TCategoryTrait>
typename std::enable_if<!has::mmbr::func::Value<TCategoryTrait, 
    typename system::defn::type::category::Value>::Value,
    typename system::defn::type::category::Value>::type  
Value(const TCategoryTrait& category_trait) noexcept
{
    return 0;
}

} //!category

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_CATEGORY_VALUE_H_
