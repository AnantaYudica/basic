#ifndef BASIC_ERROR_SYSTEM_CATEGORY_DEFAULT_H_
#define BASIC_ERROR_SYSTEM_CATEGORY_DEFAULT_H_

#include "../../../constant/error/system/Category.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/system/category/Value.h"
#include "../../defn/type/system/code/Value.h"
#include "../../defn/type/system/condition/Value.h"
#include "../../msg/String.h"

#include <system_error>

namespace basic
{
namespace error
{
namespace system
{
namespace category
{

class Default
{
public:
    typedef std::errc CodeEnumType;
    typedef std::errc ConditionEnumType;
public:
    typedef error::defn::type::Char CharType;
    typedef error::defn::type::system::category::Value CategoryValueType;
    typedef error::defn::type::system::code::Value CodeValueType;
    typedef error::defn::type::system::condition::Value ConditionValueType;
public:
    typedef msg::String StringType;
public:
    static inline Default Instance() noexcept;
public:
    inline Default() noexcept = default;
    inline Default(const Default &) noexcept = default;
    inline Default(Default &&) noexcept = default;
public:
    template<typename TCondition, typename TCode>
    inline TCondition DefaultCondition(const TCode& code) const noexcept;
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

template<typename TCondition, typename TCode>
inline TCondition Default::DefaultCondition(const TCode& code) const noexcept
{
    return {std::system_category().
        default_error_condition(code.Value()).value()};
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
        std::error_condition(cond.Value(), std::system_category()));
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
    return constant::error::system::system_category; 
}

} //!category

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_CATEGORY_DEFAULT_H_