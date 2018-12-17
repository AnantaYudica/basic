#ifndef BASIC_ERROR_SYSTEM_INTF_CONDITION_DEF_H_
#define BASIC_ERROR_SYSTEM_INTF_CONDITION_DEF_H_

#include "Condition.dec.h"
#include "Category.dec.h"

#include "../defn/type/Char.h"
#include "../defn/type/Output.h"
#include "../defn/type/system/condition/Value.h"
#include "../msg/String.h"

namespace basic
{
namespace error
{
namespace system
{
namespace intf
{

class Condition
{
public:
    typedef defn::type::Char CharType;
    typedef defn::type::Output OutputType;
    typedef defn::type::system::condition::Value ValueType;
public:
    typedef msg::String StringType;
public:
    typedef Category CategoryInterfaceType;
protected:
    Condition() noexcept = default;
public:
    Condition(const Condition &) noexcept = default;
    Condition(Condition &&) noexcept = default;
public:
    virtual ~Condition() noexcept = default;
public:
    virtual Condition & operator=(const Condition &) noexcept = 0;
    virtual Condition & operator=(Condition &&) noexcept = 0;
public:
    virtual Condition & operator=(const ValueType &) noexcept = 0;
public:
    virtual void Clear() noexcept = 0;
public:
    virtual ValueType Value() const noexcept = 0;
public:
    virtual const CategoryInterfaceType & Category() const noexcept = 0;
public:
    virtual StringType Message() const noexcept = 0;
public:
    virtual OutputType & Output(OutputType &) const noexcept = 0;
};

} //!intf

} //!system

} //!error

} //!basic 

#endif //!BASIC_ERROR_SYSTEM_INTF_CONDITION_DEF_H_