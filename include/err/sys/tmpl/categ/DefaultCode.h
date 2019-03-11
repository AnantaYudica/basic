#ifndef BASIC_ERR_SYS_TMPL_CATEG_DEFAULTCODE_H_
#define BASIC_ERR_SYS_TMPL_CATEG_DEFAULTCODE_H_

#include "../Category.defn.h"

#include "has/mmbr/func/DefaultCode.h"
#include "DefaultCodeValue.h"

#include "../../Code.defn.h"

#include <type_traits>
#include <utility>

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
typename std::enable_if<has::mmbr::func::DefaultCode<TCategoryTrait,
    sys::Code, tmpl::Category<TCategoryTrait>>::Value, 
    sys::Code>::type  
DefaultCode(const TCategoryTrait& categ_trait, 
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(categ_trait.template 
        DefaultCode<sys::Code>(categ_instance));
}

template<typename TCategoryTrait>
typename std::enable_if<!has::mmbr::func::DefaultCode<TCategoryTrait,
    sys::Code, const tmpl::Category<TCategoryTrait> &>::Value, 
    sys::Code>::type  
DefaultCode(const TCategoryTrait& categ_trait, 
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return {DefaultCodeValue(categ_trait), categ_instance};
}

} //!categ

} //!tmpl

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_TMPL_CATEG_DEFAULTCODE_H_
