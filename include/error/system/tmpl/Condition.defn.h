#ifndef BASIC_ERROR_SYSTEM_TMPL_CONDITION_H_DEFN_
#define BASIC_ERROR_SYSTEM_TMPL_CONDITION_H_DEFN_

#include "Condition.decl.h"
#include "Code.decl.h"
#include "../Category.decl.h"
#include "../Code.decl.h"

#include "../intf/Condition.h"
#include "../defn/type/Char.h"
#include "../defn/type/system/Condition/Value.h"
#include "../msg/String.h"
#include "category/has/func/DefaultCode.h"
#include "category/has/mmbr/defn/type/ConditionEnum.h"

namespace basic
{
namespace error
{
namespace system
{
namespace tmpl
{

template<typename TCategoryTrait>
class Condition : public intf::Condition
{
public:
    typedef TCategoryTrait CategoryTraitType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::system::condition::Value ValueType;
public:
    typedef msg::String StringType;
public:
    typedef Code<TCategoryTrait> CodeTemplateType;
public:
    typedef system::Category CategoryType;
    typedef system::Condition ConditionType;
    typedef system::Code CodeType;
public:
    typedef typename CategoryType::ConditionSetValueType SetValueType;
private:
    ValueType m_value;
public:
    Condition() noexcept;
    Condition(const CodeTemplateType & code) noexcept;
    Condition(const SetValueType & cond) noexcept;
public:
    Condition(const Condition<TCategoryTrait> & cpy) noexcept;
    Condition(Condition<TCategoryTrait> && mov) noexcept;
public:
    ~Condition() noexcept;
private:
    Condition<TCategoryTrait> & operator=(const ConditionType &) noexcept;
    Condition<TCategoryTrait> & operator=(ConditionType &&) noexcept;
public:
    Condition<TCategoryTrait> & 
        operator=(const Condition<TCategoryTrait> & cpy) noexcept;
    Condition<TCategoryTrait> & 
        operator=(Condition<TCategoryTrait> && mov) noexcept;
private:
    template<typename _TCategoryTrait = TCategoryTrait,
        typename = typename std::enable_if<category::has::mmbr::defn::type::
        ConditionEnum<_TCategoryTrait>::Value>::type>
    Condition<TCategoryTrait> & operator=(const ValueType& cond) noexcept;
public:
    template<typename _TCategoryTrait = TCategoryTrait,
        typename = typename std::enable_if<category::has::mmbr::defn::type::
        ConditionEnum<_TCategoryTrait>::Value>::type>
    Condition<TCategoryTrait> & operator=(const SetValueType& cond) noexcept;
    template<typename _TCategoryTrait = TCategoryTrait,
        typename = typename std::enable_if<!category::has::mmbr::defn::type::
        ConditionEnum<_TCategoryTrait>::Value>::type>
    Condition<TCategoryTrait> & operator=(const ValueType& cond) noexcept;
    Condition<TCategoryTrait> & 
        operator=(const CodeTemplateType & code) noexcept;
public:
    void Clear() noexcept;
public:
    ValueType Value() const noexcept;
public:
    const CategoryInterfaceType & Category() const noexcept;
public:
    StringType Message() const noexcept;
private:
    const error::intf::Output & operator>>(OutputType & out) const noexcept;
};

} //!tmpl

} //!system

} //!error

} //!basic


#endif //!BASIC_ERROR_SYSTEM_TMPL_CONDITION_H_DEFN_
