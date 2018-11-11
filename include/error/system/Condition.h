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
#include "defn/type/Condition/Value.h"
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
    typedef system::defn::type::condition::Value ValueType;
public:
    typedef typename Category<TCategoryTrait> CategoryType;
    typedef typename Condition<TCategoryTrait> CodeType;
public:
    typedef typename CategoryType::ConditionSetValueType SetValueType;
public:
    ValueType m_value;
    CategoryType m_category;
public:
    Condition() noexcept;
    Condition(const CodeType& code) noexcept;
    Condition(const SetValueType& cond_val) noexcept;
public:
    Condition(const Condition<TCategoryTrait>& cpy) noexcept;
    Condition(Condition<TCategoryTrait>&& mov) noexcept;
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
    const char * Message() const noexcept;
public:
    operator bool() const noexcept;
};

template<typename TCategoryTrait>
Condition<TCategoryTrait>::Condition() noexcept :
    m_category(),
    m_value(m_category.DefaultCondition(m_category.DefaultCode()).m_value)
{}

template<typename TCategoryTrait>
Condition<TCategoryTrait>::Condition(const CodeType& code) noexcept :
    m_category(),
    m_value(m_category.DefaultCondition(code).m_value)
{}

template<typename TCategoryTrait>
Condition<TCategoryTrait>::Condition(const SetValueType& cond_val) noexcept :
    m_category(),
    m_value(cond_val)
{}

template<typename TCategoryTrait>
Condition<TCategoryTrait>::Condition(const Condition<TCategoryTrait>& cpy) 
    noexcept :
        m_category(cpy.m_category),
        m_value(cpy.m_value)
{}

template<typename TCategoryTrait>
Condition<TCategoryTrait>::Condition(Condition<TCategoryTrait>&& mov) 
    noexcept :
        m_category(std::move(mov.m_category)),
        m_value(std::move(mov.m_value))
{}

template<typename TCategoryTrait>
Condition<TCategoryTrait>& 
Condition<TCategoryTrait>::operator=(const Condition<TCategoryTrait>& cpy) 
    noexcept
{
    this->m_value = cpy.m_value;
    return *this;
}
    
template<typename TCategoryTrait>
Condition<TCategoryTrait>& 
Condition<TCategoryTrait>::operator=(Condition<TCategoryTrait>&& mov) noexcept
{
    this->m_value = std::move(mov.m_value);
    return *this;
}

template<typename TCategoryTrait>
Condition<TCategoryTrait>& 
Condition<TCategoryTrait>::operator=(const SetValueType& cond_val) noexcept
{
    this->m_value = cond_val;
    return *this;
}

template<typename TCategoryTrait>
Condition<TCategoryTrait>& 
Condition<TCategoryTrait>::operator=(const CodeType& code) noexcept
{
    this->m_value = this->m_category.DefaultCondition(code).m_value;
    return *this;
}

template<typename TCategoryTrait>
void Condition<TCategoryTrait>::Assign(const SetValueType& cond_val) noexcept
{
    this->m_value = cond_val;
}

template<typename TCategoryTrait>
void Condition<TCategoryTrait>::Assign(const CodeType& code) noexcept
{
    this->m_value = this->m_category.DefaultCondition(code).m_value;
}

template<typename TCategoryTrait>
void Condition<TCategoryTrait>::Clear() noexcept
{
    this->m_value = this->m_category.DefaultCondition().m_value;
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
    return this->m_value != this->m_category.DefaultCondition().m_value;
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
