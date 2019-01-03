#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEGORY_NAME_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEGORY_NAME_H_

#include "../../defn/type/Char.h"
#include "has/mmbr/func/Name.h"

#include <type_traits>

namespace basic
{
namespace error
{
namespace system
{
namespace tmpl
{
namespace category
{

template<typename TCategoryTrait>
typename std::enable_if<has::mmbr::func::Name<TCategoryTrait>::Value, 
    const error::defn::type::Char *>::type  
Name(const TCategoryTrait& category_trait) noexcept
{
    return category_trait.Name();
}

template<typename TCategoryTrait>
typename std::enable_if<!has::mmbr::func::Name<TCategoryTrait>::Value, 
    const error::defn::type::Char *>::type  
Name(const TCategoryTrait& category_trait) noexcept
{
    return "";
}

} //!category

} //!tmpl

} //!system

} //!error

} //!basic


#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEGORY_NAME_H_
