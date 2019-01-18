#ifndef BASIC_ERROR_SYSTEM_TMPL_IMP_CATEGORY_H_
#define BASIC_ERROR_SYSTEM_TMPL_IMP_CATEGORY_H_

#include "Category.defn.h"

#include "../../Code.defn.h"
#include "../../Condition.defn.h"

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

template<typename TCategoryTrait, bool HasCodeEnum>
Category<TCategoryTrait, HasCodeEnum>::Category() noexcept :
    tmpl::category::Base<TCategoryTrait>(),
    intf::Category()
{}

template<typename TCategoryTrait, bool HasCodeEnum>
Category<TCategoryTrait, HasCodeEnum>::
    Category(Category<TCategoryTrait, HasCodeEnum> && mov) noexcept :
        tmpl::category::Base<TCategoryTrait>(std::move(mov)),
        intf::Category(std::move(mov))
{}

template<typename TCategoryTrait, bool HasCodeEnum>
typename Category<TCategoryTrait, HasCodeEnum>::CodeType 
Category<TCategoryTrait, HasCodeEnum>::
    DefaultCode(const CodeValueType & code) const noexcept
{
    return {code, *this};
}

template<typename TCategoryTrait, bool HasCodeEnum>
typename Category<TCategoryTrait, HasCodeEnum>::ConditionType
Category<TCategoryTrait, HasCodeEnum>::
    DefaultCondition(const CodeValueType & code) const noexcept
{
    return {code, *this};
}

} //!imp

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_IMP_CATEGORY_H_
