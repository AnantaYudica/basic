#ifndef BASIC_ERROR_SYS_TMPL_CATEG_VALUE_H_
#define BASIC_ERROR_SYS_TMPL_CATEG_VALUE_H_

#include "has/mmbr/func/Value.h"
#include "../../../defn/type/sys/categ/Value.h"

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
typename std::enable_if<has::mmbr::func::Value<TCategoryTrait, 
    error::defn::type::sys::categ::Value>::Value,
    error::defn::type::sys::categ::Value>::type  
Value(const TCategoryTrait& categ_trait) noexcept
{
    return categ_trait.Value();
}

template<typename TCategoryTrait>
typename std::enable_if<!has::mmbr::func::Value<TCategoryTrait, 
    error::defn::type::sys::categ::Value>::Value,
    error::defn::type::sys::categ::Value>::type  
Value(const TCategoryTrait& categ_trait) noexcept
{
    return 0;
}

} //!categ

} //!tmpl

} //!sys

} //!error

} //!basic

#endif //!BASIC_ERROR_SYS_TMPL_CATEG_VALUE_H_
