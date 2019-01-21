#ifndef BASIC_ERROR_SYSTEM_CATEGORY_GENERIC_H_
#define BASIC_ERROR_SYSTEM_CATEGORY_GENERIC_H_

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

class Generic
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
    static Generic Instance() noexcept;
public:
    inline Generic() noexcept = default;
    inline Generic(const Generic &) noexcept = default;
    inline Generic(Generic &&) noexcept = default;
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
public:
    inline const CharType * Name() const noexcept;
public:
    inline CategoryValueType Value() const noexcept;
};

template<typename TCondition, typename TCode>
inline TCondition Generic::DefaultCondition(const TCode& code) const noexcept
{
    return {std::generic_category().
        default_error_condition(code.Value()).value()};
}

template<typename TCode>
inline bool Generic::Equivalent(const TCode& code, 
    const ConditionValueType& cond) const noexcept
{
    return std::generic_category().equivalent(std::error_code(code.Value(), 
        std::generic_category()), cond);
}

template<typename TCondition>
inline bool Generic::Equivalent(const CodeValueType& code, 
    const TCondition& cond) const noexcept
{
    return std::generic_category().equivalent(code, 
        std::error_condition(cond.Value(), std::generic_category()));
}
    
template<typename TValue>
inline typename Generic::StringType 
Generic::Message(const TValue& val) const noexcept
{
    return {std::generic_category().message(val.Value())};
}

inline const typename Generic::CharType * Generic::Name() const noexcept
{
    return std::generic_category().name();
}

inline typename Generic::CategoryValueType Generic::Value() const noexcept
{
    return constant::error::system::generic_category; 
}

} //!category

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_CATEGORY_GENERIC_H_