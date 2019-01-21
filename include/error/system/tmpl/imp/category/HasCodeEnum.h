#ifndef BASIC_ERROR_SYSTEM_TMPL_IMP_CATEGORY_HASCODEENUM_H_
#define BASIC_ERROR_SYSTEM_TMPL_IMP_CATEGORY_HASCODEENUM_H_

#include "HasCodeEnum.defn.h"

#include "../../../Code.defn.h"
#include "../../../Condition.defn.h"
#include "../../category/ToCodeValue.h"

#include <type_traits>
#include <utility>

namespace basic
{
namespace error
{
namespace system
{
namespace tmpl
{
namespace imp
{

template<typename TCategoryTrait>
Category<TCategoryTrait, true>::Category() noexcept :
    tmpl::category::Base<TCategoryTrait>(),
    intf::Category()
{}

template<typename TCategoryTrait>
Category<TCategoryTrait, true>::
    Category(Category<TCategoryTrait, true> && mov) noexcept :
        tmpl::category::Base<TCategoryTrait>(std::move(mov)),
        intf::Category(std::move(mov))
{}

template<typename TCategoryTrait>
typename Category<TCategoryTrait, true>::CodeType 
Category<TCategoryTrait, true>::
    DefaultCode(const CodeValueType & code) const noexcept
{
    return {code, *this};
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait, true>::CodeType 
Category<TCategoryTrait, true>::
    DefaultCode(const CodeSetValueType & code) const noexcept
{
    return {code};
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait, true>::ConditionType
Category<TCategoryTrait, true>::
    DefaultCondition(const CodeValueType & code) const noexcept
{
    return {code, *this};
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait, true>::ConditionType
Category<TCategoryTrait, true>::
    DefaultCondition(const CodeSetValueType & code) const noexcept
{
    return {category::ToCodeValue(this->GetCategoryTrait(), code), *this};
}

} //!imp

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_IMP_CATEGORY_HASCODEENUM_H_
