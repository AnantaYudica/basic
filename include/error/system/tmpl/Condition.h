#ifndef BASIC_ERROR_SYSTEM_CONDITION_T_H_
#define BASIC_ERROR_SYSTEM_CONDITION_T_H_

#include "Condition.defn.h" 
#include "Category.defn.h"

#include "../../output/Operator.h"

#include <utility>
#include <type_traits>

namespace basic
{
namespace error
{
namespace system
{
namespace tmpl
{

template<typename TCategoryTrait>
Condition<TCategoryTrait>::Condition() noexcept :
    m_value(Category<TCategoryTrait>::GetInstance().DefaultConditionValue())
{}

template<typename TCategoryTrait>
Condition<TCategoryTrait>::Condition(const CodeTemplateType & code) noexcept :
    m_value(Category<TCategoryTrait>::
        GetInstance().DefaultCondition(code.Value()))
{}

template<typename TCategoryTrait>
Condition<TCategoryTrait>::Condition(const SetValueType & cond) noexcept :
    m_value(Category<TCategoryTrait>::GetInstance().ToConditionValue(cond))
{}

template<typename TCategoryTrait>
Condition<TCategoryTrait>::
    Condition(const Condition<TCategoryTrait> & cpy) noexcept :
        m_value(cpy.m_value)
{}

template<typename TCategoryTrait>
Condition<TCategoryTrait>::
    Condition(Condition<TCategoryTrait> && mov) noexcept :
        m_value(std::move(mov.m_value))
{
    mov.Clear();
}

template<typename TCategoryTrait>
Condition<TCategoryTrait>::~Condition() noexcept
{
    this->Clear();
}

template<typename TCategoryTrait>
Condition<TCategoryTrait> & Condition<TCategoryTrait>::
    operator=(const ConditionType & cond) noexcept
{
    this->m_value = cond.Value();
    return *this;
}

template<typename TCategoryTrait>
Condition<TCategoryTrait> & Condition<TCategoryTrait>::
    operator=(ConditionType && cond) noexcept
{
    this->m_value = cond.Value()
    cond.Clear();
    return *this;

}

template<typename TCategoryTrait>
Condition<TCategoryTrait> & Condition<TCategoryTrait>::
    operator=(const Condition<TCategoryTrait> & cpy) noexcept
{
    this->m_value = cpy.m_value;
    return *this;
}

template<typename TCategoryTrait>
Condition<TCategoryTrait> & Condition<TCategoryTrait>::
    operator=(Condition<TCategoryTrait> && mov) noexcept
{
    this->m_value = std::move(mov.m_value);
    mov.Clear();
    return *this;
}

template<typename TCategoryTrait>
template<typename _TCategoryTrait,typename>
Condition<TCategoryTrait> & Condition<TCategoryTrait>::
    operator=(const ValueType & cond) noexcept
{
    this->m_value = cond;
    return *this;
}

template<typename TCategoryTrait>
template<typename _TCategoryTrait, typename>
Condition<TCategoryTrait> & Condition<TCategoryTrait>::
    operator=(const SetValueType & cond) noexcept
{
    this->m_value = Category<TCategoryTrait>::
        GetInstance().ToConditionValue(cond);
    return *this;
}

template<typename TCategoryTrait>
template<typename _TCategoryTrait, typename>
Condition<TCategoryTrait> & Condition<TCategoryTrait>::
    operator=(const ValueType & cond) noexcept
{
    this->m_value = cond;
    return *this;
}

template<typename TCategoryTrait>
Condition<TCategoryTrait> & Condition<TCategoryTrait>::
    operator=(const CodeTemplateType & code) noexcept
{
    this->m_value = Category<TCategoryTrait>::
        GetInstance().DefaultCondition(code.Value());
    return *this;
}

template<typename TCategoryTrait>
void Condition<TCategoryTrait>::Clear() noexcept
{
    this->m_value = Category<TCategoryTrait>::
        GetInstance().DefaultConditionValue();
}

template<typename TCategoryTrait>
typename Condition<TCategoryTrait>::ValueType 
Condition<TCategoryTrait>::Value() const noexcept
{
    return this->m_value;
}

template<typename TCategoryTrait>
const typename Condition<TCategoryTrait>::CategoryInterfaceType & 
Condition<TCategoryTrait>::Category() const noexcept
{
    return Category<TCategoryTrait>::GetInstance();
}

template<typename TCategoryTrait>
typename Condition<TCategoryTrait>::StringType 
Condition<TCategoryTrait>::Message() const noexcept
{
    return Category<TCategoryTrait>::GetInstance().Message(*this);
}

template<typename TCategoryTrait>
const error::intf::Output & 
Condition<TCategoryTrait>::operator>>(OutputType & out) const noexcept
{
    error::output::Operator(out, "cond ", this->m_value),
    error::output::Operator(out, "msg ", this->Message()),
    return *this;
}

} //!tmpl

} //!system

} //!error

} //!basic


template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator==(const basic::error::system::tmpl::
    Condition<TCategoryTraitA>& cond_a, const basic::error::system::tmpl::
    Condition<TCategoryTraitB>& cond_b) noexcept
{
    return cond_a.Category() == cond_b.Category() &&
        cond_a.Value() == cond_b.Value();
}

template<typename TCategoryTrait>
bool operator==(const basic::error::system::tmpl::
    Condition<TCategoryTrait>& cond_a, const typename basic::error::system::
    tmpl::Condition<TCategoryTrait>::ValueType& cond_b_val) noexcept
{
    return cond_a.Value() == cond_b_val;
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::tmpl::category::has::mmbr::defn::
    type::ConditionEnum<TCategoryTrait>::Value, bool>::type
operator==(const basic::error::system::tmpl::
    Condition<TCategoryTrait>& cond_a, const typename basic::error::system::
    tmpl::Condition<TCategoryTrait>::SetValueType& cond_b_val)
{
    return cond_a.Value() == cond_b_val;
}

template<typename TCategoryTrait>
bool operator==(const typename basic::error::system::tmpl::
    Condition<TCategoryTrait>::ValueType& cond_a_val, const basic::error::
    system::tmpl::Condition<TCategoryTrait>& cond_b) noexcept
{
    return cond_b == cond_a_val;
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::tmpl::category::has::mmbr::defn::
    type::ConditionEnum<TCategoryTrait>::Value, bool>::type
operator==(const typename basic::error::system::tmpl::
    Condition<TCategoryTrait>::SetValueType& cond_a_val, 
    const basic::error::system::tmpl::Condition<TCategoryTrait>& cond_b)
{
    return cond_b == cond_a_val;
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator!=(const basic::error::system::tmpl::
    Condition<TCategoryTraitA>& cond_a, const basic::error::system::tmpl::
    Condition<TCategoryTraitB>& cond_b) noexcept
{
    return !(cond_a == cond_b);
}

template<typename TCategoryTrait>
bool operator!=(const basic::error::system::tmpl::
    Condition<TCategoryTrait>& cond_a, const typename basic::error::system::
    tmpl::Condition<TCategoryTrait>::ValueType& cond_b_val) noexcept
{
    return !(cond_a == cond_b_val);
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::tmpl::category::has::mmbr::defn::
    type::ConditionEnum<TCategoryTrait>::Value, bool>::type
operator!=(const basic::error::system::tmpl::
    Condition<TCategoryTrait>& cond_a, const typename basic::error::system::
    tmpl::Condition<TCategoryTrait>::SetValueType& cond_b_val)
{
    return !(cond_a == cond_b_val);
}

template<typename TCategoryTrait>
bool operator!=(const typename basic::error::system::tmpl::
    Condition<TCategoryTrait>::ValueType& cond_a_val, const basic::error::
    system::tmpl::Condition<TCategoryTrait>& cond_b) noexcept
{
    return !(cond_a_val == cond_b);
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::tmpl::category::has::mmbr::defn::
    type::ConditionEnum<TCategoryTrait>::Value, bool>::type
operator!=(const typename basic::error::system::tmpl::
    Condition<TCategoryTrait>::SetValueType& cond_a_val, 
    const basic::error::system::tmpl::Condition<TCategoryTrait>& cond_b)
{
    return !(cond_a_val == cond_b);
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator<(const basic::error::system::tmpl::
    Condition<TCategoryTraitA>& cond_a, const basic::error::system::tmpl::
    Condition<TCategoryTraitB>& cond_b) noexcept
{
    return cond_a.Category() == cond_b.Category() &&
        cond_a.Value() < cond_b.Value();
}

template<typename TCategoryTrait>
bool operator<(const basic::error::system::tmpl::
    Condition<TCategoryTrait>& cond_a, const typename basic::error::system::
    tmpl::Condition<TCategoryTrait>::ValueType& cond_b_val) noexcept
{
    return cond_a.Value() < cond_b_val;
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::tmpl::category::has::mmbr::defn::
    type::ConditionEnum<TCategoryTrait>::Value, bool>::type
operator<(const basic::error::system::tmpl::
    Condition<TCategoryTrait>& cond_a, const typename basic::error::system::
    tmpl::Condition<TCategoryTrait>::SetValueType& cond_b_val)
{
    return cond_a.Value() < cond_b_val;
}

template<typename TCategoryTrait>
bool operator<(const typename basic::error::system::tmpl::
    Condition<TCategoryTrait>::ValueType& cond_a_val, const basic::error::
    system::tmpl::Condition<TCategoryTrait>& cond_b) noexcept
{
    return cond_a_val < cond_b.Value();
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::tmpl::category::has::mmbr::defn::
    type::ConditionEnum<TCategoryTrait>::Value, bool>::type
operator<(const typename basic::error::system::tmpl::
    Condition<TCategoryTrait>::SetValueType& cond_a_val, 
    const basic::error::system::tmpl::Condition<TCategoryTrait>& cond_b)
{
    return cond_a_val < cond_b.Value();
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator>(const basic::error::system::tmpl::
    Condition<TCategoryTraitA>& cond_a, const basic::error::system::tmpl::
    Condition<TCategoryTraitB>& cond_b) noexcept
{
    return cond_a.Category() == cond_b.Category() &&
        cond_a.Value() > cond_b.Value();
}

template<typename TCategoryTrait>
bool operator>(const basic::error::system::tmpl::
    Condition<TCategoryTrait>& cond_a, const typename basic::error::system::
    tmpl::Condition<TCategoryTrait>::ValueType& cond_b_val) noexcept
{
    return cond_a.Value() > cond_b_val;
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::tmpl::category::has::mmbr::defn::
    type::ConditionEnum<TCategoryTrait>::Value, bool>::type
operator>(const basic::error::system::tmpl::
    Condition<TCategoryTrait>& cond_a, const typename basic::error::system::
    tmpl::Condition<TCategoryTrait>::SetValueType& cond_b_val)
{
    return cond_a.Value() > cond_b_val;
}

template<typename TCategoryTrait>
bool operator>(const typename basic::error::system::tmpl::
    Condition<TCategoryTrait>::ValueType& cond_a_val, const basic::error::
    system::tmpl::Condition<TCategoryTrait>& cond_b) noexcept
{
    return cond_a_val > cond_b.Value();
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::tmpl::category::has::mmbr::defn::
    type::ConditionEnum<TCategoryTrait>::Value, bool>::type
operator>(const typename basic::error::system::tmpl::
    Condition<TCategoryTrait>::SetValueType& cond_a_val, 
    const basic::error::system::tmpl::Condition<TCategoryTrait>& cond_b)
{
    return cond_a_val > cond_b.Value();
}

#endif //!BASIC_ERROR_SYSTEM_CONDITION_T_H_
