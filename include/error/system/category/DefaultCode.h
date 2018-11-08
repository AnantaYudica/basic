#ifndef BASIC_ERROR_SYSTEM_CATEGORY_DEFAULTCODE_H_
#define BASIC_ERROR_SYSTEM_CATEGORY_DEFAULTCODE_H_

#include "has/mmbr/func/DefaultCode.h"
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
typename std::enable_if<has::mmbr::func::DefaultCode<TCategoryTrait,
    typename Definition<TCategoryTrait>::CodeEnumType>::Value, 
    typename Definition<TCategoryTrait>::CodeEnumType>::type  
DefaultCode(const TCategoryTrait& category_trait)
{
    return category_trait.DefaultCode();
}

template<typename TCategoryTrait>
typename std::enable_if<!has::mmbr::func::DefaultCode<TCategoryTrait,
    typename Definition<TCategoryTrait>::CodeEnumType>::Value, 
    typename Definition<TCategoryTrait>::CodeEnumType>::type  
DefaultCode(const TCategoryTrait& category_trait)
{
    return 0;
}

} //!category

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_CATEGORY_DEFAULTCODE_H_
