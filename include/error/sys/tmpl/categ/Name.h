#ifndef BASIC_ERROR_SYS_TMPL_CATEG_NAME_H_
#define BASIC_ERROR_SYS_TMPL_CATEG_NAME_H_

#include "../../../defn/type/Char.h"
#include "has/mmbr/func/Name.h"

#include <type_traits>

namespace basic
{
namespace error
{
namespace sys
{
namespace tmpl
{
namespace categ
{

template<typename TCategoryTrait>
typename std::enable_if<has::mmbr::func::Name<TCategoryTrait>::Value, 
    const error::defn::type::Char *>::type  
Name(const TCategoryTrait& categ_trait) noexcept
{
    return categ_trait.Name();
}

template<typename TCategoryTrait>
typename std::enable_if<!has::mmbr::func::Name<TCategoryTrait>::Value, 
    const error::defn::type::Char *>::type  
Name(const TCategoryTrait& categ_trait) noexcept
{
    return "";
}

} //!categ

} //!tmpl

} //!sys

} //!error

} //!basic


#endif //!BASIC_ERROR_SYS_TMPL_CATEG_NAME_H_
