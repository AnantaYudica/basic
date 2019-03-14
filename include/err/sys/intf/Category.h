#ifndef BASIC_ERR_SYS_INTF_CATEGORY_H_
#define BASIC_ERR_SYS_INTF_CATEGORY_H_

#include "Category.decl.h"
#include "../Code.decl.h"
#include "../Condition.decl.h"

#include "../../intf/Output.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/type/sys/categ/Value.h"
#include "../../defn/type/sys/code/Value.h"
#include "../../defn/type/sys/cond/Value.h"
#include "../../msg/String.h"

#include <ostream>

namespace basic
{
namespace err
{
namespace sys
{
namespace intf
{

class Category : public err::intf::Output
{
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
    typedef defn::type::sys::categ::Value ValueType;
    typedef defn::type::sys::code::Value CodeValueType;
    typedef defn::type::sys::cond::Value ConditionValueType;
public:
    typedef msg::String StringType;
public:
    typedef sys::Code CodeType;
    typedef sys::Condition ConditionType;
protected:
    Category() noexcept = default;
public:
    Category(const Category &) noexcept = default;
    Category(Category &&) noexcept = default;
public:
    virtual ~Category() noexcept = default;
public:
    Category & operator=(const Category &) = delete;
    Category & operator=(Category &&) = delete;
public:
    virtual ValueType Value() const noexcept = 0;
public:
    virtual const CharType * Name() const noexcept = 0;
public:
    virtual CodeValueType DefaultCodeValue() const noexcept = 0;
public:
    virtual ConditionValueType DefaultConditionValue() const noexcept = 0;
public:
    virtual CodeType DefaultCode() const noexcept = 0;
    virtual CodeType DefaultCode(const CodeValueType &) const noexcept = 0;
public:
    virtual ConditionType DefaultCondition() const noexcept = 0;
    virtual ConditionType DefaultCondition(const CodeValueType &) 
        const noexcept = 0;
    virtual ConditionType DefaultCondition(const CodeType &) 
        const noexcept = 0;
public:
    virtual bool Equivalent(const CodeValueType &, 
        const ConditionType &) const noexcept = 0;
    virtual bool Equivalent(const CodeType &,
        const ConditionValueType &) const noexcept = 0;
public:
    virtual StringType Message(const CodeType &) const noexcept = 0;
    virtual StringType Message(const ConditionType &) const noexcept = 0;
protected:
    virtual const err::intf::Output & 
        operator>>(OutputType &) const noexcept = 0;
};

} //!intf

} //!sys

} //!err

} //!basic

bool operator==(const basic::err::sys::intf::Category & a, 
    const basic::err::sys::intf::Category & b) noexcept
{
    return a.Value() == b.Value();
}

bool operator!=(const basic::err::sys::intf::Category & a, 
    const basic::err::sys::intf::Category & b) noexcept
{
    return !(a == b);
}

bool operator<(const basic::err::sys::intf::Category & a, 
    const basic::err::sys::intf::Category & b) noexcept
{
    return a.Value() < b.Value();
}

bool operator>(const basic::err::sys::intf::Category & a, 
    const basic::err::sys::intf::Category & b) noexcept
{
    return b < a;
}

#endif //!BASIC_ERR_SYS_INTF_CATEGORY_H_