#ifndef BASIC_ERR_SYS_CATEG_FUTURE_H_
#define BASIC_ERR_SYS_CATEG_FUTURE_H_

#include "../../../defn/err/sys/Category.h"
#include "../../intf/Exit.h"
#include "../../defn/type/Char.h"
#include "../../defn/type/sys/categ/Value.h"
#include "../../defn/type/sys/code/Value.h"
#include "../../defn/type/sys/cond/Value.h"
#include "../../msg/String.h"

#include <future>

namespace basic
{
namespace err
{
namespace sys
{
namespace categ
{

class Future
{
public:
    typedef std::future_errc CodeEnumType;
    typedef std::future_errc ConditionEnumType;
public:
    typedef err::defn::type::Char CharType;
    typedef err::defn::type::sys::categ::Value CategoryValueType;
    typedef err::defn::type::sys::code::Value CodeValueType;
    typedef err::defn::type::sys::cond::Value ConditionValueType;
public:
    typedef msg::String StringType;
public:
    static inline Future Instance() noexcept;
private:
    inline Future() noexcept = default;
public:
    inline Future(const Future&) noexcept = default;
    inline Future(Future&&) noexcept = default;
public:
    template<typename TCondition, typename TCategory>
    inline TCondition DefaultCondition(const CodeValueType& code, 
        const TCategory & categ) const noexcept;
    template<typename TCondition, typename TCode, typename TCategory>
    inline TCondition DefaultCondition(const TCode& code,
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
    inline StringType Message(const TValue & val) const noexcept;
    inline StringType Message(const int & val) const noexcept;
    inline StringType Message(const std::future_errc & val) const noexcept; 
public:
    inline const CharType * Name() const noexcept;
public:
    inline CategoryValueType Value() const noexcept;
};

inline Future Future::Instance() noexcept
{
    return {};
}

template<typename TCondition, typename TCategory>
inline TCondition Future::DefaultCondition(const CodeValueType& code, 
    const TCategory & categ) const noexcept
{
    return {code, categ};
}
    
template<typename TCondition, typename TCode, typename TCategory>
inline TCondition Future::DefaultCondition(const TCode& code,
    const TCategory & categ) const noexcept
{
    return {static_cast<ConditionValueType>(std::future_category().
        default_error_condition(code.Value()).value()), categ};
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

inline typename Future::StringType 
Future::Message(const int & val) const noexcept
{
    return {std::future_category().message(val)};
}

inline typename Future::StringType 
Future::Message(const std::future_errc & val) const noexcept
{
    return  {std::future_category().message(static_cast<int>(val))};
}

inline const typename Future::CharType * Future::Name() const noexcept
{
    return std::future_category().name();
}

inline typename Future::CategoryValueType Future::Value() const noexcept
{
    return basic::defn::err::sys::future_category;
}

} //!categ

} //!sys

} //!err

} //!basic

#endif //!BASIC_ERR_SYS_CATEG_FUTURE_H_