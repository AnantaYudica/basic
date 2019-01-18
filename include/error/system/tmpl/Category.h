#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEGORY_H_
#define BASIC_ERROR_SYSTEM_TMPL_CATEGORY_H_

#include "Category.defn.h"
#include "../Code.defn.h"
#include "../Condition.defn.h"

#include "../../output/Operator.h"
#include "category/defn/type/code/set/Value.h"
#include "category/defn/type/condition/set/Value.h"
#include "category/msg/tag/Code.h"
#include "category/msg/tag/Condition.h"
#include "category/DefaultCode.h"
#include "category/DefaultCodeValue.h"
#include "category/DefaultCondition.h"
#include "category/DefaultConditionValue.h"
#include "category/Equivalent.h"
#include "category/Message.h"
#include "category/Name.h"
#include "category/Value.h"
#include "category/ToCodeValue.h"
#include "category/ToConditionValue.h"

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
    tmpl::category::Base<TCategoryTrait>()
{}

template<typename TCategoryTrait>
Category<TCategoryTrait>::Category(Category<TCategoryTrait> && mov) noexcept :
    tmpl::category::Base<TCategoryTrait>(std::move(mov))
{}

template<typename TCategoryTrait>
Category<TCategoryTrait>::~Category() noexcept
{}

template<typename TCategoryTrait>
const TCategoryTrait & Category<TCategoryTrait>::
    GetCategoryTrait() const noexcept
{
    return tmpl::category::Base<TCategoryTrait>::GetCategoryTrait();
}

template<typename TCategoryTrait>
TCategoryTrait & Category<TCategoryTrait>::GetCategoryTrait() noexcept
{
    return tmpl::category::Base<TCategoryTrait>::GetCategoryTrait();
}

template<typename TCategoryTrait>
template<typename _TCategoryTrait>
typename std::enable_if<std::is_base_of<error::intf::Exit, 
    _TCategoryTrait>::value, void>::type 
Category<TCategoryTrait>::Cleanup(int sig) noexcept
{
    static_cast<error::intf::Exit &>(this->GetCategoryTrait()).Cleanup(sig);
}

template<typename TCategoryTrait>
template<typename _TCategoryTrait>
typename std::enable_if<!std::is_base_of<error::intf::Exit, 
    _TCategoryTrait>::value, void>::type 
Category<TCategoryTrait>::Cleanup(int sig) noexcept
{}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::ValueType 
Category<TCategoryTrait>::Value() const noexcept
{
    return category::Value(this->GetCategoryTrait());
}

template<typename TCategoryTrait>
const typename Category<TCategoryTrait>::CharType * 
Category<TCategoryTrait>::Name() const noexcept
{
    return category::Name(this->GetCategoryTrait());
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::CodeValueType 
Category<TCategoryTrait>::DefaultCodeValue() const noexcept
{
    return category::DefaultCodeValue(this->GetCategoryTrait());
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::CodeType 
Category<TCategoryTrait>::DefaultCode() const noexcept
{
    return category::DefaultCode(this->GetCategoryTrait(),
        GetInstance());
}

template<typename TCategoryTrait>
template<typename _TCategoryTrait>
typename std::enable_if<category::has::mmbr::defn::type::
    CodeEnum<_TCategoryTrait>::Value, 
    typename Category<TCategoryTrait>::CodeType>::type
Category<TCategoryTrait>::
    DefaultCode(const CodeValueType & code) const noexcept
{
    return CodeType{code, GetInstance()}; 
}

template<typename TCategoryTrait>
template<typename _TCategoryTrait>
typename std::enable_if<!category::has::mmbr::defn::type::
    CodeEnum<_TCategoryTrait>::Value, 
    typename Category<TCategoryTrait>::CodeType>::type
Category<TCategoryTrait>::
    DefaultCode(const CodeValueType & code) const noexcept
{
    return CodeType{code, GetInstance()};
}

template<typename TCategoryTrait>
template<typename _TCategoryTrait>
typename std::enable_if<category::has::mmbr::defn::type::
    CodeEnum<_TCategoryTrait>::Value, 
    typename Category<TCategoryTrait>::CodeType>::type
Category<TCategoryTrait>::
    DefaultCode(const CodeSetValueType & code) const noexcept
{
    return {code};
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::ConditionValueType 
Category<TCategoryTrait>::DefaultConditionValue() const noexcept
{
    return category::DefaultConditionValue(this->GetCategoryTrait());
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::ConditionType 
Category<TCategoryTrait>::DefaultCondition() const noexcept
{
    return category::DefaultCondition(this->GetCategoryTrait(),
        category::DefaultCodeValue(this->GetCategoryTrait()), GetInstance());
}

template<typename TCategoryTrait>
template<typename _TCategoryTrait>
typename std::enable_if<category::has::mmbr::defn::type::
    ConditionEnum<_TCategoryTrait>::Value, 
    typename Category<TCategoryTrait>::ConditionType>::type
Category<TCategoryTrait>::
    DefaultCondition(const CodeValueType & code) const noexcept
{
    return category::DefaultCondition(this->GetCategoryTrait(), code, 
        GetInstance());
}

template<typename TCategoryTrait>
template<typename _TCategoryTrait>
typename std::enable_if<!category::has::mmbr::defn::type::
    ConditionEnum<_TCategoryTrait>::Value, 
    typename Category<TCategoryTrait>::ConditionType>::type
Category<TCategoryTrait>::
    DefaultCondition(const CodeValueType & code) const noexcept
{
    return category::DefaultCondition(this->GetCategoryTrait(), code, 
        GetInstance());
}

template<typename TCategoryTrait>
template<typename _TCategoryTrait>
typename std::enable_if<category::has::mmbr::defn::type::
    ConditionEnum<_TCategoryTrait>::Value, 
    typename Category<TCategoryTrait>::ConditionType>::type
Category<TCategoryTrait>::
    DefaultCondition(const CodeSetValueType & code) const noexcept
{
    return {code};
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::ConditionType 
Category<TCategoryTrait>::
    DefaultCondition(const CodeType & code) const noexcept
{
    return category::DefaultCondition(this->GetCategoryTrait(), code.Value(),
        GetInstance());
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::CodeValueType 
Category<TCategoryTrait>::
    ToCodeValue(const CodeSetValueType & code) const noexcept
{
    return category::ToCodeValue(this->GetCategoryTrait(), code);
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
    return category::Equivalent(this->GetCategoryTrait(), code, cond);
}

template<typename TCategoryTrait>
bool Category<TCategoryTrait>::Equivalent(const CodeType & code,
    const ConditionValueType & cond) const noexcept
{
    return category::Equivalent(this->GetCategoryTrait(), code, cond);
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::StringType 
Category<TCategoryTrait>::Message(const CodeType & code) const noexcept
{
    return category::Message<category::msg::tag::
        Code>(this->GetCategoryTrait(), code.Value());
}

template<typename TCategoryTrait>
typename Category<TCategoryTrait>::StringType 
Category<TCategoryTrait>::Message(const ConditionType & cond) const noexcept
{
    return category::Message<category::msg::tag::
        Condition>(this->GetCategoryTrait(), cond.Value());
}

template<typename TCategoryTrait>
const error::intf::Output & Category<TCategoryTrait>::
    operator>>(OutputType & out) const noexcept
{
    output::Operator(out, "category ", this->Name(), ":", this->Value());
    return *this;
}

} //!tmpl

} //!system

} //!error

} //!basic

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator==(const basic::error::system::tmpl::
    Category<TCategoryTraitA>& category_a, const basic::error::system::tmpl::
    Category<TCategoryTraitA>& category_b) noexcept
{
    return category_a.Value() == category_b.Value();
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator!=(const basic::error::system::tmpl::
    Category<TCategoryTraitA>& category_a, const basic::error::system::tmpl::
    Category<TCategoryTraitA>& category_b) noexcept
{
    return !(category_a == category_b);
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator<(const basic::error::system::tmpl::
    Category<TCategoryTraitA>& category_a, const basic::error::system::tmpl::
    Category<TCategoryTraitA>& category_b) noexcept
{
    return category_a.Value() < category_b.Value();
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator>(const basic::error::system::tmpl::
    Category<TCategoryTraitA>& category_a, const basic::error::system::tmpl::
    Category<TCategoryTraitA>& category_b) noexcept
{
    return category_b < category_a;
}

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEGORY_H_