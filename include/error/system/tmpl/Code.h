#ifndef BASIC_ERROR_SYSTEM_TMPL_CODE_H_
#define BASIC_ERROR_SYSTEM_TMPL_CODE_H_

#include "Code.defn.h"
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
Code<TCategoryTrait>::Code() noexcept :
    m_value(Category<TCategoryTrait>::GetInstance().DefaultCodeValue())
{}

template<typename TCategoryTrait>
Code<TCategoryTrait>::Code(const SetValueType & code) noexcept :
    m_value(Category<TCategoryTrait>::GetInstance().ToCodeValue(code))
{}

template<typename TCategoryTrait>
Code<TCategoryTrait>::Code(const Code<TCategoryTrait> & cpy) noexcept :
    m_value(cpy.m_value)
{}

template<typename TCategoryTrait>
Code<TCategoryTrait>::Code(Code<TCategoryTrait> && mov) noexcept :
    m_value(std::move(mov.m_value))
{}

template<typename TCategoryTrait>
Code<TCategoryTrait>::~Code()
{
    this->Clear();
}

template<typename TCategoryTrait>
Code<TCategoryTrait> & Code<TCategoryTrait>::
    operator=(const CodeType & cpy) noexcept
{
    this->m_value = cpy.Value();
    return *this;
}

template<typename TCategoryTrait>
Code<TCategoryTrait> & Code<TCategoryTrait>::
    operator=(CodeType && mov) noexcept
{
    this->m_value = mov.Value();
    mov.Clear();
    return *this;
}

template<typename TCategoryTrait>
Code<TCategoryTrait> & Code<TCategoryTrait>::
    operator=(const Code<TCategoryTrait> & cpy) noexcept
{
    this->m_value = cpy.m_value;
    return *this;
}
    
template<typename TCategoryTrait>
Code<TCategoryTrait> & Code<TCategoryTrait>::
    operator=(Code<TCategoryTrait> && mov) noexcept
{
    this->m_value = std::move(mov.m_value);
    mov.Clear();
    return *this;
}

template<typename TCategoryTrait>
template<typename _TCategoryTrait, typename>
Code<TCategoryTrait> & Code<TCategoryTrait>::
    operator=(const ValueType & code) noexcept
{
    this->m_value = code;
    return *this;
}

template<typename TCategoryTrait>
template<typename _TCategoryTrait, typename>
Code<TCategoryTrait> & Code<TCategoryTrait>::
    operator=(const SetValueType & code) noexcept
{
    this->m_value = Category<TCategoryTrait>::
        GetInstance().ToCodeValue(code); 
    return *this;
}

template<typename TCategoryTrait>
template<typename _TCategoryTrait, typename>
Code<TCategoryTrait> & Code<TCategoryTrait>::
    operator=(const ValueType & code) noexcept
{
    this->m_value = code;
    return *this;
} 

template<typename TCategoryTrait>
void Code<TCategoryTrait>::Clear() noexcept
{
    this->m_value = Category<TCategoryTrait>::GetInstance().DefaultCode();
}

template<typename TCategoryTrait>
typename Code<TCategoryTrait>::ValueType 
Code<TCategoryTrait>::Value() const noexcept
{
    return this->m_value;
}

template<typename TCategoryTrait>
const intf::Category & Code<TCategoryTrait>::Category() const noexcept
{
    return Category<TCategoryTrait>::GetInstance();
}

template<typename TCategoryTrait>
typename Code<TCategoryTrait>::ConditionType 
Code<TCategoryTrait>::DefaultCondition() const noexcept
{
    return Category<TCategoryTrait>::GetInstance().DefaultCondition(m_value);
}

template<typename TCategoryTrait>
typename Code<TCategoryTrait>::StringType 
Code<TCategoryTrait>::Message() const noexcept
{
    return Category<TCategoryTrait>::GetInstance().Message(*this);
}

template<typename TCategoryTrait>
const error::intf::Output & Code<TCategoryTrait>::
    operator>>(OutputType & out) const noexcept
{
    error::output::Operator(out, "code ", this->m_value),
    error::output::Operator(out, "msg ", this->Message()),
    return *this;
}

} //!tmpl

} //!system

} //!error

} //!basic

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator==(const basic::error::system::tmpl::
    Code<TCategoryTraitA>& code_a, const basic::error::system::tmpl::
    Code<TCategoryTraitA>& code_b) noexcept
{
    return code_a.Category() == code_b.Category() &&
        code_a.Value() == code_b.Value();
}

template<typename TCategoryTrait>
bool operator==(const basic::error::system::tmpl::
    Code<TCategoryTrait>& code_a, const typename basic::error::system::tmpl::
    Code<TCategoryTrait>::ValueType& code_b_val) noexcept
{
    return code_a.Value() == code_b_val;
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::tmpl::category::has::mmbr::defn::
    type::CodeEnum<TCategoryTrait>::Value, bool>::type
operator==(const basic::error::system::tmpl::
    Code<TCategoryTrait>& code_a, const typename basic::error::system::tmpl::
    Code<TCategoryTrait>::SetValueType& code_b_val)
{
    return code_a.Value() == code_b_val;
}

template<typename TCategoryTrait>
bool operator==(const typename basic::error::system::tmpl::
    Code<TCategoryTrait>::ValueType& code_a_val, const basic::error::system::
    tmpl::Code<TCategoryTrait>& code_b) noexcept
{
    return code_b == code_a_val;
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::tmpl::category::has::mmbr::defn::
    type::CodeEnum<TCategoryTrait>::Value, bool>::type
operator==(const typename basic::error::system::tmpl::
    Code<TCategoryTrait>::SetValueType& code_a_val, 
    const basic::error::system::tmpl::Code<TCategoryTrait>& code_b)
{
    return code_b == code_a_val;
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator!=(const basic::error::system::tmpl::
    Code<TCategoryTraitA>& code_a, const basic::error::system::tmpl::
    Code<TCategoryTraitA>& code_b) noexcept
{
    return !(code_a == code_b);
}

template<typename TCategoryTrait>
bool operator!=(const basic::error::system::tmpl::
    Code<TCategoryTrait>& code_a, const typename basic::error::system::tmpl::
    Code<TCategoryTrait>::ValueType& code_b_val) noexcept
{
    return !(code_a == code_b_val);
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::tmpl::category::has::mmbr::defn::
    type::CodeEnum<TCategoryTrait>::Value, bool>::type
operator!=(const basic::error::system::tmpl::
    Code<TCategoryTrait>& code_a, const typename basic::error::system::tmpl::
    Code<TCategoryTrait>::SetValueType& code_b_val)
{
    return !(code_a == code_b_val);
}

template<typename TCategoryTrait>
bool operator!=(const typename basic::error::system::tmpl::
    Code<TCategoryTrait>::ValueType& code_a_val, const basic::error::system::
    tmpl::Code<TCategoryTrait>& code_b) noexcept
{
    return !(code_a_val == code_b);
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::tmpl::category::has::mmbr::defn::
    type::CodeEnum<TCategoryTrait>::Value, bool>::type
operator!=(const typename basic::error::system::tmpl::
    Code<TCategoryTrait>::SetValueType& code_a_val, 
    const basic::error::system::tmpl::Code<TCategoryTrait>& code_b)
{
    return !(code_a_val == code_b);
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator<(const basic::error::system::tmpl::
    Code<TCategoryTraitA>& code_a, const basic::error::system::tmpl::
    Code<TCategoryTraitA>& code_b) noexcept
{
    return code_a.Category() == code_b.Category() &&
        code_a.Value() < code_b.Value();
}

template<typename TCategoryTrait>
bool operator<(const basic::error::system::tmpl::
    Code<TCategoryTrait>& code_a, const typename basic::error::system::tmpl::
    Code<TCategoryTrait>::ValueType& code_b_val) noexcept
{
    return code_a.Value() < code_b_val;
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::tmpl::category::has::mmbr::defn::
    type::CodeEnum<TCategoryTrait>::Value, bool>::type
operator<(const basic::error::system::tmpl::
    Code<TCategoryTrait>& code_a, const typename basic::error::system::tmpl::
    Code<TCategoryTrait>::SetValueType& code_b_val)
{
    return code_a.Value() < code_b_val;
}

template<typename TCategoryTrait>
bool operator<(const typename basic::error::system::tmpl::
    Code<TCategoryTrait>::ValueType& code_a_val, const basic::error::system::
    tmpl::Code<TCategoryTrait>& code_b) noexcept
{
    return code_a_val < code_b.Value();
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::tmpl::category::has::mmbr::defn::
    type::CodeEnum<TCategoryTrait>::Value, bool>::type
operator<(const typename basic::error::system::tmpl::
    Code<TCategoryTrait>::SetValueType& code_a_val, 
    const basic::error::system::tmpl::Code<TCategoryTrait>& code_b)
{
    return code_a_val < code_b.Value();
}

template<typename TCategoryTraitA, typename TCategoryTraitB>
bool operator>(const basic::error::system::tmpl::
    Code<TCategoryTraitA>& code_a, const basic::error::system::tmpl::
    Code<TCategoryTraitA>& code_b) noexcept
{
    return code_a.Category() == code_b.Category() &&
        code_a.Value() > code_b.Value();
}

template<typename TCategoryTrait>
bool operator>(const basic::error::system::tmpl::
    Code<TCategoryTrait>& code_a, const typename basic::error::system::tmpl::
    Code<TCategoryTrait>::ValueType& code_b_val) noexcept
{
    return code_a.Value() > code_b_val;
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::tmpl::category::has::mmbr::defn::
    type::CodeEnum<TCategoryTrait>::Value, bool>::type
operator>(const basic::error::system::tmpl::
    Code<TCategoryTrait>& code_a, const typename basic::error::system::tmpl::
    Code<TCategoryTrait>::SetValueType& code_b_val)
{
    return code_a.Value() > code_b_val;
}

template<typename TCategoryTrait>
bool operator>(const typename basic::error::system::tmpl::
    Code<TCategoryTrait>::ValueType& code_a_val, const basic::error::system::
    tmpl::Code<TCategoryTrait>& code_b) noexcept
{
    return code_a_val > code_b.Value();
}

template<typename TCategoryTrait>
typename std::enable_if<basic::error::system::tmpl::category::has::mmbr::defn::
    type::CodeEnum<TCategoryTrait>::Value, bool>::type
operator>(const typename basic::error::system::tmpl::
    Code<TCategoryTrait>::SetValueType& code_a_val, 
    const basic::error::system::tmpl::Code<TCategoryTrait>& code_b)
{
    return code_a_val > code_b.Value();
}

#endif //!BASIC_ERROR_SYSTEM_TMPL_CODE_H_
