#ifndef BASIC_ERR_TAG_CATCH_H_
#define BASIC_ERR_TAG_CATCH_H_

#include "../../Error.defn.h"

#include "Trigger.h"
#include "../id/Catch.h"
#include "../defn/type/Char.h"
#include "../defn/type/Output.h"
#include "../defn/func/output/Operator.h"

#include <utility>

namespace basic
{
namespace err
{
namespace tag
{

template<typename TTrigger = Error<err::tag::Trigger>>
struct Catch {};

} //!tag

} //!err

template<typename TTrigger>
class Error<err::tag::Catch<TTrigger>> : 
    public Error<err::tag::Trigger>
{
public:
    typedef Error<err::tag::Trigger> TriggerType;
public:
    typedef err::defn::type::Char CharType;
    typedef err::defn::type::Output OutputType;
private:
    TTrigger m_trigger;
public:
    Error() noexcept;
    template<typename... TArgs>
    Error(const TTrigger & trigger, const err::id::Catch & id, 
        TArgs  && ... args) noexcept;
public:
    Error(const Error<err::tag::Catch<TTrigger>> & cpy) noexcept;
    Error(Error<err::tag::Catch<TTrigger>> && mov) noexcept;
public:
    Error<err::tag::Catch<TTrigger>> & 
        operator=(const Error<err::tag::Catch<TTrigger>> &) = delete;
    Error<err::tag::Catch<TTrigger>> & 
        operator=(Error<err::tag::Catch<TTrigger>> &&) = delete;
public:
    const CharType * Message() const noexcept;
public:
    const TTrigger & Trigger() const noexcept;
protected:
    virtual const err::intf::Output & 
        operator>>(OutputType & out) const noexcept;
};

template<typename TTrigger>
Error<err::tag::Catch<TTrigger>>::Error() noexcept :
    TriggerType(),
    m_trigger()
{}

template<typename TTrigger>
template<typename... TArgs>
Error<err::tag::Catch<TTrigger>>::Error(const TTrigger & trigger, 
    const err::id::Catch & id, TArgs &&... args) noexcept :
        m_trigger(trigger),
        TriggerType(id, std::forward<TArgs>(args)...)
{}

template<typename TTrigger>
Error<err::tag::Catch<TTrigger>>::
    Error(const Error<err::tag::Catch<TTrigger>> & cpy) noexcept :
        m_trigger(cpy.m_trigger),
        TriggerType(cpy)

{}

template<typename TTrigger>
Error<err::tag::Catch<TTrigger>>::
    Error(Error<err::tag::Catch<TTrigger>> && mov) noexcept :
        m_trigger(std::move(mov.m_trigger)),
        TriggerType(std::move(mov))
{}

template<typename TTrigger>
const typename Error<err::tag::Catch<TTrigger>>::CharType * 
Error<err::tag::Catch<TTrigger>>::Message() const noexcept
{
    return "";
}

template<typename TTrigger>
const TTrigger& Error<err::tag::Catch<TTrigger>>::Trigger() const noexcept
{
    return m_trigger;
}

template<typename TTrigger>
const err::intf::Output & Error<err::tag::Catch<TTrigger>>::
    operator>>(OutputType & out) const noexcept
{
    err::defn::func::output::Operator(out, "in catch ");
    TriggerType::operator>>(out);
    return out;
}

} //!basic

#endif //!BASIC_ERR_TAG_CATCH_H_
