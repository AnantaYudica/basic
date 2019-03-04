#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEG_DEFAULTCODEVALUE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEG_DEFAULTCODEVALUE_H_

#include "has/mmbr/func/DefaultCodeValue.h"
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

template<typename TCategoryTrait>
inline typename std::enable_if<has::mmbr::func::
    DefaultCodeValue<TCategoryTrait>::Value, error::defn::type::system::code::
    Value>::type 
DefaultCodeValue(const TCategoryTrait & categ_trait) noexcept
{
    return categ_trait.DefaultCodeValue();
}

template<typename TCategoryTrait>
inline typename std::enable_if<!has::mmbr::func::
    DefaultCodeValue<TCategoryTrait>::Value, error::defn::type::system::code::
    Value>::type 
DefaultCodeValue(const TCategoryTrait & categ_trait) noexcept
{
    return 0;
}

} //!categ

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEG_DEFAULTCODEVALUE_H_
