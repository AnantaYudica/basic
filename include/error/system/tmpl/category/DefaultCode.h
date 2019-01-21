#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEGORY_DEFAULTCODE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEGORY_DEFAULTCODE_H_

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
namespace category
{

template<typename TCategoryTrait>
typename std::enable_if<has::mmbr::func::DefaultCode<TCategoryTrait,
    system::Code, tmpl::Category<TCategoryTrait>>::Value, 
    system::Code>::type  
DefaultCode(const TCategoryTrait& category_trait, 
    const tmpl::Category<TCategoryTrait> & category_instance) noexcept
{
    return std::move(category_trait.template 
        DefaultCode<system::Code>(category_instance));
}

template<typename TCategoryTrait>
typename std::enable_if<!has::mmbr::func::DefaultCode<TCategoryTrait,
    system::Code, const tmpl::Category<TCategoryTrait> &>::Value, 
    system::Code>::type  
DefaultCode(const TCategoryTrait& category_trait, 
    const tmpl::Category<TCategoryTrait> & category_instance) noexcept
{
    return {DefaultCodeValue(category_trait), category_instance};
}

} //!category

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEGORY_DEFAULTCODE_H_
