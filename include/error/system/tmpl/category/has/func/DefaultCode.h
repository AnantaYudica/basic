#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEGORY_HAS_FUNC_DEFAULTCODE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEGORY_HAS_FUNC_DEFAULTCODE_H_

#include "../../defn/type/code/set/Value.h"
#include "../mmbr/func/DefaultCode.h"
#include "../mmbr/defn/type/CodeEnum.h"

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
namespace has
{
namespace func
{

template<typename TCategoryTrait>
struct DefaultCode
{
    static constexpr bool Value = has::mmbr::func::DefaultCode<TCategoryTrait,
        defn::type::code::set::Value<TCategoryTrait>>::Value || 
        !has::mmbr::defn::type::CodeEnum<TCategoryTrait>::Value;
};

} //!func

} //!has

} //!category

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEGORY_HAS_FUNC_DEFAULTCODE_H_
