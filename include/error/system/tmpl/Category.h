#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEGORY_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEGORY_H_

#include "Category.defn.h"
#include "../Code.defn.h"
#include "../Condition.defn.h"

#include "imp/categ/HasCodeEnum.h"
#include "../../defn/func/output/Operator.h"
#include "categ/defn/type/code/set/Value.h"
#include "categ/defn/type/condition/set/Value.h"
#include "categ/msg/tag/Code.h"
#include "categ/msg/tag/Condition.h"
#include "categ/DefaultCode.h"
#include "categ/DefaultCodeValue.h"
#include "categ/DefaultCondition.h"
#include "categ/DefaultConditionValue.h"
#include "categ/Equivalent.h"
#include "categ/Message.h"
#include "categ/Name.h"
#include "categ/Value.h"
#include "categ/ToCodeValue.h"
#include "categ/ToConditionValue.h"

#include <cstdint>
#include <utility>
#include <type_traits>
#include <system_error>

namespace basic
{
namespace error
{
namespace system
{
namespace tmpl
{

template<typename TCategoryTrait>
Category<TCategoryTrait> * Category<TCategoryTrait>::ms_instance;

template<typename TCategoryTrait>
Category<TCategoryTrait> & Category<TCategoryTrait>::
    ConstructInstance() noexcept
{
    static Category<TCategoryTrait> instance;
    if (ms_instance == nullptr)
        return instance;
    return *ms_instance;
}

template<typename TCategoryTrait>
const Category<TCategoryTrait> & Category<TCategoryTrait>::
    GetInstance() noexcept
{
    if (ms_instance == nullptr)
        ms_instance = &ConstructInstance();
    return *ms_instance;
}

template<typename TCategoryTrait>
Category<TCategoryTrait>::Category() noexcept :
    tmpl::categ::Base<TCategoryTrait>(),
    tmpl::imp::Category<TCategoryTrait>(),
    tmpl::imp::Exit<TCategoryTrait>()
{}

template<typename TCategoryTrait>
Category<TCategoryTrait>::Category(Category<TCategoryTrait> && mov) noexcept :
    tmpl::categ::Base<TCategoryTrait>(std::move(mov)),
    tmpl::imp::Category<TCategoryTrait>(std::move(mov)),
    tmpl::imp::Exit<TCategoryTrait>(std::move(mov))
{}

template<typename TCategoryTrait>
Category<TCategoryTrait>::~Category() noexcept
{}

template<typename TCategoryTrait>
const TCategoryTrait & Category<TCategoryTrait>::
    GetCategoryTrait() const noexcept
{
    return tmpl::categ::Base<TCategoryTrait>::GetCategoryTrait();
}

template<typename TCategoryTrait>
TCategoryTrait & Category<TCategoryTrait>::GetCategoryTrait() noexcept
{
    return tmpl::categ::Base<TCategoryTrait>::GetCategoryTrait();
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::ValueType 
Category<TCategoryTrait>::Value() const noexcept
{
    return categ::Value(this->GetCategoryTrait());
}

template<typename TCategoryTrait>
const typename Category<TCategoryTrait>::CharType * 
Category<TCategoryTrait>::Name() const noexcept
{
    return categ::Name(this->GetCategoryTrait());
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::CodeValueType 
Category<TCategoryTrait>::DefaultCodeValue() const noexcept
{
    return categ::DefaultCodeValue(this->GetCategoryTrait());
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::CodeType 
Category<TCategoryTrait>::DefaultCode() const noexcept
{
    return categ::DefaultCode(this->GetCategoryTrait(),
        *this);
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::ConditionValueType 
Category<TCategoryTrait>::DefaultConditionValue() const noexcept
{
    return categ::DefaultConditionValue(this->GetCategoryTrait());
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::ConditionType 
Category<TCategoryTrait>::DefaultCondition() const noexcept
{
    return categ::DefaultCondition(this->GetCategoryTrait(),
        categ::DefaultCodeValue(this->GetCategoryTrait()), *this);
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::ConditionType 
Category<TCategoryTrait>::
    DefaultCondition(const CodeType & code) const noexcept
{
    return categ::DefaultCondition(this->GetCategoryTrait(), code.Value(),
        *this);
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::CodeValueType 
Category<TCategoryTrait>::
    ToCodeValue(const CodeSetValueType & code) const noexcept
{
    return categ::ToCodeValue(this->GetCategoryTrait(), code);
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::ConditionValueType 
Category<TCategoryTrait>::
    ToConditionValue(const ConditionSetValueType & cond) const noexcept
{
    return Category::ToConditionValue(this->GetCategoryTrait(), cond);
}

template<typename TCategoryTrait>
bool Category<TCategoryTrait>::Equivalent(const CodeValueType & code, 
    const ConditionType & cond) const noexcept
{
    return categ::Equivalent(this->GetCategoryTrait(), code, cond);
}

template<typename TCategoryTrait>
bool Category<TCategoryTrait>::Equivalent(const CodeType & code,
    const ConditionValueType & cond) const noexcept
{
    return categ::Equivalent(this->GetCategoryTrait(), code, cond);
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::StringType 
Category<TCategoryTrait>::Message(const CodeType & code) const noexcept
{
    return categ::Message<categ::msg::tag::
        Code>(this->GetCategoryTrait(), code);
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::StringType 
Category<TCategoryTrait>::Message(const ConditionType & cond) const noexcept
{
    return categ::Message<categ::msg::tag::
        Condition>(this->GetCategoryTrait(), cond);
}

template<typename TCategoryTrait>
const error::intf::Output & Category<TCategoryTrait>::
    operator>>(OutputType & out) const noexcept
{
    defn::func::output::Operator(out, "category ", this->Name(), 
        ":", this->Value());
    return *this;
}

} //!tmpl

} //!system

} //!error

} //!basic

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator==(const basic::error::system::tmpl::
    Category<TCategoryTraitA>& categ_a, const basic::error::system::tmpl::
    Category<TCategoryTraitA>& categ_b) noexcept
{
    return categ_a.Value() == categ_b.Value();
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator!=(const basic::error::system::tmpl::
    Category<TCategoryTraitA>& categ_a, const basic::error::system::tmpl::
    Category<TCategoryTraitA>& categ_b) noexcept
{
    return !(categ_a == categ_b);
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator<(const basic::error::system::tmpl::
    Category<TCategoryTraitA>& categ_a, const basic::error::system::tmpl::
    Category<TCategoryTraitA>& categ_b) noexcept
{
    return categ_a.Value() < categ_b.Value();
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator>(const basic::error::system::tmpl::
    Category<TCategoryTraitA>& categ_a, const basic::error::system::tmpl::
    Category<TCategoryTraitA>& categ_b) noexcept
{
    return categ_b < categ_a;
}

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEGORY_H_