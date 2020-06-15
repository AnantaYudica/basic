#ifndef BASIC_ERR_SYS_CATEG_DEFAULT_H_
#define BASIC_ERR_SYS_CATEG_DEFAULT_H_

#include "../../../defn/err/sys/Category.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/sys/categ/Value.h"
#include "../../defn/type/sys/code/Value.h"
#include "../../defn/type/sys/cond/Value.h"
#include "../../msg/String.h"

#include <system_error>

namespace basic
{
namespace err
{
namespace sys
{
namespace categ
{

class Default
{
public:
    typedef std::errc CodeEnumType;
    typedef std::errc ConditionEnumType;
public:
    typedef err::defn::type::Char CharType;
    typedef err::defn::type::sys::categ::Value CategoryValueType;
    typedef err::defn::type::sys::code::Value CodeValueType;
    typedef err::defn::type::sys::cond::Value ConditionValueType;
public:
    typedef msg::String StringType;
public:
    static inline Default Instance() noexcept;
public:
    inline Default() noexcept = default;
    inline Default(const Default &) noexcept = default;
    inline Default(Default &&) noexcept = default;
public:
    template<typename TCondition, typename TCode, typename TCategory>
    inline TCondition DefaultCondition(const TCode& code,
        const TCategory & categ) const noexcept;
    template<typename TCondition, typename TCategory>
    inline TCondition DefaultCondition(const CodeValueType & code,
        const TCategory & categ) const noexcept;
public:
    template<typename TCode>
    inline bool Equivalent(const TCode& code, 
        const ConditionValueType& cond) const noexcept;
    template<typename TCondition>
    inline bool Equivalent(const CodeValueType& code, 
        const TCondition& cond) const noexcept;
public:
    template<typename TValue>
    inline StringType Message(const TValue& val) const noexcept;
    inline StringType Message(const int & val) const noexcept;
    inline StringType Message(const std::errc & val) const noexcept; 
public:
    inline const CharType * Name() const noexcept;
public:
    inline CategoryValueType Value() const noexcept;
};

inline Default Default::Instance() noexcept
{
    return {};
}

template<typename TCondition, typename TCode, typename TCategory>
inline TCondition Default::DefaultCondition(const TCode& code,
        const TCategory & categ) const noexcept
{
    return {static_cast<ConditionValueType>(std::system_category().
        default_error_condition(code.Value()).value()), categ};
}

template<typename TCondition, typename TCategory>
inline TCondition Default::DefaultCondition(const CodeValueType & code,
    const TCategory & categ) const noexcept
{
    return {code, categ};
}

template<typename TCode>
inline bool Default::Equivalent(const TCode& code, 
    const ConditionValueType& cond) const noexcept
{
    return std::system_category().equivalent(std::error_code(code.Value(), 
        std::system_category()), cond);
}

template<typename TCondition>
inline bool Default::Equivalent(const CodeValueType& code, 
    const TCondition& cond) const noexcept
{
    return std::system_category().equivalent(code, 
        std::error_condition(cond.Value(), std::system_category())) || 
        std::system_category().equivalent(code, 
        std::error_condition(cond.Value(), std::generic_category())) ;
}
    
template<typename TValue>
inline typename Default::StringType 
Default::Message(const TValue& val) const noexcept
{
    return {std::system_category().message(val.Value())};
}

inline typename Default::StringType 
Default::Message(const int & val) const noexcept
{
    return {std::system_category().message(val)};
}

inline typename Default::StringType 
Default::Message(const std::errc & val) const noexcept
{
    return {std::system_category().message(static_cast<int>(val))};
}

inline const typename Default::CharType * Default::Name() const noexcept
{
    return std::system_category().name();
}

inline typename Default::CategoryValueType Default::Value() const noexcept
{
    return basic::defn::err::sys::system_category; 
}

} //!categ

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_CATEG_DEFAULT_H_