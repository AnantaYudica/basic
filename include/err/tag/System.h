#ifndef BASIC_ERR_TAG_SYSTEM_H_
#define BASIC_ERR_TAG_SYSTEM_H_

#include "../../Error.defn.h"

#include "../Information.h"
#include "../id/System.h"
#include "../sys/Category.h"
#include "../defn/type/Char.h"
#include "../defn/type/Output.h"
#include "../defn/type/sys/categ/Value.h"
#include "../defn/type/sys/code/Value.h"

#include <utility>

namespace basic
{
namespace err
{
namespace tag
{

struct System {};

} //!tag

} //!err

template<>
class Error<err::tag::System> : public err::Information
{
public:
    typedef err::defn::type::Char CharType;
    typedef err::defn::type::Output OutputType;
    typedef err::defn::type::sys::categ::Value 
        CategoryValueType;
    typedef err::defn::type::sys::code::Value 
        CodeValueType;
public:
    typedef err::Identification IdType;
public:
    typedef err::Information InfoType;
public:
    Error() noexcept;
    template<typename ... TArgs>
    Error(const err::id::System & id, TArgs && ... args) noexcept;
public:
    Error(const Error<err::tag::System> & cpy) noexcept;
    Error(Error<err::tag::System> && mov) noexcept;
public:
    Error<err::tag::System> & 
        operator=(const Error<err::tag::System> &) = delete;
    Error<err::tag::System> & 
        operator=(Error<err::tag::System> &&) = delete;
public:
    virtual const CharType * Message() const noexcept;
public:
    CategoryValueType Category() const noexcept;
    CodeValueType Code() const noexcept;
protected:
    virtual const err::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

Error<err::tag::System>::Error() noexcept
{}

template<typename ... TArgs>
Error<err::tag::System>::Error(const err::id::System & id, 
    TArgs && ... args) noexcept :
        InfoType(id, std::forward<TArgs>(args) ...)
{}

Error<err::tag::System>::Error(const Error<err::tag::System> & cpy) 
    noexcept :
        InfoType(cpy)
{}

Error<err::tag::System>::Error(Error<err::tag::System> && mov) noexcept :
    InfoType(std::move(mov))
{}

const Error<err::tag::System>::CharType * 
Error<err::tag::System>::Message() const noexcept 
{
    return "";
}

typename Error<err::tag::System>::CategoryValueType 
    Error<err::tag::System>::Category() const noexcept
{
    return this->Identification().ErrorSystem().Category();
}

typename Error<err::tag::System>::CodeValueType 
    Error<err::tag::System>::Code() const noexcept
{
    return this->Identification().ErrorSystem().Code();
}

const err::intf::Output & Error<err::tag::System>::
    operator>>(OutputType & out) const noexcept
{
    err::Information::operator>>(out);
    return *this;
}

} //!basic

#endif //!BASIC_ERR_TAG_SYSTEM_H_
