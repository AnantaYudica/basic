#ifndef BASIC_ERROR_H__FORWARD_DECLARATION_

#include "../../Error.h"

#else //else BASIC_ERROR_H__FORWARD_DECLARATION_

#ifndef BASIC_ERROR_TAG_TRIGGER_H_
#define BASIC_ERROR_TAG_TRIGGER_H_

#include "../Identification.h"
#include "../Information.h"
#include "../output/Operator.h"
#include "../defn/type/Char.h"
#include "../defn/type/Output.h"
#include "../defn/type/code/Value.h"

#include <utility>

namespace basic
{
namespace error
{
namespace tag
{

struct Trigger {};

} //!tag

} //!error

template<>
class Error<error::tag::Trigger> : public error::Information
{
public:
    typedef error::defn::type::Char CharType;
    typedef error::defn::type::Output OutputType;
    typedef error::defn::type::code::Value CodeValueType;
public:
    typedef error::Identification IdType;
public:
    typedef error::Information InfoType;
public:
    Error() noexcept;
    template<typename... TArgs>
    Error(const IdType & id, TArgs && ... args) noexcept;
public:
    Error(const Error<error::tag::Trigger> & cpy) noexcept;
    Error(Error<error::tag::Trigger> && mov) noexcept;
public:
    Error<error::tag::Trigger> & 
        operator=(const Error<error::tag::Trigger> &) = delete;
    Error<error::tag::Trigger> & 
        operator=(Error<error::tag::Trigger> &&) = delete;
public:
    virtual const CharType * Message() const noexcept;
public:
    const InfoType & Information() const noexcept;
    CodeValueType Code() const noexcept;
protected:
    virtual const error::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

Error<error::tag::Trigger>::Error() noexcept :
    InfoType()
{}

template<typename... TArgs>
Error<error::tag::Trigger>::Error(const IdType & id, 
    TArgs && ... args) noexcept :
        InfoType(id, std::forward<TArgs>(args)...)
{}

Error<error::tag::Trigger>::
    Error(const Error<error::tag::Trigger> & cpy) noexcept :
        InfoType(cpy)
{}

Error<error::tag::Trigger>::Error(Error<error::tag::Trigger> && mov) noexcept :
    InfoType(std::move(mov))
{}

const typename Error<error::tag::Trigger>::CharType * 
Error<error::tag::Trigger>::Message() const noexcept
{
    return "";
}

const typename Error<error::tag::Trigger>::InfoType & 
    Error<error::tag::Trigger>::Information() const noexcept
{
    return *this;
}

typename Error<error::tag::Trigger>::CodeValueType
    Error<error::tag::Trigger>::Code() const noexcept
{
    return this->Identification().Error().Code();
}

const error::intf::Output & Error<error::tag::Trigger>::
    operator>>(OutputType & out) const noexcept
{
    error::Information::operator>>(out);
    return *this;
}

} //!basic

#endif //!BASIC_ERROR_TAG_TRIGGER_H_

#endif //!BASIC_ERROR_H__FORWARD_DECLARATION_
