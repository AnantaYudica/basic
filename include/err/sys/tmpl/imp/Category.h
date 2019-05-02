#ifndef BASIC_ERR_SYS_TMPL_IMP_CATEGORY_H_
#define BASIC_ERR_SYS_TMPL_IMP_CATEGORY_H_

#include "Category.defn.h"

#include "../../Code.defn.h"
#include "../../Condition.defn.h"
#include "../categ/DefaultCode.h"
#include "../categ/DefaultCondition.h"

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

template<typename TCategoryTrait, typename TDerive, bool HasCodeEnum>
Category<TCategoryTrait, TDerive, HasCodeEnum>::Category() noexcept :
    tmpl::categ::Base<TCategoryTrait>(),
    intf::Category()
{}

template<typename TCategoryTrait, typename TDerive, bool HasCodeEnum>
Category<TCategoryTrait, TDerive, HasCodeEnum>::
    Category(Category<TCategoryTrait, TDerive, HasCodeEnum> && mov) noexcept :
        tmpl::categ::Base<TCategoryTrait>(std::move(mov)),
        intf::Category(std::move(mov))
{}

} //!imp

} //!tmpl

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_TMPL_IMP_CATEGORY_H_
