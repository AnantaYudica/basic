#ifndef BASIC_ERR_SYS_CONDITION_H_DEFN_
#define BASIC_ERR_SYS_CONDITION_H_DEFN_

#include "Condition.decl.h"
#include "Code.decl.h"

#include "Category.h"
#include "../intf/Output.h"
#include "../intf/Exit.h"
#include "../defn/type/Char.h"
#include "../defn/type/Output.h"
#include "../defn/type/sys/cond/Value.h"
#include "../msg/String.h"

namespace basic
{
namespace err
{
namespace sys
{

class Condition : 
    public err::intf::Output,
    public err::intf::Exit
{
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
    typedef defn::type::sys::cond::Value ValueType;
public:
    typedef msg::String StringType;
public:
    typedef intf::Category CategoryType;
private:
    ValueType m_value;
    CategoryType * m_categ;
    StringType m_message;
public:
    template<typename TConditionEnum>
    inline Condition(const TConditionEnum & cond) noexcept;
    inline Condition(const ValueType & val, 
        const CategoryType & categ) noexcept;
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
public:
    inline void Assign(const ValueType & cond, 
        const CategoryType & categ) noexcept;
public:
    inline void Clear() noexcept;
public:
    inline ValueType Value() const noexcept;
public:
    inline const CategoryType & Category() const noexcept;
public:
    inline const CharType * Message() const noexcept;
private:
    inline const err::intf::Output & operator>>(OutputType &) const noexcept;
private:
    inline void Cleanup(int sig) noexcept;
};

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_CONDITION_H_DEFN_
