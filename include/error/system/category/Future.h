#ifndef BASIC_ERROR_SYSTEM_CATEGORY_FUTURE_H_
#define BASIC_ERROR_SYSTEM_CATEGORY_FUTURE_H_

#include "../../constant/error/system/Category.h"
#include "../defn/type/Char.h"
#include "../defn/type/system/category/Value.h"
#include "../defn/type/system/code/Value.h"
#include "../defn/type/system/condition/Value.h"
#include "../msg/String.h"

#include <future>

namespace basic
{
namespace error
{
namespace system
{
namespace category
{

class Future
{
public:
    typedef std::future_errc CodeEnumType;
    typedef std::future_errc ConditionEnumType;
public:
    typedef error::defn::type::Char CharType;
    typedef error::defn::type::system::category::Value CategoryValueType;
    typedef error::defn::type::system::code::Value CodeValueType;
    typedef error::defn::type::system::condition::Value ConditionValueType;
public:
    typedef msg::String StringType;
public:
    static Future Instance() noexcept;
public:
    inline Future() noexcept = default;
    inline Future(const Future&) noexcept = default;
    inline Future(Future&&) noexcept = default;
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

inline Future Future::Instance() noexcept
{
    return {};
}

template<typename TCondition, typename TCode>
inline TCondition Future::DefaultCondition(const TCode& code) const noexcept
{
    return {std::future_category().
        default_error_condition(code.Value()).value()};
}

template<typename TCode>
inline bool Future::Equivalent(const TCode& code, 
    const ConditionValueType& cond) const noexcept
{
    return std::future_category().equivalent(std::error_code(code.Value(), 
        std::future_category()), cond);
}

template<typename TCondition>
inline bool Future::Equivalent(const CodeValueType& code, 
    const TCondition& cond) const noexcept
{
    return std::future_category().equivalent(code, 
        std::error_condition(cond.Value(), std::future_category()));
}

template<typename TValue>
inline typename Future::StringType 
Future::Message(const TValue& val) const noexcept
{
    return {std::future_category().message(val.Value())};
}

inline const typename Future::CharType * Future::Name() const noexcept
{
    return std::future_category().name();
}

inline typename Future::CategoryValueType Future::Value() const noexcept
{
    return constant::error::system::future_category;
}

} //!category

} //!system

} //!error

} //!basic

#endif //!BASIC_ERROR_SYSTEM_CATEGORY_FUTURE_H_