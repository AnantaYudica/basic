#ifndef BASIC_ERROR_SYSTEM_CATEGORY_VALUE_H_
#define BASIC_ERROR_SYSTEM_CATEGORY_VALUE_H_

#include "has/mmbr/func/Value.h"
#include "Definition.h"

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
    typename Definition<TCategoryTrait>::CategoryValueType>::Value,
    typename Definition<TCategoryTrait>::CategoryValueType>::type  
Value(const TCategoryTrait& category_trait)
{
    return category_trait.Value();
}

template<typename TCategoryTrait>
typename std::enable_if<!has::mmbr::func::Value<TCategoryTrait, 
    typename Definition<TCategoryTrait>::CategoryValueType>::Value,
    typename Definition<TCategoryTrait>::CategoryValueType>::type  
Value(const TCategoryTrait& category_trait)
{
    return 0;
}

} //!category

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_CATEGORY_VALUE_H_
