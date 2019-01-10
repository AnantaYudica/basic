#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEGORY_DEFAULTCODEVALUE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEGORY_DEFAULTCODEVALUE_H_

#include "has/mmbr/func/DefaultCodeValue.h"
#include "../../../defn/type/code/Value.h"

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
typename std::enable_if<has::mmbr::func::
    DefaultCodeValue<TCategoryTrait>::Value, error::defn::type::code::
    Value>::type 
DefaultCodeValue(const TCategoryTrait & category_trait) noexcept
{
    return category_trait.DefaultCodeValue();
}

template<typename TCategoryTrait>
typename std::enable_if<!has::mmbr::func::
    DefaultCodeValue<TCategoryTrait>::Value, error::defn::type::code::
    Value>::type 
DefaultCodeValue(const TCategoryTrait & category_trait) noexcept
{
    return 0;
}

} //!category

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEGORY_DEFAULTCODEVALUE_H_
