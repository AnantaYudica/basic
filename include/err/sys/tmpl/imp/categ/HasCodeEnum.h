#ifndef BASIC_ERR_SYS_TMPL_IMP_CATEG_HASCODEENUM_H_
#define BASIC_ERR_SYS_TMPL_IMP_CATEG_HASCODEENUM_H_

#include "HasCodeEnum.defn.h"

#include "../../../Code.defn.h"
#include "../../../Condition.defn.h"
#include "../../categ/DefaultCode.h"
#include "../../categ/DefaultCondition.h"

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

template<typename TCategoryTrait, typename TDerive>
Category<TCategoryTrait, TDerive, true>::Category() noexcept :
    tmpl::categ::Base<TCategoryTrait>(),
    intf::Category()
{}

template<typename TCategoryTrait, typename TDerive>
Category<TCategoryTrait, TDerive, true>::
    Category(Category<TCategoryTrait, TDerive, true> && mov) noexcept :
        tmpl::categ::Base<TCategoryTrait>(std::move(mov)),
        intf::Category(std::move(mov))
{}

template<typename TCategoryTrait, typename TDerive>
typename Category<TCategoryTrait, TDerive, true>::CodeType 
Category<TCategoryTrait, TDerive, true>::
    DefaultCode(const CodeSetValueType & code) const noexcept
{
    return categ::DefaultCode(this->GetCategoryTrait(), code, 
        static_cast<const TDerive &>(*this));
}

template<typename TCategoryTrait, typename TDerive>
typename Category<TCategoryTrait, TDerive, true>::ConditionType
Category<TCategoryTrait, TDerive, true>::
    DefaultCondition(const CodeSetValueType & code) const noexcept
{
    return categ::DefaultCondition(this->GetCategoryTrait(), code, 
        static_cast<const TDerive &>(*this));
}

} //!imp

} //!tmpl

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_TMPL_IMP_CATEG_HASCODEENUM_H_
