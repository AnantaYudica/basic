#ifndef BASIC_ERROR_SYSTEM_CODE_H_DEFN_
#define BASIC_ERROR_SYSTEM_CODE_H_DEFN_

#include "Code.decl.h"
#include "Condition.decl.h"
#include "intf/Category.decl.h"
#include "intf/Code.decl.h"

#include "../intf/Output.h"
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

class Code : public error::intf::Output
{
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
    typedef defn::type::system::code::Value ValueType;
public:
    typedef msg::String StringType;
public:
    typedef intf::Category CategoryInterfaceType;
    typedef intf::Code CodeInterfaceType;
public:
    typedef Condition ConditionType;
private:
    ValueType m_value;
    const CategoryInterfaceType & m_category;
    StringType m_message;
public:
    template<typename TCodeEnum>
    inline Code(const TCodeEnum & code) noexcept;
    inline Code(const CodeInterfaceType & code) noexcept;
    inline Code(const ValueType & code, 
        const CategoryInterfaceType & category) noexcept;
public:
    inline Code(const Code & cpy) noexcept;
    inline Code(Code && mov) noexcept;
public:
    inline ~Code() noexcept;
public:
    Code & operator=(const Code & cpy) noexcept = delete;
    Code & operator=(Code && mov) noexcept = delete;
public:
    template<typename TCodeEnum>
    inline Code & operator=(const TCodeEnum& code) noexcept;
    inline Code & operator=(const CodeInterfaceType & code) noexcept;
public:
    inline void Assign(const ValueType& code,
        const CategoryInterfaceType & category) noexcept;
public:
    inline void Clear() noexcept;
public:
    inline ValueType Value() const noexcept;
public:
    inline const CategoryInterfaceType & Category() const noexcept;
public:
    inline ConditionType DefaultCondition() const noexcept;
public:
    inline const CharType * Message() const noexcept;
private:
    inline error::intf::Output & operator>>(OutputType & out) const noexcept;
};

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_CODE_H_DEFN_
