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
#include "defn/type/Code/Value.h"
#include "category/has/mmbr/defn/type/CodeEnum.h"

#include <cstdint>
#include <type_traits>
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
    typedef system::defn::type::code::Value ValueType;
public:
    typedef typename Category<TCategoryTrait> CategoryType;
    typedef typename Condition<TCategoryTrait> ConditionType;
public:
    typedef typename CategoryType::CodeSetValueType CodeSetValueType;
public:
    ValueType m_value;
    CategoryType m_category;
public:
    Code() noexcept;
    Code(const CodeSetValueType& code_val) noexcept;
public:
    Code(const Code<TCategoryTrait>& cpy) noexcept;
    Code(Code<TCategoryTrait>&& mov) noexcept;
public:
    ~Code();
public:
    Code<TCategoryTrait>& operator=(const Code<TCategoryTrait>& cpy) noexcept;
    Code<TCategoryTrait>& operator=(Code<TCategoryTrait>&& mov) noexcept;
public:
    Code<TCategoryTrait>& operator=(const CodeSetValueType& code_val) noexcept;
public:
    void Assign(const CodeSetValueType& code_val) noexcept;
public:
    void Clear() noexcept;
public:
    ValueType Value() const noexcept;
public:
    const CategoryType& Category() const noexcept;
public:
    ConditionType DefaultCondition() const noexcept;
public:
    const char * Message() const noexcept;
public:
    operator bool() const noexcept;
};

template<typename TCategoryTrait>
Code<TCategoryTrait>::Code() noexcept :
    m_category(),
    m_value(m_category.DefaultCode())
{}

template<typename TCategoryTrait>
Code<TCategoryTrait>::Code(const CodeSetValueType& code_val) noexcept :
    m_category(),
    m_value(code_val)
{}

template<typename TCategoryTrait>
Code<TCategoryTrait>::Code(const Code<TCategoryTrait>& cpy) noexcept :
    m_category(cpy.m_category),
    m_value(cpy.m_value)
{}

template<typename TCategoryTrait>
Code<TCategoryTrait>::Code(Code<TCategoryTrait>&& mov) noexcept :
    m_category(std::move(mov.m_category)),
    m_value(std::move(mov.m_value))
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
    return *this;
}

template<typename TCategoryTrait>
Code<TCategoryTrait>& Code<TCategoryTrait>::
    operator=(Code<TCategoryTrait>&& mov) noexcept
{
    this->m_value = std::move(mov.m_value);
    return *this;
}

template<typename TCategoryTrait>
Code<TCategoryTrait>& Code<TCategoryTrait>::
    operator=(const CodeSetValueType& code_val) noexcept
{
    this->m_value = code_val;
    return *this;
}

template<typename TCategoryTrait>
void Code<TCategoryTrait>::Assign(const CodeSetValueType& code_val) noexcept
{
    this->m_value = code_val;
}

template<typename TCategoryTrait>
void Code<TCategoryTrait>::Clear() noexcept
{
    this->m_value = m_category.DefaultCode();
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
    return m_category;
}

template<typename TCategoryTrait>
typename Code<TCategoryTrait>::ConditionType 
    Code<TCategoryTrait>::DefaultCondition() const noexcept
{
    return ConditionType(*this);
}

template<typename TCategoryTrait>
const char * Code<TCategoryTrait>::Message() const noexcept
{
    return m_category.Message(*this);
}

template<typename TCategoryTrait>
Code<TCategoryTrait>::operator bool() const noexcept
{
    return m_value != m_category.DefaultCode();
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
    Code<TCategoryTrait>::EnumType& code_b_emum)
{
    return code_a.Value() == code_b_emum;
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
    Code<TCategoryTrait>::EnumType& code_a_emum, const basic::error::system::
    Code<TCategoryTrait>& code_b)
{
    return code_b == code_a_emum;
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
    Code<TCategoryTrait>::EnumType& code_b_emum)
{
    return !(code_a == code_b_emum);
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
    Code<TCategoryTrait>::EnumType& code_a_emum, const basic::error::system::
    Code<TCategoryTrait>& code_b)
{
    return !(code_a_emum == code_b);
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
    Code<TCategoryTrait>::EnumType& code_b_emum)
{
    return code_a.Value() < code_b_emum;
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
    Code<TCategoryTrait>::EnumType& code_a_emum, const basic::error::system::
    Code<TCategoryTrait>& code_b)
{
    return code_a_emum < code_b.Value();
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
    Code<TCategoryTrait>::EnumType& code_b_emum)
{
    return code_a.Value() > code_b_emum;
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
    Code<TCategoryTrait>::EnumType& code_a_emum, const basic::error::system::
    Code<TCategoryTrait>& code_b)
{
    return code_a_emum > code_b.Value();
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
