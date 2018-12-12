#ifndef BASIC_ERROR_SYSTEM_CODE_H__FORWARD_DECLARATION_
#define BASIC_ERROR_SYSTEM_CODE_H__FORWARD_DECLARATION_

namespace basic
{
namespace error
{
namespace system
{

template<typename TCategoryTrait>
class Code;

} //!system

} //!error

} //!basic

#ifndef BASIC_ERROR_SYSTEM_CATEGORY_H__FORWARD_DECLARATION_

#include "Category.h"

#endif //!BASIC_ERROR_SYSTEM_CATEGORY_H__FORWARD_DECLARATION_

#ifndef BASIC_ERROR_SYSTEM_CONDITION_H__FORWARD_DECLARATION_

#include "Condition.h"

#endif //!BASIC_ERROR_SYSTEM_CONDITION_H__FORWARD_DECLARATION_

#include "Code.h"

#else //else BASIC_ERROR_SYSTEM_CODE_H__FORWARD_DECLARATION_

#ifndef BASIC_ERROR_SYSTEM_CODE_H_
#define BASIC_ERROR_SYSTEM_CODE_H_

#include "../../Error.h"
#include "../defn/type/Char.h"
#include "../defn/type/system/code/Value.h"
#include "../msg/String.h"
#include "category/has/func/DefaultCode.h"
#include "category/has/mmbr/defn/type/CodeEnum.h"

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
class Code
{
public:
    typedef TCategoryTrait CategoryTraitType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::system::code::Value ValueType;
public:
    typedef msg::String StringType;
public:
    typedef Category<TCategoryTrait> CategoryType;
    typedef Condition<TCategoryTrait> ConditionType;
public:
    typedef typename CategoryType::CodeSetValueType SetValueType;
private:
    template<typename _TCategoryTrait = TCategoryTrait>
    static constexpr typename std::enable_if<category::has::func::
        DefaultCode<_TCategoryTrait>::Value, ValueType>::type 
    DefaultCodeValue(const CategoryType& category) noexcept;
    template<typename _TCategoryTrait = TCategoryTrait>
    static constexpr typename std::enable_if<!category::has::func::
        DefaultCode<_TCategoryTrait>::Value, ValueType>::type 
    DefaultCodeValue(const CategoryType& category) noexcept;
private:
    ValueType m_value;
    CategoryType m_category;
    StringType m_message;
public:
    Code() noexcept;
    Code(const SetValueType& code_val) noexcept;
public:
    Code(const Code<TCategoryTrait>& cpy) noexcept;
    Code(Code<TCategoryTrait>&& mov) noexcept;
public:
    ~Code();
public:
    Code<TCategoryTrait>& operator=(const Code<TCategoryTrait>& cpy) noexcept;
    Code<TCategoryTrait>& operator=(Code<TCategoryTrait>&& mov) noexcept;
public:
    Code<TCategoryTrait>& operator=(const SetValueType& code_val) noexcept;
public:
    void Assign(const SetValueType& code_val) noexcept;
public:
    void Clear() noexcept;
public:
    ValueType Value() const noexcept;
public:
    const CategoryType& Category() const noexcept;
public:
    ConditionType DefaultCondition() const noexcept;
public:
    const CharType * Message() const noexcept;
public:
    operator bool() const noexcept;
};

template<typename TCategoryTrait>
template<typename _TCategoryTrait>
constexpr typename std::enable_if<category::has::func::
    DefaultCode<_TCategoryTrait>::Value, 
    typename Code<TCategoryTrait>::ValueType>::type 
Code<TCategoryTrait>::DefaultCodeValue(const CategoryType& category) noexcept
{
    return category.DefaultCode().m_value;
}

template<typename TCategoryTrait>
template<typename _TCategoryTrait >
constexpr typename std::enable_if<!category::has::func::
    DefaultCode<_TCategoryTrait>::Value, 
    typename Code<TCategoryTrait>::ValueType>::type 
Code<TCategoryTrait>::DefaultCodeValue(const CategoryType& category) noexcept
{
    return 0;
}

template<typename TCategoryTrait>
Code<TCategoryTrait>::Code() noexcept :
    m_category(),
    m_value(DefaultCodeValue(this->m_category)),
    m_message(this->m_category.Message(*this))
{}

template<typename TCategoryTrait>
Code<TCategoryTrait>::Code(const SetValueType& code_val) noexcept :
    m_category(),
    m_value(static_cast<ValueType>(code_val)),
    m_message(this->m_category.Message(*this))
{}

template<typename TCategoryTrait>
Code<TCategoryTrait>::Code(const Code<TCategoryTrait>& cpy) noexcept :
    m_category(cpy.m_category),
    m_value(cpy.m_value),
    m_message(cpy.m_message)
{}

template<typename TCategoryTrait>
Code<TCategoryTrait>::Code(Code<TCategoryTrait>&& mov) noexcept :
    m_category(std::move(mov.m_category)),
    m_value(std::move(mov.m_value)),
    m_message(std::move(mov.m_message))
{}

template<typename TCategoryTrait>
Code<TCategoryTrait>::~Code()
{
    Clear();
}

template<typename TCategoryTrait>
Code<TCategoryTrait>& Code<TCategoryTrait>::
    operator=(const Code<TCategoryTrait>& cpy) noexcept
{
    this->m_value = cpy.m_value;
    this->m_message = cpy.m_message;
    return *this;
}

template<typename TCategoryTrait>
Code<TCategoryTrait>& Code<TCategoryTrait>::
    operator=(Code<TCategoryTrait>&& mov) noexcept
{
    this->m_value = std::move(mov.m_value);
    this->m_message = std::move(mov.m_message);
    return *this;
}

template<typename TCategoryTrait>
Code<TCategoryTrait>& Code<TCategoryTrait>::
    operator=(const SetValueType& code_val) noexcept
{
    this->m_value = static_cast<ValueType>(code_val);
    this->m_message = this->m_category.Message(*this);
    return *this;
}

template<typename TCategoryTrait>
void Code<TCategoryTrait>::Assign(const SetValueType& code_val) noexcept
{
    this->m_value = static_cast<ValueType>(code_val);
    this->m_message = this->m_category.Message(*this);
}

template<typename TCategoryTrait>
void Code<TCategoryTrait>::Clear() noexcept
{
    this->m_value = DefaultCodeValue(this->m_category);
    this->m_message = std::move(StringType());
}

template<typename TCategoryTrait>
typename Code<TCategoryTrait>::ValueType 
Code<TCategoryTrait>::Value() const noexcept
{
    return this->m_value;
}

template<typename TCategoryTrait>
const typename Code<TCategoryTrait>::CategoryType& 
    Code<TCategoryTrait>::Category() const noexcept
{
    return this->m_category;
}

template<typename TCategoryTrait>
typename Code<TCategoryTrait>::ConditionType 
    Code<TCategoryTrait>::DefaultCondition() const noexcept
{
    return ConditionType(*this);
}

template<typename TCategoryTrait>
const typename Code<TCategoryTrait>::CharType * 
Code<TCategoryTrait>::Message() const noexcept
{
    return this->m_message.Value();
}

template<typename TCategoryTrait>
Code<TCategoryTrait>::operator bool() const noexcept
{
    return m_value != DefaultCodeValue(this->m_category);
}

} //!system

} //!error

} //!basic

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator==(const basic::error::system::
    Code<TCategoryTraitA>& code_a, const basic::error::system::
    Code<TCategoryTraitA>& code_b) noexcept
{
    return code_a.Category() == code_b.Category() &&
        code_a.Value() == code_b.Value();
}

template<typename TCategoryTrait>
bool operator==(const basic::error::system::
    Code<TCategoryTrait>& code_a, const typename basic::error::system::
    Code<TCategoryTrait>::ValueType& code_b_val) noexcept
{
    return code_a.Value() == code_b_val;
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::category::has::mmbr::defn::type::
    CodeEnum<TCategoryTrait>::Value, bool>::type
operator==(const basic::error::system::
    Code<TCategoryTrait>& code_a, const typename basic::error::system::
    Code<TCategoryTrait>::SetValueType& code_b_val)
{
    return code_a.Value() == code_b_val;
}

template<typename TCategoryTrait>
bool operator==(const typename basic::error::system::
    Code<TCategoryTrait>::ValueType& code_a_val, const basic::error::system::
    Code<TCategoryTrait>& code_b) noexcept
{
    return code_b == code_a_val;
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::category::has::mmbr::defn::type::
    CodeEnum<TCategoryTrait>::Value, bool>::type
operator==(const typename basic::error::system::
    Code<TCategoryTrait>::SetValueType& code_a_val, 
    const basic::error::system::Code<TCategoryTrait>& code_b)
{
    return code_b == code_a_val;
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator!=(const basic::error::system::
    Code<TCategoryTraitA>& code_a, const basic::error::system::
    Code<TCategoryTraitA>& code_b) noexcept
{
    return !(code_a == code_b);
}

template<typename TCategoryTrait>
bool operator!=(const basic::error::system::
    Code<TCategoryTrait>& code_a, const typename basic::error::system::
    Code<TCategoryTrait>::ValueType& code_b_val) noexcept
{
    return !(code_a == code_b_val);
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::category::has::mmbr::defn::type::
    CodeEnum<TCategoryTrait>::Value, bool>::type
operator!=(const basic::error::system::
    Code<TCategoryTrait>& code_a, const typename basic::error::system::
    Code<TCategoryTrait>::SetValueType& code_b_val)
{
    return !(code_a == code_b_val);
}

template<typename TCategoryTrait>
bool operator!=(const typename basic::error::system::
    Code<TCategoryTrait>::ValueType& code_a_val, const basic::error::system::
    Code<TCategoryTrait>& code_b) noexcept
{
    return !(code_a_val == code_b);
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::category::has::mmbr::defn::type::
    CodeEnum<TCategoryTrait>::Value, bool>::type
operator!=(const typename basic::error::system::
    Code<TCategoryTrait>::SetValueType& code_a_val, 
    const basic::error::system::Code<TCategoryTrait>& code_b)
{
    return !(code_a_val == code_b);
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator<(const basic::error::system::
    Code<TCategoryTraitA>& code_a, const basic::error::system::
    Code<TCategoryTraitA>& code_b) noexcept
{
    return code_a.Category() == code_b.Category() &&
        code_a.Value() < code_b.Value();
}

template<typename TCategoryTrait>
bool operator<(const basic::error::system::
    Code<TCategoryTrait>& code_a, const typename basic::error::system::
    Code<TCategoryTrait>::ValueType& code_b_val) noexcept
{
    return code_a.Value() < code_b_val;
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::category::has::mmbr::defn::type::
    CodeEnum<TCategoryTrait>::Value, bool>::type
operator<(const basic::error::system::
    Code<TCategoryTrait>& code_a, const typename basic::error::system::
    Code<TCategoryTrait>::SetValueType& code_b_val)
{
    return code_a.Value() < code_b_val;
}

template<typename TCategoryTrait>
bool operator<(const typename basic::error::system::
    Code<TCategoryTrait>::ValueType& code_a_val, const basic::error::system::
    Code<TCategoryTrait>& code_b) noexcept
{
    return code_a_val < code_b.Value();
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::category::has::mmbr::defn::type::
    CodeEnum<TCategoryTrait>::Value, bool>::type
operator<(const typename basic::error::system::
    Code<TCategoryTrait>::SetValueType& code_a_val, 
    const basic::error::system::Code<TCategoryTrait>& code_b)
{
    return code_a_val < code_b.Value();
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator>(const basic::error::system::
    Code<TCategoryTraitA>& code_a, const basic::error::system::
    Code<TCategoryTraitA>& code_b) noexcept
{
    return code_a.Category() == code_b.Category() &&
        code_a.Value() > code_b.Value();
}

template<typename TCategoryTrait>
bool operator>(const basic::error::system::
    Code<TCategoryTrait>& code_a, const typename basic::error::system::
    Code<TCategoryTrait>::ValueType& code_b_val) noexcept
{
    return code_a.Value() > code_b_val;
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::category::has::mmbr::defn::type::
    CodeEnum<TCategoryTrait>::Value, bool>::type
operator>(const basic::error::system::
    Code<TCategoryTrait>& code_a, const typename basic::error::system::
    Code<TCategoryTrait>::SetValueType& code_b_val)
{
    return code_a.Value() > code_b_val;
}

template<typename TCategoryTrait>
bool operator>(const typename basic::error::system::
    Code<TCategoryTrait>::ValueType& code_a_val, const basic::error::system::
    Code<TCategoryTrait>& code_b) noexcept
{
    return code_a_val > code_b.Value();
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::category::has::mmbr::defn::type::
    CodeEnum<TCategoryTrait>::Value, bool>::type
operator>(const typename basic::error::system::
    Code<TCategoryTrait>::SetValueType& code_a_val, 
    const basic::error::system::Code<TCategoryTrait>& code_b)
{
    return code_a_val > code_b.Value();
}

template<typename TChar, typename TCharTraits, typename TCategoryTrait>
std::basic_ostream<TChar, TCharTraits>& operator<<(std::basic_ostream<TChar, 
    TCharTraits>& out, const basic::error::system::Code<TCategoryTrait>& code)
{
    out << code.Message();
    return out;
}

#endif //!BASIC_ERROR_SYSTEM_CODE_H_

#endif //!BASIC_ERROR_SYSTEM_CODE_H__FORWARD_DECLARATION_
