#ifndef BASIC_ERROR_SYSTEM_TMPL_CATEGORY_H_DEFN_
#define BASIC_ERROR_SYSTEM_TMPL_CATEGORY_H_DEFN_

#include "Category.decl.h"
#include "Code.decl.h"
#include "Condition.decl.h"
#include "../Code.decl.h"
#include "../Condition.decl.h"

#include "category/has/mmbr/defn/type/CodeEnum.h"
#include "../../intf/Category.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/system/category/Value.h"
#include "../../defn/type/system/code/Value.h"
#include "../../defn/type/system/condition/Value.h"
#include "../../msg/String.h"

namespace basic
{
namespace error
{
namespace system
{
namespace tmpl
{

template<typename TCategoryTrait>
class Category : public intf::Category
{
public:
    typedef TCategoryTrait TraitType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::system::category::Value ValueType;
    typedef defn::type::system::code::Value CodeValueType;
    typedef defn::type::system::condition::Value ConditionValueType;
public:
    typedef msg::String StringType;
public:
    typedef category::defn::type::code::set::
        Value<TCategoryTrait> CodeSetValueType;
    typedef category::defn::type::condition::set::
        Value<TCategoryTrait> ConditionSetValueType;
public:
    typedef system::Code CodeType;
    typedef system::Condition ConditionType;
public:
    Category() noexcept;
public:
    Category(const Category<TCategoryTrait> & cpy) noexcept;
    Category(Category<TCategoryTrait> && mov) noexcept;
public:
    ~Category() noexcept;
public:
    Category<TCategoryTrait> & 
        operator=(const Category<TCategoryTrait> &) = delete;
    Category<TCategoryTrait> & 
        operator=(Category<TCategoryTrait> &&) = delete;
public:
    ValueType Value() const noexcept;
public:
    const CharType * Name() const noexcept;
public:
    CodeType DefaultCode() const noexcept;
private:
    template<typename _TCategoryTrait = TCategoryTrait>
    typename std::enable_if<category::has::mmbr::defn::type::
        CodeEnum<_TCategoryTrait>::Value, CodeType>::type
    DefaultCode(const CodeValueType &) const noexcept;
public:
    template<typename _TCategoryTrait = TCategoryTrait>
    typename std::enable_if<!category::has::mmbr::defn::type::
        CodeEnum<_TCategoryTrait>::Value, CodeType>::type
    DefaultCode(const CodeValueType &) const noexcept;
    template<typename _TCategoryTrait = TCategoryTrait>
    typename std::enable_if<category::has::mmbr::defn::type::
        CodeEnum<_TCategoryTrait>::Value, CodeType>::type
    DefaultCode(const CodeSetValueType &) const noexcept;
public:
    ConditionType DefaultCondition() const noexcept;
public:
    template<typename _TCategoryTrait = TCategoryTrait>
    typename std::enable_if<!category::has::mmbr::defn::type::
        ConditionEnum<_TCategoryTrait>::Value, ConditionType>::type
    DefaultCondition(const CodeValueType & code) const noexcept;
    template<typename _TCategoryTrait = TCategoryTrait>
    ConditionType DefaultCondition(const Code & code) const noexcept;
private:
    bool Equivalent(const CodeValueType & code, 
        const ConditionType & cond) const noexcept;
    bool Equivalent(const CodeType & code,
        const ConditionValueType & cond) const noexcept;
public:
    bool Equivalent(const CodeValueType & code, 
        const Condition<TCategoryTrait> & cond) const noexcept;
    bool Equivalent(const Code<TCategoryTrait> & code,
        const ConditionValueType & cond) const noexcept;
private:
    StringType Message(const CodeType & code) const noexcept;
    StringType Message(const ConditionType & cond) const noexcept;
public:
    StringType Message(const Code<TCategoryTrait> & code) const noexcept;
    StringType Message(const Condition<TCategoryTrait> & cond) const noexcept;
private:
    const error::intf::Output & operator>>(OutputType &) const noexcept;
};

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CATEGORY_H_DEFN_