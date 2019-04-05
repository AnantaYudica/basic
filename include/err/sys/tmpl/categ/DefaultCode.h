#ifndef BASIC_ERR_SYS_TMPL_CATEG_DEFAULTCODE_H_
#define BASIC_ERR_SYS_TMPL_CATEG_DEFAULTCODE_H_

#include "../Category.defn.h"

#include "has/mmbr/func/DefaultCode.h"
#include "has/mmbr/defn/type/CodeEnum.h"
#include "defn/type/code/set/Value.h"
#include "DefaultCodeValue.h"
#include "../../../defn/type/sys/code/Value.h"
#include "ToCodeValue.h"
#include "../../Code.defn.h"

#include <type_traits>
#include <utility>

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
typename std::enable_if<
    has::mmbr::func::DefaultCode<TCategoryTrait, sys::Code, 
        tmpl::Category<TCategoryTrait>>::Value, 
    sys::Code>::type  
DefaultCode(const TCategoryTrait& categ_trait, 
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(categ_trait.template 
        DefaultCode<sys::Code>(categ_instance));
}

template<typename TCategoryTrait>
typename std::enable_if<
    !has::mmbr::func::DefaultCode<TCategoryTrait, sys::Code, 
        tmpl::Category<TCategoryTrait>>::Value, 
    sys::Code>::type  
DefaultCode(const TCategoryTrait& categ_trait, 
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return sys::Code{DefaultCodeValue(categ_trait), categ_instance};
}

template<typename TCategoryTrait, typename TValue>
typename std::enable_if<
    has::mmbr::func::DefaultCode<TCategoryTrait, sys::Code, 
        TValue, tmpl::Category<TCategoryTrait>>::Value, 
    sys::Code>::type  
DefaultCode(const TCategoryTrait& categ_trait, const TValue & value,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(categ_trait.template DefaultCode<
        sys::Code>(value, categ_instance));
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::DefaultCode<TCategoryTrait, sys::Code, 
        defn::type::code::set::Value<TCategoryTrait>, 
        tmpl::Category<TCategoryTrait>>::Value &&
    has::mmbr::func::DefaultCode<TCategoryTrait, sys::Code, 
        err::defn::type::sys::code::Value, 
        tmpl::Category<TCategoryTrait>>::Value,
    sys::Code>::type 
DefaultCode(const TCategoryTrait& categ_trait, 
    const defn::type::code::set::Value<TCategoryTrait> & value,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return std::move(categ_trait.template DefaultCode<
        sys::Code>(ToCodeValue(categ_trait, value), categ_instance));
}

template<typename TCategoryTrait>
typename std::enable_if<
    !has::mmbr::func::DefaultCode<TCategoryTrait, sys::Code, 
        err::defn::type::sys::code::Value, 
        tmpl::Category<TCategoryTrait>>::Value, 
    sys::Code>::type  
DefaultCode(const TCategoryTrait& categ_trait, 
    const err::defn::type::sys::code::Value & value,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return sys::Code{value, categ_instance};
}

template<typename TCategoryTrait>
typename std::enable_if<
    has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value &&
    !has::mmbr::func::DefaultCode<TCategoryTrait, sys::Code, 
        defn::type::code::set::Value<TCategoryTrait>, 
        tmpl::Category<TCategoryTrait>>::Value &&
    !has::mmbr::func::DefaultCode<TCategoryTrait, sys::Code, 
        err::defn::type::sys::code::Value, 
        tmpl::Category<TCategoryTrait>>::Value,
    sys::Code>::type 
DefaultCode(const TCategoryTrait& categ_trait, 
    const defn::type::code::set::Value<TCategoryTrait> & value,
    const tmpl::Category<TCategoryTrait> & categ_instance) noexcept
{
    return sys::Code{value};
}

} //!categ

} //!tmpl

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_TMPL_CATEG_DEFAULTCODE_H_
