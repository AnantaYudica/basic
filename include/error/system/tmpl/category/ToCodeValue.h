#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEGORY_TOCODEVALUE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEGORY_TOCODEVALUE_H_

#include "has/mmbr/func/ToCodeValue.h"
#include "../../../defn/type/system/code/Value.h"

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

template<typename TCategoryTrait, typename TCodeEnum>
inline typename std::enable_if<has::mmbr::func::
    ToCodeValue<TCategoryTrait, TCodeEnum>::Value, 
    error::defn::type::system::code::Value>::type 
ToCodeValue(const TCategoryTrait & category_trait, 
    const TCodeEnum & code) noexcept
{
    return category_trait.ToCodeValue(code);
}

template<typename TCategoryTrait, typename TCodeEnum>
inline typename std::enable_if<!has::mmbr::func::
    ToCodeValue<TCategoryTrait, TCodeEnum>::Value, 
    error::defn::type::system::code::Value>::type 
ToCodeValue(const TCategoryTrait & category_trait, 
    const TCodeEnum & code) noexcept
{
    return static_cast<error::defn::type::system::code::Value>(code);
}

} //!category

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEGORY_TOCODEVALUE_H_
