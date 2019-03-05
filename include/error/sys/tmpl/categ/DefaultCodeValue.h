#ifndef BASIC_ERROR_SYS_TMPL_CATEG_DEFAULTCODEVALUE_H_
#define BASIC_ERROR_SYS_TMPL_CATEG_DEFAULTCODEVALUE_H_

#include "has/mmbr/func/DefaultCodeValue.h"
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

template<typename TCategoryTrait>
inline typename std::enable_if<has::mmbr::func::
    DefaultCodeValue<TCategoryTrait>::Value, error::defn::type::sys::code::
    Value>::type 
DefaultCodeValue(const TCategoryTrait & categ_trait) noexcept
{
    return categ_trait.DefaultCodeValue();
}

template<typename TCategoryTrait>
inline typename std::enable_if<!has::mmbr::func::
    DefaultCodeValue<TCategoryTrait>::Value, error::defn::type::sys::code::
    Value>::type 
DefaultCodeValue(const TCategoryTrait & categ_trait) noexcept
{
    return 0;
}

} //!categ

} //!tmpl

} //!sys

} //!error

} //!basic

#endif //!BASIC_ERROR_SYS_TMPL_CATEG_DEFAULTCODEVALUE_H_
