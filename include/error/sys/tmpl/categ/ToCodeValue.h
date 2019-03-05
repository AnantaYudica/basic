#ifndef BASIC_ERROR_SYS_TMPL_CATEG_TOCODEVALUE_H_
#define BASIC_ERROR_SYS_TMPL_CATEG_TOCODEVALUE_H_

#include "has/mmbr/func/ToCodeValue.h"
#include "../../../defn/type/sys/code/Value.h"

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

template<typename TCategoryTrait, typename TCodeEnum>
inline typename std::enable_if<has::mmbr::func::
    ToCodeValue<TCategoryTrait, TCodeEnum>::Value, 
    error::defn::type::sys::code::Value>::type 
ToCodeValue(const TCategoryTrait & categ_trait, 
    const TCodeEnum & code) noexcept
{
    return categ_trait.ToCodeValue(code);
}

template<typename TCategoryTrait, typename TCodeEnum>
inline typename std::enable_if<!has::mmbr::func::
    ToCodeValue<TCategoryTrait, TCodeEnum>::Value, 
    error::defn::type::sys::code::Value>::type 
ToCodeValue(const TCategoryTrait & categ_trait, 
    const TCodeEnum & code) noexcept
{
    return static_cast<error::defn::type::sys::code::Value>(code);
}

} //!categ

} //!tmpl

} //!sys

} //!error

} //!basic

#endif //!BASIC_ERROR_SYS_TMPL_CATEG_TOCODEVALUE_H_
