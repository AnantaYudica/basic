#ifndef BASIC_ERR_SYS_TMPL_CATEG_NAME_H_
#define BASIC_ERR_SYS_TMPL_CATEG_NAME_H_

#include "../../../defn/type/Char.h"
#include "has/mmbr/func/Name.h"

#include <type_traits>

namespace basic
{
namespace err
{
namespace sys
{
namespace tmpl
{
namespace categ
{

template<typename TCategoryTrait>
typename std::enable_if<has::mmbr::func::Name<TCategoryTrait>::Value, 
    const err::defn::type::Char *>::type  
Name(const TCategoryTrait& categ_trait) noexcept
{
    return categ_trait.Name();
}

template<typename TCategoryTrait>
typename std::enable_if<!has::mmbr::func::Name<TCategoryTrait>::Value, 
    const err::defn::type::Char *>::type  
Name(const TCategoryTrait& categ_trait) noexcept
{
    return "";
}

} //!categ

} //!tmpl

} //!sys

} //!err

} //!basic


#endif //!BASIC_ERR_SYS_TMPL_CATEG_NAME_H_
