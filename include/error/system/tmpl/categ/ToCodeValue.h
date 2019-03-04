#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEG_TOCODEVALUE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEG_TOCODEVALUE_H_

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
namespace categ
{

template<typename TCategoryTrait, typename TCodeEnum>
inline typename std::enable_if<has::mmbr::func::
    ToCodeValue<TCategoryTrait, TCodeEnum>::Value, 
    error::defn::type::system::code::Value>::type 
ToCodeValue(const TCategoryTrait & categ_trait, 
    const TCodeEnum & code) noexcept
{
    return categ_trait.ToCodeValue(code);
}

template<typename TCategoryTrait, typename TCodeEnum>
inline typename std::enable_if<!has::mmbr::func::
    ToCodeValue<TCategoryTrait, TCodeEnum>::Value, 
    error::defn::type::system::code::Value>::type 
ToCodeValue(const TCategoryTrait & categ_trait, 
    const TCodeEnum & code) noexcept
{
    return static_cast<error::defn::type::system::code::Value>(code);
}

} //!categ

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEG_TOCODEVALUE_H_
