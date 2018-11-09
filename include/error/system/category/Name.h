#ifndef BASIC_ERROR_SYSTEM_CATEGORY_NAME_H_
#define BASIC_ERROR_SYSTEM_CATEGORY_NAME_H_

#include "has/mmbr/func/Name.h"

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
typename std::enable_if<has::mmbr::func::Name<TCategoryTrait>::Value, 
    const char *>::type  
Name(const TCategoryTrait& category_trait) noexcept
{
    return category_trait.Name();
}

template<typename TCategoryTrait>
typename std::enable_if<!has::mmbr::func::Name<TCategoryTrait>::Value, 
    const char *>::type  
Name(const TCategoryTrait& category_trait) noexcept
{
    return "";
}

} //!category

} //!system

} //!error

} //!basic


#endif //!BASIC_ERROR_SYSTEM_CATEGORY_NAME_H_
