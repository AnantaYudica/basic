#ifndef BASIC_ERR_TAG_TRIGGER_H_
#define BASIC_ERR_TAG_TRIGGER_H_

#include "../../Error.defn.h"

#include "../Identification.h"
#include "../Information.h"
#include "../defn/func/output/Operator.h"
#include "../defn/type/Char.h"
#include "../defn/type/Output.h"
#include "../defn/type/code/Value.h"

#include <utility>

namespace basic
{
namespace err
{
namespace tag
{

struct Trigger {};

} //!tag

} //!err

template<>
class Error<err::tag::Trigger> : public err::Information
{
public:
    typedef err::defn::type::Char CharType;
    typedef err::defn::type::Output OutputType;
    typedef err::defn::type::code::Value CodeValueType;
public:
    typedef err::Identification IdType;
public:
    typedef err::Information InfoType;
public:
    Error() noexcept;
    template<typename... TArgs>
    Error(const IdType & id, TArgs && ... args) noexcept;
public:
    Error(const Error<err::tag::Trigger> & cpy) noexcept;
    Error(Error<err::tag::Trigger> && mov) noexcept;
public:
    Error<err::tag::Trigger> & 
        operator=(const Error<err::tag::Trigger> &) = delete;
    Error<err::tag::Trigger> & 
        operator=(Error<err::tag::Trigger> &&) = delete;
public:
    virtual const CharType * Message() const noexcept;
public:
    CodeValueType Code() const noexcept;
protected:
    virtual const err::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

Error<err::tag::Trigger>::Error() noexcept :
    InfoType()
{}

template<typename... TArgs>
Error<err::tag::Trigger>::Error(const IdType & id, 
    TArgs && ... args) noexcept :
        InfoType(id, std::forward<TArgs>(args)...)
{}

Error<err::tag::Trigger>::
    Error(const Error<err::tag::Trigger> & cpy) noexcept :
        InfoType(cpy)
{}

Error<err::tag::Trigger>::Error(Error<err::tag::Trigger> && mov) noexcept :
    InfoType(std::move(mov))
{}

const typename Error<err::tag::Trigger>::CharType * 
Error<err::tag::Trigger>::Message() const noexcept
{
    return "";
}

typename Error<err::tag::Trigger>::CodeValueType
    Error<err::tag::Trigger>::Code() const noexcept
{
    return this->Identification().Error().Code();
}

const err::intf::Output & Error<err::tag::Trigger>::
    operator>>(OutputType & out) const noexcept
{
    err::Information::operator>>(out);
    return *this;
}

} //!basic

#endif //!BASIC_ERR_TAG_TRIGGER_H_
