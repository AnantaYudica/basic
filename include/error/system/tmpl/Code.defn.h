#ifndef BASIC_ERROR_SYSTEM_TMPL_CODE_H_DEFN_
#define BASIC_ERROR_SYSTEM_TMPL_CODE_H_DEFN_

#include "Code.decl.h"
#include "Category.decl.h"
#include "../Category.decl.h"
#include "../Code.decl.h"

#include "../intf/Category.h"
#include "../intf/Code.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/Output.h"
#include "../../defn/type/system/code/Value.h"
#include "../../msg/String.h"
#include "category/has/mmbr/defn/type/CodeEnum.h"

namespace basic
{
namespace error
{
namespace system
{
namespace tmpl
{

template<typename TCategoryTrait>
class Code : public intf::Code
{
public:
    typedef TCategoryTrait CategoryTraitType;
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
    typedef defn::type::system::code::Value ValueType;
public:
    typedef msg::String StringType;
public:
    typedef system::Category CategoryType;
    typedef system::Code CodeType;
    typedef system::Condition ConditionType;
public:
    typedef typename CategoryType::CodeSetValueType SetValueType;
private:
    ValueType m_value;
public:
    Code() noexcept;
    Code(const SetValueType & code) noexcept;
public:
    Code(const Code<TCategoryTrait> & cpy) noexcept;
    Code(Code<TCategoryTrait> && mov) noexcept;
public:
    ~Code();
private:
    Code<TCategoryTrait> & operator=(const CodeType & cpy) noexcept;
    Code<TCategoryTrait> & operator=(CodeType && mov) noexcept;
public:
    Code<TCategoryTrait> & 
        operator=(const Code<TCategoryTrait> & cpy) noexcept;
    Code<TCategoryTrait> & operator=(Code<TCategoryTrait> && mov) noexcept;
private:
    template<typename _TCategoryTrait = TCategoryTrait, 
        typename = typename std::enable_if<category::has::mmbr::defn::type::
        CodeEnum<_TCategoryTrait>::Value>::type>
    Code<TCategoryTrait> & operator=(const ValueType & code) noexcept 
public:
    template<typename _TCategoryTrait = TCategoryTrait, 
        typename = typename std::enable_if<category::has::mmbr::defn::type::
        CodeEnum<_TCategoryTrait>::Value>::type>
    Code<TCategoryTrait> & operator=(const SetValueType & code) noexcept;
    template<typename _TCategoryTrait = TCategoryTrait, 
        typename = typename std::enable_if<!category::has::mmbr::defn::type::
        CodeEnum<_TCategoryTrait>::Value>::type>
    Code<TCategoryTrait> & operator=(const ValueType & code) noexcept 
public:
    void Clear() noexcept;
public:
    ValueType Value() const noexcept;
public:
    const intf::Category & Category() const noexcept;
public:
    ConditionType DefaultCondition() const noexcept;
public:
    StringType Message() const noexcept;
private:
    const error::intf::Output & operator>>(OutputType &) const noexcept;
};

} //!tmpl

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_TMPL_CODE_H_DEFN_