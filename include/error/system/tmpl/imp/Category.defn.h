#ifndef BASIC_ERROR_SYSTEM_TMPL_IMP_CATEGORY_H_DEFN_
#define BASIC_ERROR_SYSTEM_TMPL_IMP_CATEGORY_H_DEFN_

#include "../../Code.decl.h"
#include "../../Condition.decl.h"

#include "../../intf/Category.h"
#include "../categ/Base.h"
#include "../../../intf/Output.h"
#include "../../../defn/type/Char.h"
#include "../../../defn/type/Output.h"
#include "../../../defn/type/system/categ/Value.h"
#include "../../../defn/type/system/code/Value.h"
#include "../../../defn/type/system/condition/Value.h"
#include "../../../msg/String.h"
#include "../categ/has/mmbr/defn/type/CodeEnum.h"

namespace basic
{
namespace error
{
namespace system
{
namespace tmpl
{
namespace imp
{

template<typename TCategoryTrait, 
    bool HasCodeEnum = tmpl::categ::has::mmbr::defn::type::
        CodeEnum<TCategoryTrait>::Value>
class Category :
    virtual public tmpl::categ::Base<TCategoryTrait>,
    public intf::Category
{
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
    typedef defn::type::system::categ::Value ValueType;
    typedef defn::type::system::code::Value CodeValueType;
    typedef defn::type::system::condition::Value ConditionValueType;
public:
    typedef msg::String StringType;
public:
    typedef system::Code CodeType;
    typedef system::Condition ConditionType;
protected:
    Category() noexcept;
public:
    Category(const Category<TCategoryTrait, 
        HasCodeEnum> & cpy) noexcept = delete;
    Category(Category<TCategoryTrait, HasCodeEnum> && mov) noexcept;
public:
    virtual ~Category() noexcept = default;
public:
    Category<TCategoryTrait, HasCodeEnum> & 
    operator=(const Category<TCategoryTrait, HasCodeEnum> & cpy) = delete;
    Category<TCategoryTrait, HasCodeEnum> & 
    operator=(Category<TCategoryTrait, HasCodeEnum> && mov) = delete;
public:
    virtual ValueType Value() const noexcept = 0;
public:
    virtual const CharType * Name() const noexcept = 0;
public:
    virtual CodeType DefaultCode() const noexcept = 0;
    CodeType DefaultCode(const CodeValueType &) const noexcept;
public:
    virtual ConditionType DefaultCondition() const noexcept = 0;
    ConditionType DefaultCondition(const CodeValueType &) 
        const noexcept;
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
    virtual const error::intf::Output & 
        operator>>(OutputType &) const noexcept = 0;
}; 

} //!imp

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_IMP_CATEGORY_H_DEFN_
