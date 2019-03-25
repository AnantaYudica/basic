#ifndef BASIC_ERR_SYS_CODE_H_DEFN_
#define BASIC_ERR_SYS_CODE_H_DEFN_

#include "Code.decl.h"
#include "Condition.decl.h"

#include "Category.h"
#include "../intf/Output.h"
#include "../intf/Exit.h"
#include "../defn/type/Char.h"
#include "../defn/type/Output.h"
#include "../defn/type/sys/code/Value.h"
#include "../msg/String.h"

namespace basic
{
namespace err
{
namespace sys
{

class Code : 
    public err::intf::Output,
    public err::intf::Exit
{
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
    typedef defn::type::sys::code::Value ValueType;
public:
    typedef msg::String StringType;
public:
    typedef intf::Category CategoryType;
public:
    typedef Condition ConditionType;
private:
    ValueType m_value;
    CategoryType * m_categ;
    StringType m_message;
public:
    template<typename TCodeEnum>
    explicit inline Code(const TCodeEnum & code) noexcept;
    inline Code(const ValueType & code, 
        const CategoryType & categ) noexcept;
public:
    inline Code(const Code & cpy) noexcept;
    inline Code(Code && mov) noexcept;
public:
    inline ~Code() noexcept;
public:
    inline Code & operator=(const Code & cpy) noexcept;
    inline Code & operator=(Code && mov) noexcept;
public:
    template<typename TCodeEnum>
    inline Code & operator=(const TCodeEnum& code) noexcept;
    inline Code & operator=(const CategoryType & code) noexcept;
public:
    inline void Assign(const ValueType& code,
        const CategoryType & categ) noexcept;
public:
    inline void Clear() noexcept;
public:
    inline ValueType Value() const noexcept;
public:
    inline const CategoryType & Category() const noexcept;
public:
    inline ConditionType DefaultCondition() const noexcept;
public:
    inline const CharType * Message() const noexcept;
private:
    inline const err::intf::Output & operator>>(OutputType & out) const noexcept;
private:
    inline void Cleanup(int sig) noexcept;
};

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_CODE_H_DEFN_
