#ifndef BASIC_ERR_SYS_TMPL_CATEG_VALUE_H_
#define BASIC_ERR_SYS_TMPL_CATEG_VALUE_H_

#include "has/mmbr/func/Value.h"
#include "../../../defn/type/sys/categ/Value.h"

#include <type_traits>

namespace basic
{
namespace err
{
namespace sys
{
namespace tmpl
{
namespace categ
{

template<typename TCategoryTrait>
typename std::enable_if<has::mmbr::func::Value<TCategoryTrait, 
    err::defn::type::sys::categ::Value>::Value,
    err::defn::type::sys::categ::Value>::type  
Value(const TCategoryTrait& categ_trait) noexcept
{
    return categ_trait.Value();
}

template<typename TCategoryTrait>
typename std::enable_if<!has::mmbr::func::Value<TCategoryTrait, 
    err::defn::type::sys::categ::Value>::Value,
    err::defn::type::sys::categ::Value>::type  
Value(const TCategoryTrait& categ_trait) noexcept
{
    return 0;
}

} //!categ

} //!tmpl

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_TMPL_CATEG_VALUE_H_
