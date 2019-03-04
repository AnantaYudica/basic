#ifndef BASIC_ERROR_TAG_SYSTEM_H_
#define BASIC_ERROR_TAG_SYSTEM_H_

#include "../../Error.defn.h"

#include "../Information.h"
#include "../id/System.h"
#include "../system/Category.h"
#include "../defn/type/Char.h"
#include "../defn/type/Output.h"
#include "../defn/type/system/categ/Value.h"
#include "../defn/type/system/code/Value.h"

#include <utility>

namespace basic
{
namespace error
{
namespace tag
{

struct System {};

} //!tag

} //!error

template<>
class Error<error::tag::System> : public error::Information
{
public:
    typedef error::defn::type::Char CharType;
    typedef error::defn::type::Output OutputType;
    typedef error::defn::type::system::categ::Value 
        CategoryValueType;
    typedef error::defn::type::system::code::Value 
        CodeValueType;
public:
    typedef error::Identification IdType;
public:
    typedef error::Information InfoType;
public:
    Error() noexcept;
    template<typename ... TArgs>
    Error(const error::id::System & id, TArgs && ... args) noexcept;
public:
    Error(const Error<error::tag::System> & cpy) noexcept;
    Error(Error<error::tag::System> && mov) noexcept;
public:
    Error<error::tag::System> & 
        operator=(const Error<error::tag::System> &) = delete;
    Error<error::tag::System> & 
        operator=(Error<error::tag::System> &&) = delete;
public:
    virtual const CharType * Message() const noexcept;
public:
    CategoryValueType Category() const noexcept;
    CodeValueType Code() const noexcept;
protected:
    virtual const error::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

Error<error::tag::System>::Error() noexcept
{}

template<typename ... TArgs>
Error<error::tag::System>::Error(const error::id::System & id, 
    TArgs && ... args) noexcept :
        InfoType(id, std::forward<TArgs>(args) ...)
{}

Error<error::tag::System>::Error(const Error<error::tag::System> & cpy) 
    noexcept :
        InfoType(cpy)
{}

Error<error::tag::System>::Error(Error<error::tag::System> && mov) noexcept :
    InfoType(std::move(mov))
{}

const Error<error::tag::System>::CharType * 
Error<error::tag::System>::Message() const noexcept 
{
    return "";
}

typename Error<error::tag::System>::CategoryValueType 
    Error<error::tag::System>::Category() const noexcept
{
    return this->Identification().ErrorSystem().Category();
}

typename Error<error::tag::System>::CodeValueType 
    Error<error::tag::System>::Code() const noexcept
{
    return this->Identification().ErrorSystem().Code();
}

const error::intf::Output & Error<error::tag::System>::
    operator>>(OutputType & out) const noexcept
{
    error::Information::operator>>(out);
    return *this;
}

} //!basic

#endif //!BASIC_ERROR_TAG_SYSTEM_H_
