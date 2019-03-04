#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEG_DEFAULTCODE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEG_DEFAULTCODE_H_

#include "../Category.defn.h"

#include "has/mmbr/func/DefaultCode.h"
#include "DefaultCodeValue.h"

#include "../../Code.h"

#include <type_traits>
#include <utility>

namespace basic
{
namespace error
{
namespace system
{
namespace tmpl
{
namespace categ
{

template<typename TCategoryTrait>
typename std::enable_if<has::mmbr::func::DefaultCode<TCategoryTrait,
    system::Code, tmpl::Category<TCategoryTrait>>::Value, 
    system::Code>::type  
DefaultCode(const TCategoryTrait& categ_trait, 
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(categ_trait.template 
        DefaultCode<system::Code>(categ_instance));
}

template<typename TCategoryTrait>
typename std::enable_if<!has::mmbr::func::DefaultCode<TCategoryTrait,
    system::Code, const tmpl::Category<TCategoryTrait> &>::Value, 
    system::Code>::type  
DefaultCode(const TCategoryTrait& categ_trait, 
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return {DefaultCodeValue(categ_trait), categ_instance};
}

} //!categ

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEG_DEFAULTCODE_H_
