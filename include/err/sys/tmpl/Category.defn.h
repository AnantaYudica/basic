#ifndef BASIC_ERR_SYS_TMPL_CATEGORY_H_DEFN_
#define BASIC_ERR_SYS_TMPL_CATEGORY_H_DEFN_

#include "Category.decl.h"
#include "../Code.decl.h"
#include "../Condition.decl.h"
#include "imp/categ/HasCodeEnum.defn.h"

#include "categ/Base.h"
#include "categ/defn/type/code/set/Value.h"
#include "categ/defn/type/cond/set/Value.h"
#include "categ/has/mmbr/defn/type/CodeEnum.h"
#include "imp/exit/HasCleanup.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/type/sys/categ/Value.h"
#include "../../defn/type/sys/code/Value.h"
#include "../../defn/type/sys/cond/Value.h"
#include "../../msg/String.h"

#include <type_traits>

namespace basic
{
namespace err
{
namespace sys
{
namespace tmpl
{

template<typename TCategoryTrait>
class Category : 
    virtual public tmpl::categ::Base<TCategoryTrait>,
    public tmpl::imp::Category<TCategoryTrait, Category<TCategoryTrait>>,
    public tmpl::imp::Exit<TCategoryTrait>
{
public:
    typedef TCategoryTrait TraitType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
    typedef defn::type::sys::categ::Value ValueType;
    typedef defn::type::sys::code::Value CodeValueType;
    typedef defn::type::sys::cond::Value ConditionValueType;
public:
    typedef msg::String StringType;
public:
    typedef categ::defn::type::code::set::
        Value<TCategoryTrait> CodeSetValueType;
    typedef categ::defn::type::cond::set::
        Value<TCategoryTrait> ConditionSetValueType;
public:
    typedef sys::Code CodeType;
    typedef sys::Condition ConditionType;
private:
    static Category<TCategoryTrait> * ms_instance;
private:
    static Category<TCategoryTrait> & ConstructInstance() noexcept;
public:
    static const Category<TCategoryTrait> & GetInstance() noexcept;
private:
    Category() noexcept;
public:
    Category(const Category<TCategoryTrait> & cpy) noexcept = delete;
    Category(Category<TCategoryTrait> && mov) noexcept;
public:
    ~Category() noexcept;
public:
    Category<TCategoryTrait> & 
        operator=(const Category<TCategoryTrait> &) = delete;
    Category<TCategoryTrait> & 
        operator=(Category<TCategoryTrait> &&) = delete;
private:
    const TCategoryTrait & GetCategoryTrait() const noexcept;
    TCategoryTrait & GetCategoryTrait() noexcept;
public:
    ValueType Value() const noexcept;
public:
    const CharType * Name() const noexcept;
public:
    CodeValueType DefaultCodeValue() const noexcept;
public:
    using tmpl::imp::Category<TCategoryTrait, Category<TCategoryTrait>>::
        DefaultCode;
public:
    CodeType DefaultCode() const noexcept;
    CodeType DefaultCode(const CodeValueType & code) const noexcept;
public:
    ConditionValueType DefaultConditionValue() const noexcept;
public:
    using tmpl::imp::Category<TCategoryTrait, Category<TCategoryTrait>>::
        DefaultCondition;
public:
    ConditionType DefaultCondition() const noexcept;
    ConditionType DefaultCondition(const CodeValueType &) const noexcept;
    ConditionType DefaultCondition(const CodeType & code) const noexcept;
public:
    CodeValueType ToCodeValue(const CodeSetValueType & code) const noexcept;
public:
    ConditionValueType 
    ToConditionValue(const ConditionSetValueType & cond) const noexcept;
public:
    bool Equivalent(const CodeValueType & code, 
        const ConditionType & cond) const noexcept;
    bool Equivalent(const CodeType & code,
        const ConditionValueType & cond) const noexcept;
public:
    StringType Message(const CodeType & code) const noexcept;
    StringType Message(const ConditionType & cond) const noexcept;
private:
    const err::intf::Output & operator>>(OutputType &) const noexcept;
};

} //!tmpl

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_TMPL_CATEGORY_H_DEFN_