#ifndef BASIC_ERROR_SYSTEM_CODE_H_
#define BASIC_ERROR_SYSTEM_CODE_H_

#include "Code.defn.h"

#include "make/Category.h"
#include "make/code/Value.h"
#include "../defn/type/system/code/Value.h"
#include "../defn/func/output/Operator.h"
#include "code/has/Enum.h"

#include <utility>
#include <type_traits>

namespace basic
{
namespace error
{
namespace system
{

template<typename TCodeEnum>
inline Code::Code(const TCodeEnum & code) noexcept :
    m_value(system::make::code::Value(code)),
    m_categ(const_cast<CategoryType *>(&system::make::Category(code))),
    m_message(std::move(m_categ->Message(*this)))
{}

inline Code::Code(const ValueType & code, 
    const CategoryType & categ) noexcept :
        m_value(code),
        m_categ(const_cast<CategoryType *>(&categ)),
        m_message(std::move(m_categ->Message(*this)))
{}

inline Code::Code(const Code & cpy) noexcept :
    m_value(cpy.m_value),
    m_categ(cpy.m_categ),
    m_message(cpy.m_message)
{}

inline Code::Code(Code && mov) noexcept :
    m_value(std::move(mov.m_value)),
    m_categ(std::move(mov.m_categ)),
    m_message(std::move(mov.m_message))
{
    mov.Clear();
}

inline Code::~Code() noexcept
{}

inline Code & Code::operator=(const Code & cpy) noexcept
{
    this->m_value = cpy.m_value;
    this->m_categ = cpy.m_categ;
    this->m_message = cpy.m_message;
    return *this;
}

inline Code & Code::operator=(Code && mov) noexcept
{
    this->m_value = std::move(mov.m_value);
    this->m_categ = std::move(mov.m_categ);
    this->m_message = std::move(mov.m_message);
    mov.Clear();
    return *this;
}

template<typename TCodeEnum>
inline Code & Code::operator=(const TCodeEnum & code) noexcept
{
    this->m_value = system::make::code::Value(code);
    this->m_categ = const_cast<CategoryType *>(&system::make::
        Category(code));
    this->m_message = std::move(m_categ->Message(*this));
    return *this;
}

inline void Code::Assign(const ValueType & code,
    const CategoryType & categ) noexcept
{
    this->m_value = code;
    this->m_categ = const_cast<CategoryType *>(&categ);
    this->m_message = std::move(m_categ->Message(*this));
}

inline void Code::Clear() noexcept
{
    this->m_value = this->m_categ->DefaultCode().Value();
    this->m_message = std::move(m_categ->Message(*this));
}

inline typename Code::ValueType Code::Value() const noexcept
{
    return this->m_value;
}

inline const typename Code::CategoryType & 
Code::Category() const noexcept
{
    return *this->m_categ;
}

inline typename Code::ConditionType 
Code::DefaultCondition() const noexcept
{
    return this->m_categ->DefaultCondition(*this);
}

inline const typename Code::CharType * Code::Message() const noexcept
{
    return this->m_message.Value();
}

inline const error::intf::Output & 
Code::operator>>(OutputType & out) const noexcept
{
    error::defn::func::output::Operator(out, "code ", this->m_value);
    error::defn::func::output::Operator(out, "msg ", this->Message());
    return *this;
}

inline void Code::Cleanup(int sig) noexcept
{
    static_cast<error::intf::Exit &>(this->m_message).Cleanup(sig);
}

} //!system

} //!error

} //!basic

inline bool operator==(const basic::error::system::Code & code_a, 
    const basic::error::system::Code & code_b) noexcept
{
    return code_a.Category() == code_b.Category() &&
        code_a.Value() == code_b.Value();
}

inline bool operator==(const basic::error::system::Code & code_a, 
    const basic::error::defn::type::system::code::Value & code_b) noexcept
{
    return code_a.Value() == code_b;
}

template<typename TCodeEnum>
inline typename std::enable_if<basic::error::system::code::has::
    Enum<TCodeEnum>::Value, bool>::type 
operator==(const basic::error::system::Code & code_a, 
    const TCodeEnum & code_b) noexcept
{
    return code_a.Category() == basic::error::system::make::Category(code_b) &&
        code_a.Value() == basic::error::system::make::code::Value(code_b);
}

inline bool operator==(const basic::error::defn::type::system::code::
    Value & code_a, const basic::error::system::Code & code_b) noexcept
{
    return code_b == code_a;
}

template<typename TCodeEnum>
inline typename std::enable_if<basic::error::system::code::has::
    Enum<TCodeEnum>::Value, bool>::type 
operator==(const basic::error::defn::type::system::code::Value & code_a, 
    const TCodeEnum & code_b) noexcept
{
    return code_a == basic::error::system::make::code::Value(code_b);
}

template<typename TCodeEnum>
inline typename std::enable_if<basic::error::system::code::has::
    Enum<TCodeEnum>::Value, bool>::type 
operator==(const TCodeEnum & code_a, 
    const basic::error::system::Code & code_b) noexcept
{
    return code_b == code_a;
}

template<typename TCodeEnum>
inline typename std::enable_if<basic::error::system::code::has::
    Enum<TCodeEnum>::Value, bool>::type 
operator==(const TCodeEnum & code_a,
    const basic::error::defn::type::system::code::Value & code_b) noexcept
{
    return code_a == code_b;
}

inline bool operator!=(const basic::error::system::Code & code_a, 
    const basic::error::system::Code & code_b) noexcept
{
    return !(code_a == code_b);
}

inline bool operator!=(const basic::error::system::Code & code_a, 
    const basic::error::defn::type::system::code::Value & code_b) noexcept
{
    return !(code_a == code_b);
}

template<typename TCodeEnum>
inline typename std::enable_if<basic::error::system::code::has::
    Enum<TCodeEnum>::Value, bool>::type 
operator!=(const basic::error::system::Code & code_a, 
    const TCodeEnum & code_b) noexcept
{
    return !(code_a == code_b);
}

inline bool operator!=(const basic::error::defn::type::system::code::
    Value & code_a, const basic::error::system::Code & code_b) noexcept
{
    return !(code_a == code_b);
}

template<typename TCodeEnum>
inline typename std::enable_if<basic::error::system::code::has::
    Enum<TCodeEnum>::Value, bool>::type 
operator!=(const basic::error::defn::type::system::code::Value & code_a, 
    const TCodeEnum & code_b) noexcept
{
    return !(code_a == code_b);
}

template<typename TCodeEnum>
inline typename std::enable_if<basic::error::system::code::has::
    Enum<TCodeEnum>::Value, bool>::type 
operator!=(const TCodeEnum & code_a, 
    const basic::error::system::Code & code_b) noexcept
{
    return !(code_a == code_b);
}

template<typename TCodeEnum>
inline typename std::enable_if<basic::error::system::code::has::
    Enum<TCodeEnum>::Value, bool>::type 
operator!=(const TCodeEnum & code_a, 
    const basic::error::defn::type::system::code::Value & code_b) noexcept
{
    return !(code_a == code_b);
}

inline bool operator<(const basic::error::system::Code & code_a, 
    const basic::error::system::Code & code_b) noexcept
{
    return code_a.Category() == code_b.Category() &&
        code_a.Value() < code_b.Value();
}

inline bool operator<(const basic::error::system::Code & code_a, 
    const basic::error::defn::type::system::code::Value & code_b) noexcept
{
    return code_a.Value() < code_b;
}

template<typename TCodeEnum>
inline typename std::enable_if<basic::error::system::code::has::
    Enum<TCodeEnum>::Value, bool>::type 
operator<(const basic::error::system::Code & code_a, 
    const TCodeEnum & code_b) noexcept
{
    return code_a.Category() == basic::error::system::make::Category(code_b) &&
        code_a.Value() < basic::error::system::make::code::Value(code_b);
}

inline bool operator<(const basic::error::defn::type::system::code::
    Value & code_a, const basic::error::system::Code & code_b) noexcept
{
    return code_a < code_b.Value();
}

template<typename TCodeEnum>
inline typename std::enable_if<basic::error::system::code::has::
    Enum<TCodeEnum>::Value, bool>::type 
operator<(const basic::error::defn::type::system::code::Value & code_a, 
    const TCodeEnum & code_b) noexcept
{
    return code_a < basic::error::system::make::code::Value(code_b);
}

template<typename TCodeEnum>
inline typename std::enable_if<basic::error::system::code::has::
    Enum<TCodeEnum>::Value, bool>::type 
operator<(const TCodeEnum & code_a, 
    const basic::error::system::Code & code_b) noexcept
{
    return basic::error::system::make::Category(code_a) == code_b.Category() &&
        basic::error::system::make::code::Value(code_a) < code_b.Value();
}

template<typename TCodeEnum>
inline typename std::enable_if<basic::error::system::code::has::
    Enum<TCodeEnum>::Value, bool>::type 
operator<(const TCodeEnum & code_a, 
    const basic::error::defn::type::system::code::Value & code_b) noexcept
{
    return basic::error::system::make::code::Value(code_a) < code_b;
}

inline bool operator>(const basic::error::system::Code & code_a, 
    const basic::error::system::Code & code_b) noexcept
{
    return code_b < code_a;
}

inline bool operator>(const basic::error::system::Code & code_a, 
    const basic::error::defn::type::system::code::Value & code_b) noexcept
{
    return code_b < code_a;
}

template<typename TCodeEnum>
inline typename std::enable_if<basic::error::system::code::has::
    Enum<TCodeEnum>::Value, bool>::type 
operator>(const basic::error::system::Code & code_a, 
    const TCodeEnum & code_b) noexcept
{
    return code_b < code_a;
}

inline bool operator>(const basic::error::defn::type::system::code::
    Value & code_a, const basic::error::system::Code & code_b) noexcept
{
    return code_b < code_a;
}

template<typename TCodeEnum>
inline typename std::enable_if<basic::error::system::code::has::
    Enum<TCodeEnum>::Value, bool>::type 
operator>(const basic::error::defn::type::system::code::Value & code_a, 
    const TCodeEnum & code_b) noexcept
{
    return code_b < code_a;
}

template<typename TCodeEnum>
inline typename std::enable_if<basic::error::system::code::has::
    Enum<TCodeEnum>::Value, bool>::type 
operator>(const TCodeEnum & code_a, 
    const basic::error::system::Code & code_b) noexcept
{
    return code_b < code_a;
}

template<typename TCodeEnum>
inline typename std::enable_if<basic::error::system::code::has::
    Enum<TCodeEnum>::Value, bool>::type 
operator>(const TCodeEnum & code_a, 
    const basic::error::defn::type::system::code::Value & code_b) noexcept
{
    return code_b < code_a;
}

#endif //!BASIC_ERROR_SYSTEM_CODE_H_
