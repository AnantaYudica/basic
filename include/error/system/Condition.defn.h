#ifndef BASIC_ERROR_SYSTEM_CONDITION_H_DEFN_
#define BASIC_ERROR_SYSTEM_CONDITION_H_DEFN_

#include "Condition.decl.h"
#include "Code.decl.h"
#include "intf/Category.decl.h"
#include "intf/Condition.decl.h"

#include "../intf/Output.h"
#include "../defn/type/Char.h"
#include "../defn/type/Output.h"
#include "../defn/type/system/condition/Value.h"
#include "../msg/String.h"

namespace basic
{
namespace error
{
namespace system
{

class Condition : public error::intf::Output
{
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
    typedef defn::type::system::condition::Value ValueType;
public:
    typedef msg::String StringType;
public:
    typedef intf::Category CategoryInterfaceType;
    typedef intf::Condition ConditionInterfaceType;
private:
    ValueType m_value;
    const CategoryInterfaceType & m_category;
    StringType m_message;
protected:
    template<typename TConditionEnum>
    inline Condition(const TConditionEnum & cond) noexcept;
    inline Condition(const ConditionInterfaceType & cond) noexcept;
    inline Condition(const ValueType & val, 
        const CategoryInterfaceType & category) noexcept;
public:
    inline Condition(const Condition & cpy) noexcept;
    inline Condition(Condition && mov) noexcept;
public:
    inline ~Condition() noexcept;
public:
    inline Condition & operator=(const Condition & cpy) noexcept;
    inline Condition & operator=(Condition && mov) noexcept;
public:
    template<typename TConditionEnum>
    inline Condition & operator=(const TConditionEnum & cond) noexcept;
    inline Condition & operator=(const ConditionInterfaceType & cond) noexcept;
public:
    inline void Assign(const ValueType & cond, 
        const CategoryInterfaceType & category) noexcept;
public:
    inline void Clear() noexcept;
public:
    inline ValueType Value() const noexcept;
public:
    inline const CategoryInterfaceType & Category() const noexcept;
public:
    inline const CharType * Message() const noexcept;
private:
    inline error::intf::Output & operator>>(OutputType &) const noexcept;
};

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_CONDITION_H_DEFN_
