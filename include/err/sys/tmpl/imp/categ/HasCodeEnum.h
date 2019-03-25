#ifndef BASIC_ERR_SYS_TMPL_IMP_CATEG_HASCODEENUM_H_
#define BASIC_ERR_SYS_TMPL_IMP_CATEG_HASCODEENUM_H_

#include "HasCodeEnum.defn.h"

#include "../../../Code.defn.h"
#include "../../../Condition.defn.h"
#include "../../categ/ToCodeValue.h"

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
namespace imp
{

template<typename TCategoryTrait>
Category<TCategoryTrait, true>::Category() noexcept :
    tmpl::categ::Base<TCategoryTrait>(),
    intf::Category()
{}

template<typename TCategoryTrait>
Category<TCategoryTrait, true>::
    Category(Category<TCategoryTrait, true> && mov) noexcept :
        tmpl::categ::Base<TCategoryTrait>(std::move(mov)),
        intf::Category(std::move(mov))
{}

template<typename TCategoryTrait>
typename Category<TCategoryTrait, true>::CodeType 
Category<TCategoryTrait, true>::
    DefaultCode(const CodeValueType & code) const noexcept
{
    return CodeType{code, *this};
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait, true>::CodeType 
Category<TCategoryTrait, true>::
    DefaultCode(const CodeSetValueType & code) const noexcept
{
    return CodeType{code};
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait, true>::ConditionType
Category<TCategoryTrait, true>::
    DefaultCondition(const CodeValueType & code) const noexcept
{
    return ConditionType{code, *this};
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait, true>::ConditionType
Category<TCategoryTrait, true>::
    DefaultCondition(const CodeSetValueType & code) const noexcept
{
    return ConditionType{categ::ToCodeValue(this->GetCategoryTrait(), code), 
        *this};
}

} //!imp

} //!tmpl

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_TMPL_IMP_CATEG_HASCODEENUM_H_
