#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEG_VALUE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEG_VALUE_H_

#include "has/mmbr/func/Value.h"
#include "../../../defn/type/system/categ/Value.h"

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
typename std::enable_if<has::mmbr::func::Value<TCategoryTrait, 
    error::defn::type::system::categ::Value>::Value,
    error::defn::type::system::categ::Value>::type  
Value(const TCategoryTrait& categ_trait) noexcept
{
    return categ_trait.Value();
}

template<typename TCategoryTrait>
typename std::enable_if<!has::mmbr::func::Value<TCategoryTrait, 
    error::defn::type::system::categ::Value>::Value,
    error::defn::type::system::categ::Value>::type  
Value(const TCategoryTrait& categ_trait) noexcept
{
    return 0;
}

} //!categ

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEG_VALUE_H_
