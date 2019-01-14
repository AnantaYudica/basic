#ifndef BASIC_ERROR_SYSTEM_CODE_H_DEFN_
#define BASIC_ERROR_SYSTEM_CODE_H_DEFN_

#include "Code.decl.h"
#include "Condition.decl.h"

#include "Category.h"
#include "../intf/Output.h"
#include "../intf/Exit.h"
#include "../defn/type/Char.h"
#include "../defn/type/Output.h"
#include "../defn/type/system/code/Value.h"
#include "../msg/String.h"

namespace basic
{
namespace error
{
namespace system
{

class Code : 
    public error::intf::Output,
    public error::intf::Exit
{
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
    typedef defn::type::system::code::Value ValueType;
public:
    typedef msg::String StringType;
public:
    typedef Category CategoryType;
public:
    typedef Condition ConditionType;
private:
    ValueType m_value;
    CategoryType * m_category;
    StringType m_message;
public:
    template<typename TCodeEnum>
    inline Code(const TCodeEnum & code) noexcept;
    inline Code(const ValueType & code, 
        const CategoryType & category) noexcept;
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
        const CategoryType & category) noexcept;
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
    inline const error::intf::Output & operator>>(OutputType & out) const noexcept;
private:
    inline void Cleanup(int sig) noexcept;
};

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_CODE_H_DEFN_
