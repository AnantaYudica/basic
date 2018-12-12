#ifndef BASIC_ERROR_SYSTEM_CONDITION_H__FORWARD_DECLARATION_
#define BASIC_ERROR_SYSTEM_CONDITION_H__FORWARD_DECLARATION_

namespace basic
{
namespace error
{
namespace system
{

template<typename TCategoryTrait>
class Condition;

} //!system

} //!error

} //!basic

#ifndef BASIC_ERROR_SYSTEM_CATEGORY_H__FORWARD_DECLARATION_

#include "Category.h"

#endif //!BASIC_ERROR_SYSTEM_CATEGORY_H__FORWARD_DECLARATION_

#ifndef BASIC_ERROR_SYSTEM_CODE_H__FORWARD_DECLARATION_

#include "Code.h"

#endif //!BASIC_ERROR_SYSTEM_CODE_H__FORWARD_DECLARATION_

#include "Condition.h"

#else //else BASIC_ERROR_SYSTEM_CONDITION_H__FORWARD_DECLARATION_

#ifndef BASIC_ERROR_SYSTEM_CONDITION_H_
#define BASIC_ERROR_SYSTEM_CONDITION_H_

#include "../../Error.h"
#include "../defn/type/Char.h"
#include "../defn/type/system/Condition/Value.h"
#include "../msg/String.h"
#include "category/has/func/DefaultCode.h"
#include "category/has/mmbr/defn/type/ConditionEnum.h"

#include <utility>
#include <type_traits>
#include <ostream>

namespace basic
{
namespace error
{
namespace system
{

template<typename TCategoryTrait>
class Condition
{
public:
    typedef TCategoryTrait CategoryTraitType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::system::condition::Value ValueType;
public:
    typedef msg::String StringType;
public:
    typedef Category<TCategoryTrait> CategoryType;
    typedef Code<TCategoryTrait> CodeType;
public:
    typedef typename CategoryType::ConditionSetValueType SetValueType;
private:
    template<typename _TCategoryTrait = TCategoryTrait>
    static constexpr typename std::enable_if<category::has::func::
        DefaultCode<_TCategoryTrait>::Value, ValueType>::type 
    DefaultConditionValue(const CategoryType& category) noexcept;
    template<typename _TCategoryTrait = TCategoryTrait>
    static constexpr typename std::enable_if<!category::has::func::
        DefaultCode<_TCategoryTrait>::Value, ValueType>::type 
    DefaultConditionValue(const CategoryType& category) noexcept;
private:
    ValueType m_value;
    CategoryType m_category;
    StringType m_message;
public:
    Condition() noexcept;
    Condition(const CodeType& code) noexcept;
    Condition(const SetValueType& cond_val) noexcept;
    template<typename _TCategoryTrait = TCategoryTrait, typename = typename
        std::enable_if<!std::is_same<typename _TCategoryTrait::ValueType,
        typename _TCategoryTrait::SetValueType>::value>::type>
    Condition(const ValueType& val) noexcept;
public:
    Condition(const Condition<TCategoryTrait>& cpy) noexcept;
    Condition(Condition<TCategoryTrait>&& mov) noexcept;
public:
    ~Condition() noexcept;
public:
    Condition<TCategoryTrait>& 
        operator=(const Condition<TCategoryTrait>& cpy) noexcept;
    Condition<TCategoryTrait>& 
        operator=(Condition<TCategoryTrait>&& mov) noexcept;
public:
    Condition<TCategoryTrait>& 
        operator=(const SetValueType& cond_val) noexcept;
    Condition<TCategoryTrait>& 
        operator=(const CodeType& code) noexcept;
public:
    void Assign(const SetValueType& cond_val) noexcept;
    void Assign(const CodeType& code) noexcept;
public:
    void Clear() noexcept;
public:
    ValueType Value() const noexcept;
public:
    const CategoryType& Category() const noexcept;
public:
    const CharType * Message() const noexcept;
public:
    operator bool() const noexcept;
};

template<typename TCategoryTrait>
template<typename _TCategoryTrait>
constexpr typename std::enable_if<category::has::func::
    DefaultCode<_TCategoryTrait>::Value, 
    typename Condition<TCategoryTrait>::ValueType>::type 
Condition<TCategoryTrait>::
    DefaultConditionValue(const CategoryType& category) noexcept
{
    return category.DefaultCondition().m_value;
}

template<typename TCategoryTrait>
template<typename _TCategoryTrait >
constexpr typename std::enable_if<!category::has::func::
    DefaultCode<_TCategoryTrait>::Value, 
    typename Condition<TCategoryTrait>::ValueType>::type 
Condition<TCategoryTrait>::
    DefaultConditionValue(const CategoryType& category) noexcept
{
    return 0;
}

template<typename TCategoryTrait>
Condition<TCategoryTrait>::Condition() noexcept :
    m_category(),
    m_value(DefaultConditionValue(this->m_category)),
    m_message(this->m_category.Message(*this))
{}

template<typename TCategoryTrait>
Condition<TCategoryTrait>::Condition(const CodeType& code) noexcept :
    m_category(),
    m_value(this->m_category.DefaultCondition(code).m_value),
    m_message(this->m_category.Message(*this))
{}

template<typename TCategoryTrait>
Condition<TCategoryTrait>::Condition(const SetValueType& cond_val) noexcept :
    m_category(),
    m_value(static_cast<ValueType>(cond_val)),
    m_message(this->m_category.Message(*this))
{}

template<typename TCategoryTrait>
template<typename _TCategoryTrai, typename>
Condition<TCategoryTrait>::Condition(const ValueType& val) noexcept :
    m_category(),
    m_value(val),
    m_message(this->m_category.Message(*this))
{}

template<typename TCategoryTrait>
Condition<TCategoryTrait>::Condition(const Condition<TCategoryTrait>& cpy) 
    noexcept :
        m_category(cpy.m_category),
        m_value(cpy.m_value),
        m_message(cpy.m_message)
{}

template<typename TCategoryTrait>
Condition<TCategoryTrait>::Condition(Condition<TCategoryTrait>&& mov) 
    noexcept :
        m_category(std::move(mov.m_category)),
        m_value(std::move(mov.m_value)),
        m_message(std::move(mov.m_message))
{}

template<typename TCategoryTrait>
Condition<TCategoryTrait>::~Condition() noexcept
{
    Clear();
}

template<typename TCategoryTrait>
Condition<TCategoryTrait>& 
Condition<TCategoryTrait>::operator=(const Condition<TCategoryTrait>& cpy) 
    noexcept
{
    this->m_value = cpy.m_value;
    this->m_message = cpy.m_message;
    return *this;
}
    
template<typename TCategoryTrait>
Condition<TCategoryTrait>& 
Condition<TCategoryTrait>::operator=(Condition<TCategoryTrait>&& mov) noexcept
{
    this->m_value = std::move(mov.m_value);
    this->m_message = std::move(mov.m_message);
    return *this;
}

template<typename TCategoryTrait>
Condition<TCategoryTrait>& 
Condition<TCategoryTrait>::operator=(const SetValueType& cond_val) noexcept
{
    this->m_value = static_cast<ValueType>(cond_val);
    this->m_message = this->m_category.Message(*this);
    return *this;
}

template<typename TCategoryTrait>
Condition<TCategoryTrait>& 
Condition<TCategoryTrait>::operator=(const CodeType& code) noexcept
{
    this->m_value = this->m_category.DefaultCondition(code).m_value;
    this->m_message = this->m_category.Message(*this);
    return *this;
}

template<typename TCategoryTrait>
void Condition<TCategoryTrait>::Assign(const SetValueType& cond_val) noexcept
{
    this->m_value = static_cast<ValueType>(cond_val);
    this->m_message = this->m_category.Message(*this);
}

template<typename TCategoryTrait>
void Condition<TCategoryTrait>::Assign(const CodeType& code) noexcept
{
    this->m_value = this->m_category.DefaultCondition(code).m_value;
    this->m_message = this->m_category.Message(*this);
}

template<typename TCategoryTrait>
void Condition<TCategoryTrait>::Clear() noexcept
{
    this->m_value = this->m_category.DefaultCondition().m_value;
    this->m_message = std::move(StringType());
}

template<typename TCategoryTrait>
typename Condition<TCategoryTrait>::ValueType 
Condition<TCategoryTrait>::Value() const noexcept
{
    return this->m_value;
}

template<typename TCategoryTrait>
const typename Condition<TCategoryTrait>::CategoryType& 
Condition<TCategoryTrait>::Category() const noexcept
{
    return this->m_category;
}

template<typename TCategoryTrait>
const char * Condition<TCategoryTrait>::Message() const noexcept
{
    return this->m_category.Message(*this);
}

template<typename TCategoryTrait>
Condition<TCategoryTrait>::operator bool() const noexcept
{
    return this->m_value != DefaultConditionValue(this->m_category);
}

} //!system

} //!error

} //!basic


template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator==(const basic::error::system::
    Condition<TCategoryTraitA>& cond_a, const basic::error::system::
    Condition<TCategoryTraitA>& cond_b) noexcept
{
    return cond_a.Category() == cond_b.Category() &&
        cond_a.Value() == cond_b.Value();
}

template<typename TCategoryTrait>
bool operator==(const basic::error::system::
    Condition<TCategoryTrait>& cond_a, const typename basic::error::system::
    Condition<TCategoryTrait>::ValueType& cond_b_val) noexcept
{
    return cond_a.Value() == cond_b_val;
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::category::has::mmbr::defn::type::
    ConditionEnum<TCategoryTrait>::Value, bool>::type
operator==(const basic::error::system::
    Condition<TCategoryTrait>& cond_a, const typename basic::error::system::
    Condition<TCategoryTrait>::SetValueType& cond_b_val)
{
    return cond_a.Value() == cond_b_val;
}

template<typename TCategoryTrait>
bool operator==(const typename basic::error::system::
    Condition<TCategoryTrait>::ValueType& cond_a_val, 
    const basic::error::system::Condition<TCategoryTrait>& cond_b) noexcept
{
    return cond_b == cond_a_val;
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::category::has::mmbr::defn::type::
    ConditionEnum<TCategoryTrait>::Value, bool>::type
operator==(const typename basic::error::system::
    Condition<TCategoryTrait>::SetValueType& cond_a_val, 
    const basic::error::system::Condition<TCategoryTrait>& cond_b)
{
    return cond_b == cond_a_val;
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator!=(const basic::error::system::
    Condition<TCategoryTraitA>& cond_a, const basic::error::system::
    Condition<TCategoryTraitA>& cond_b) noexcept
{
    return !(cond_a == cond_b);
}

template<typename TCategoryTrait>
bool operator!=(const basic::error::system::
    Condition<TCategoryTrait>& cond_a, const typename basic::error::system::
    Condition<TCategoryTrait>::ValueType& cond_b_val) noexcept
{
    return !(cond_a == cond_b_val);
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::category::has::mmbr::defn::type::
    ConditionEnum<TCategoryTrait>::Value, bool>::type
operator!=(const basic::error::system::
    Condition<TCategoryTrait>& cond_a, const typename basic::error::system::
    Condition<TCategoryTrait>::SetValueType& cond_b_val)
{
    return !(cond_a == cond_b_val);
}

template<typename TCategoryTrait>
bool operator!=(const typename basic::error::system::
    Condition<TCategoryTrait>::ValueType& cond_a_val, 
    const basic::error::system::Condition<TCategoryTrait>& cond_b) noexcept
{
    return !(cond_a_val == cond_b);
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::category::has::mmbr::defn::type::
    ConditionEnum<TCategoryTrait>::Value, bool>::type
operator!=(const typename basic::error::system::
    Condition<TCategoryTrait>::SetValueType& cond_a_val, 
    const basic::error::system::Condition<TCategoryTrait>& cond_b)
{
    return !(cond_a_val == cond_b);
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator<(const basic::error::system::
    Condition<TCategoryTraitA>& cond_a, const basic::error::system::
    Condition<TCategoryTraitA>& cond_b) noexcept
{
    return cond_a.Category() == cond_b.Category() &&
        cond_a.Value() < cond_b.Value();
}

template<typename TCategoryTrait>
bool operator<(const basic::error::system::
    Condition<TCategoryTrait>& cond_a, const typename basic::error::system::
    Condition<TCategoryTrait>::ValueType& cond_b_val) noexcept
{
    return cond_a.Value() < cond_b_val;
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::category::has::mmbr::defn::type::
    ConditionEnum<TCategoryTrait>::Value, bool>::type
operator<(const basic::error::system::
    Condition<TCategoryTrait>& cond_a, const typename basic::error::system::
    Condition<TCategoryTrait>::SetValueType& cond_b_val)
{
    return cond_a.Value() < cond_b_val;
}

template<typename TCategoryTrait>
bool operator<(const typename basic::error::system::
    Condition<TCategoryTrait>::ValueType& cond_a_val, 
    const basic::error::system::Condition<TCategoryTrait>& cond_b) noexcept
{
    return cond_a_val < cond_b.Value();
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::category::has::mmbr::defn::type::
    ConditionEnum<TCategoryTrait>::Value, bool>::type
operator<(const typename basic::error::system::
    Condition<TCategoryTrait>::SetValueType& cond_a_val, 
    const basic::error::system::Condition<TCategoryTrait>& cond_b)
{
    return cond_a_val < cond_b.Value();
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator>(const basic::error::system::
    Condition<TCategoryTraitA>& cond_a, const basic::error::system::
    Condition<TCategoryTraitA>& cond_b) noexcept
{
    return cond_a.Category() == cond_b.Category() &&
        cond_a.Value() > cond_b.Value();
}

template<typename TCategoryTrait>
bool operator>(const basic::error::system::
    Condition<TCategoryTrait>& cond_a, const typename basic::error::system::
    Condition<TCategoryTrait>::ValueType& cond_b_val) noexcept
{
    return cond_a.Value() > cond_b_val;
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::category::has::mmbr::defn::type::
    ConditionEnum<TCategoryTrait>::Value, bool>::type
operator>(const basic::error::system::
    Condition<TCategoryTrait>& cond_a, const typename basic::error::system::
    Condition<TCategoryTrait>::SetValueType& cond_b_val)
{
    return cond_a.Value() > cond_b_val;
}

template<typename TCategoryTrait>
bool operator>(const typename basic::error::system::
    Condition<TCategoryTrait>::ValueType& cond_a_val, 
    const basic::error::system::Condition<TCategoryTrait>& cond_b) noexcept
{
    return cond_a_val > cond_b.Value();
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::category::has::mmbr::defn::type::
    ConditionEnum<TCategoryTrait>::Value, bool>::type
operator>(const typename basic::error::system::
    Condition<TCategoryTrait>::SetValueType& cond_a_val, 
    const basic::error::system::Condition<TCategoryTrait>& cond_b)
{
    return cond_a_val > cond_b.Value();
}

template<typename TChar, typename TCharTraits, typename TCategoryTrait>
std::basic_ostream<TChar, TCharTraits>& operator<<(std::basic_ostream<TChar, 
    TCharTraits>& out, const basic::error::system::
    Condition<TCategoryTrait>& cond)
{
    out << cond.Message();
    return out;
}

#endif //!BASIC_ERROR_SYSTEM_CONDITION_H_

#endif //!BASIC_ERROR_SYSTEM_CONDITION_H__FORWARD_DECLARATION_
