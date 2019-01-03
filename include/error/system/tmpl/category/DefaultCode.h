#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEGORY_DEFAULTCODE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEGORY_DEFAULTCODE_H_

#include "has/mmbr/func/DefaultCode.h"
#include "has/mmbr/defn/type/CodeEnum.h"

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
    typename TCategoryTrait::CodeType>::Value, 
    typename TCategoryTrait::CodeType>::type  
DefaultCode(const TCategoryTrait& category_trait) noexcept
{
    return std::move(category_trait.template 
        DefaultCode<typename TCategoryTrait::CodeType>());
}

template<typename TCategoryTrait>
typename std::enable_if<!has::mmbr::func::DefaultCode<TCategoryTrait,
    typename TCategoryTrait::CodeType>::Value &&
    !has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value, 
    typename TCategoryTrait::CodeType>::type  
DefaultCode(const TCategoryTrait& category_trait) noexcept
{
    return {};
}

} //!category

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEGORY_DEFAULTCODE_H_
