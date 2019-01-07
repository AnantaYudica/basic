#ifndef BASIC_ERROR_SYSTEM_INTF_CODE_H_DEFN_
#define BASIC_ERROR_SYSTEM_INTF_CODE_H_DEFN_

#include "Code.decl.h"
#include "Category.decl.h"
#include "../Condition.decl.h"

#include "../../intf/Output.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/type/system/code/Value.h"
#include "../../msg/String.h"

namespace basic
{
namespace error
{
namespace system
{
namespace intf
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
    typedef system::Condition ConditionType;
protected:
    Code() noexcept = default;
public:
    Code(const Code &) noexcept = default;
    Code(Code &&) noexcept = default;
public:
    virtual ~Code() noexcept = default;
public:
    virtual Code & operator=(const Code &) noexcept = 0;
    virtual Code & operator=(Code &&) noexcept = 0;
public:
    virtual Code & operator=(const ValueType &) noexcept = 0;
public:
    virtual void Clear() noexcept = 0;
public:
    virtual ValueType Value() const noexcept = 0;
public:
    virtual const CategoryInterfaceType & Category() const noexcept = 0;
public:
    virtual ConditionType DefaultCondition() const noexcept = 0;
public:
    virtual StringType Message() const noexcept = 0;
private:
    virtual const error::intf::Output & 
        operator>>(OutputType &) const noexcept = 0;
};

} //!intf

} //!system

} //!error

} //!basic 

#endif //!BASIC_ERROR_SYSTEM_INTF_CODE_H_DEFN_