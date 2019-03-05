#ifndef BASIC_ERROR_SYS_TMPL_IMP_CATEG_HASCODEENUM_H_DEFN_
#define BASIC_ERROR_SYS_TMPL_IMP_CATEG_HASCODEENUM_H_DEFN_

#include "../../../Code.decl.h"
#include "../../../Condition.decl.h"

#include "../Category.h"
#include "../../../intf/Category.h"
#include "../../categ/Base.h"
#include "../../../../intf/Output.h"
#include "../../../../defn/type/Char.h"
#include "../../../../defn/type/Output.h"
#include "../../../../defn/type/sys/categ/Value.h"
#include "../../../../defn/type/sys/code/Value.h"
#include "../../../../defn/type/sys/condition/Value.h"
#include "../../../../msg/String.h"
#include "../../categ/defn/type/code/set/Value.h"

namespace basic
{
namespace error
{
namespace sys
{
namespace tmpl
{
namespace imp
{

template<typename TCategoryTrait>
class Category<TCategoryTrait, true> :
    virtual public tmpl::categ::Base<TCategoryTrait>,
    public intf::Category
{
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
    typedef defn::type::sys::categ::Value ValueType;
    typedef defn::type::sys::code::Value CodeValueType;
    typedef defn::type::sys::condition::Value ConditionValueType;
public:
    typedef msg::String StringType;
public:
    typedef sys::Code CodeType;
    typedef sys::Condition ConditionType;
public:
    typedef tmpl::categ::defn::type::code::set::
        Value<TCategoryTrait> CodeSetValueType;
protected:
    Category() noexcept;
public:
    Category(const Category<TCategoryTrait, true> & cpy) noexcept = delete;
    Category(Category<TCategoryTrait, true> && mov) noexcept;
public:
    virtual ~Category() noexcept = default;
public:
    Category<TCategoryTrait, true> & 
    operator=(const Category<TCategoryTrait, true> & cpy) = delete;
    Category<TCategoryTrait, true> & 
    operator=(Category<TCategoryTrait, true> && mov) = delete;
public:
    virtual ValueType Value() const noexcept = 0;
public:
    virtual const CharType * Name() const noexcept = 0;
public:
    virtual CodeType DefaultCode() const noexcept = 0;
private:
    CodeType DefaultCode(const CodeValueType &) const noexcept;
public:
    CodeType DefaultCode(const CodeSetValueType &) const noexcept;
public:
    virtual ConditionType DefaultCondition() const noexcept = 0;
private:
    ConditionType DefaultCondition(const CodeValueType &) 
        const noexcept;
public:
    ConditionType DefaultCondition(const CodeSetValueType &) 
        const noexcept;
public:
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

} //!sys

} //!error

} //!basic

#endif //!BASIC_ERROR_SYS_TMPL_IMP_CATEG_HASCODEENUM_H_DEFN_
