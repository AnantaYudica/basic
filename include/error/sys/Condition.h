#ifndef BASIC_ERROR_SYS_CONDITION_H_
#define BASIC_ERROR_SYS_CONDITION_H_

#include "Condition.defn.h"

#include "make/Category.h"
#include "make/cond/Value.h"
#include "../defn/type/sys/cond/Value.h"
#include "../defn/func/output/Operator.h"
#include "cond/has/Enum.h"

#include <utility>
#include <type_traits>

namespace basic
{
namespace error
{
namespace sys
{

template<typename TConditionEnum>
inline Condition::Condition(const TConditionEnum & cond) noexcept :
    m_value(sys::make::cond::Value(cond)),
    m_categ(const_cast<CategoryType *>(&sys::make::Category(cond))),
    m_message(m_categ->Message(*this))
{}

inline Condition::Condition(const ValueType & val, 
    const CategoryType & categ) noexcept :
        m_value(val),
        m_categ(const_cast<CategoryType *>(&categ)),
        m_message(m_categ->Message(*this))
{}

inline Condition::Condition(const Condition & cpy) noexcept :
    m_value(cpy.m_value),
    m_categ(cpy.m_categ),
    m_message(cpy.m_message)
{}

inline Condition::Condition(Condition && mov) noexcept :
    m_value(std::move(mov.m_value)),
    m_categ(std::move(mov.m_categ)),
    m_message(std::move(mov.m_message))
{
    this->Clear();
}

inline Condition::~Condition() noexcept
{}

inline Condition & Condition::operator=(const Condition & cpy) noexcept
{
    this->m_value = cpy.m_value;
    this->m_categ = cpy.m_categ;
    this->m_message = cpy.m_message;
    return *this;
}

inline Condition & Condition::operator=(Condition && mov) noexcept
{
    this->m_value = std::move(mov.m_value);
    this->m_categ = std::move(mov.m_categ);
    this->m_message = std::move(mov.m_message);
    mov.Clear();
    return *this;
}

template<typename TConditionEnum>
inline Condition & Condition::operator=(const TConditionEnum & cond) noexcept
{
    this->m_value = sys::make::cond::Value(cond);
    this->m_categ = const_cast<CategoryType *>(&sys::make::
        Category(cond));
    this->m_message = std::move(m_categ->Message(*this));
    return *this;
}

inline void Condition::Assign(const ValueType & cond, 
    const CategoryType & categ) noexcept
{
    this->m_value = cond;
    this->m_categ = const_cast<CategoryType *>(&categ);
    this->m_message = std::move(m_categ->Message(*this));
}

inline void Condition::Clear() noexcept
{
    this->m_value = this->m_categ->DefaultCondition().Value();
    this->m_message = std::move(m_categ->Message(*this));
}

inline typename Condition::ValueType 
Condition::Value() const noexcept
{
    return this->m_value;
}

inline const typename Condition::CategoryType & 
Condition::Category() const noexcept
{
    return *this->m_categ;
}

inline const typename Condition::CharType * 
Condition::Message() const noexcept
{
    return this->m_message.Value();
}

inline const error::intf::Output & 
Condition::operator>>(OutputType & out) const noexcept
{
    error::defn::func::output::Operator(out, "code ", this->m_value);
    error::defn::func::output::Operator(out, "msg ", this->Message());
    return *this;
}

inline void Condition::Cleanup(int sig) noexcept
{
    static_cast<error::intf::Exit &>(this->m_message).Cleanup(sig);
}

} //!basic

} //!error

} //!sys

inline bool operator==(const basic::error::sys::Condition & cond_a, 
    const basic::error::sys::Condition & cond_b) noexcept
{
    return cond_a.Category() == cond_b.Category() &&
        cond_a.Value() == cond_b.Value();
}

inline bool operator==(const basic::error::sys::Condition & cond_a, 
    const basic::error::defn::type::sys::cond::Value & cond_b) noexcept
{
    return cond_a.Value() == cond_b;
}

template<typename TConditionEnum>
inline typename std::enable_if<basic::error::sys::cond::has::
    Enum<TConditionEnum>::Value, bool>::type  
operator==(const basic::error::sys::Condition & cond_a, 
    const TConditionEnum & cond_b) noexcept
{
    return cond_a.Category() == basic::error::sys::make::Category(cond_b) &&
        cond_a.Value() == basic::error::sys::make::cond::Value(cond_b);
}

inline bool operator==(const basic::error::defn::type::sys::cond::
    Value & cond_a, const basic::error::sys::Condition & cond_b) noexcept
{
    return cond_b == cond_a;
}

template<typename TConditionEnum>
inline typename std::enable_if<basic::error::sys::cond::has::
    Enum<TConditionEnum>::Value, bool>::type  
operator==(const basic::error::defn::type::sys::cond::
    Value & cond_a, const TConditionEnum & cond_b) noexcept
{
    return cond_a == basic::error::sys::make::cond::Value(cond_b);
}

template<typename TConditionEnum>
inline typename std::enable_if<basic::error::sys::cond::has::
    Enum<TConditionEnum>::Value, bool>::type  
operator==(const TConditionEnum & cond_a, 
    const basic::error::sys::Condition & cond_b) noexcept
{
    return cond_b == basic::error::sys::make::cond::
        Value(cond_a);
}

template<typename TConditionEnum>
inline typename std::enable_if<basic::error::sys::cond::has::
    Enum<TConditionEnum>::Value, bool>::type  
operator==(const TConditionEnum & cond_a, 
    const basic::error::defn::type::sys::cond::Value & cond_b) noexcept
{
    return cond_b == cond_a;
}

inline bool operator!=(const basic::error::sys::Condition & cond_a, 
    const basic::error::sys::Condition & cond_b) noexcept
{
    return !(cond_a == cond_b);
}

inline bool operator!=(const basic::error::sys::Condition & cond_a, 
    const basic::error::defn::type::sys::cond::Value & cond_b) noexcept
{
    return !(cond_a == cond_b);
}

template<typename TConditionEnum>
inline typename std::enable_if<basic::error::sys::cond::has::
    Enum<TConditionEnum>::Value, bool>::type  
operator!=(const basic::error::sys::Condition & cond_a, 
    const TConditionEnum & cond_b) noexcept
{
    return !(cond_a == cond_b);
}

inline bool operator!=(const basic::error::defn::type::sys::cond::
    Value & cond_a, const basic::error::sys::Condition & cond_b) noexcept
{
    return !(cond_a == cond_b);
}

template<typename TConditionEnum>
inline typename std::enable_if<basic::error::sys::cond::has::
    Enum<TConditionEnum>::Value, bool>::type  
operator!=(const basic::error::defn::type::sys::cond::
    Value & cond_a, const TConditionEnum & cond_b) noexcept
{
    return !(cond_a == cond_b);
}

template<typename TConditionEnum>
inline typename std::enable_if<basic::error::sys::cond::has::
    Enum<TConditionEnum>::Value, bool>::type  
operator!=(const TConditionEnum & cond_a, 
    const basic::error::sys::Condition & cond_b) noexcept
{
    return !(cond_a == cond_b);
}

template<typename TConditionEnum>
inline typename std::enable_if<basic::error::sys::cond::has::
    Enum<TConditionEnum>::Value, bool>::type  
operator!=(const TConditionEnum & cond_a, 
    const basic::error::defn::type::sys::cond::Value & cond_b) noexcept
{
    return !(cond_a == cond_b);
}

inline bool operator<(const basic::error::sys::Condition & cond_a, 
    const basic::error::sys::Condition & cond_b) noexcept
{
    return cond_a.Category() == cond_b.Category() &&
        cond_a.Value() < cond_b.Value();
}

inline bool operator<(const basic::error::sys::Condition & cond_a, 
    const basic::error::defn::type::sys::cond::Value & cond_b) noexcept
{
    return cond_a.Value() < cond_b;
}

template<typename TConditionEnum>
inline typename std::enable_if<basic::error::sys::cond::has::
    Enum<TConditionEnum>::Value, bool>::type  
operator<(const basic::error::sys::Condition & cond_a, 
    const TConditionEnum & cond_b) noexcept
{
    return cond_a.Category() == basic::error::sys::make::Category(cond_b) &&
        cond_a.Value() < basic::error::sys::make::cond::Value(cond_b);
}

inline bool operator<(const basic::error::defn::type::sys::cond::
    Value & cond_a, const basic::error::sys::Condition & cond_b) noexcept
{
    return cond_a < cond_b.Value();
}

template<typename TConditionEnum>
inline typename std::enable_if<basic::error::sys::cond::has::
    Enum<TConditionEnum>::Value, bool>::type  
operator<(const basic::error::defn::type::sys::cond::
    Value & cond_a, const TConditionEnum & cond_b) noexcept
{
    return cond_a < basic::error::sys::make::cond::Value(cond_b);
}

template<typename TConditionEnum>
inline typename std::enable_if<basic::error::sys::cond::has::
    Enum<TConditionEnum>::Value, bool>::type  
operator<(const TConditionEnum & cond_a, 
    const basic::error::sys::Condition & cond_b) noexcept
{
    return basic::error::sys::make::Category(cond_a) == cond_b.Category() &&
        basic::error::sys::make::cond::Value(cond_a) < cond_b.Value();
}

template<typename TConditionEnum>
inline typename std::enable_if<basic::error::sys::cond::has::
    Enum<TConditionEnum>::Value, bool>::type  
operator<( const TConditionEnum & cond_a, 
    const basic::error::defn::type::sys::cond::Value & cond_b) noexcept
{
    return basic::error::sys::make::cond::Value(cond_a) < cond_b;
}

inline bool operator>(const basic::error::sys::Condition & cond_a, 
    const basic::error::sys::Condition & cond_b) noexcept
{
    return cond_b < cond_a;
}

inline bool operator>(const basic::error::sys::Condition & cond_a, 
    const basic::error::defn::type::sys::cond::Value & cond_b) noexcept
{
    return cond_b < cond_a;
}

template<typename TConditionEnum>
inline typename std::enable_if<basic::error::sys::cond::has::
    Enum<TConditionEnum>::Value, bool>::type  
operator>(const basic::error::sys::Condition & cond_a, 
    const TConditionEnum & cond_b) noexcept
{
    return cond_b < cond_a;
}

inline bool operator>(const basic::error::defn::type::sys::cond::
    Value & cond_a, const basic::error::sys::Condition & cond_b) noexcept
{
    return cond_b < cond_a;
}

template<typename TConditionEnum>
inline typename std::enable_if<basic::error::sys::cond::has::
    Enum<TConditionEnum>::Value, bool>::type  
operator>(const basic::error::defn::type::sys::cond::
    Value & cond_a, const TConditionEnum & cond_b) noexcept
{
    return cond_b < cond_a;
}

template<typename TConditionEnum>
inline typename std::enable_if<basic::error::sys::cond::has::
    Enum<TConditionEnum>::Value, bool>::type  
operator>(const TConditionEnum & cond_a, 
    const basic::error::sys::Condition & cond_b) noexcept
{
    return cond_b < cond_a;
}

template<typename TConditionEnum>
inline typename std::enable_if<basic::error::sys::cond::has::
    Enum<TConditionEnum>::Value, bool>::type  
operator>(const TConditionEnum & cond_a, 
    const basic::error::defn::type::sys::cond::Value & cond_b) noexcept
{
    return cond_b < cond_a;
}


#endif //!BASIC_ERROR_SYS_CONDITION_H_
