#ifndef BASIC_ERROR_H__FORWARD_DECLARATION_

#include "../../Error.h"

#else //else BASIC_ERROR_H__FORWARD_DECLARATION_

#ifndef BASIC_ERROR_TAG_CATCH_H_
#define BASIC_ERROR_TAG_CATCH_H_

#include "Trigger.h"
#include "../id/Catch.h"
#include "../defn/type/Char.h"
#include "../defn/type/Output.h"
#include "../output/Interface.h"
#include "../output/Operator.h"

#include <utility>

namespace basic
{
namespace error
{
namespace tag
{

template<typename TTrigger = Error<error::tag::Trigger>>
struct Catch {};

} //!tag

} //!error

template<typename TTrigger>
class Error<error::tag::Catch<TTrigger>> : 
    public Error<error::tag::Trigger>
{
public:
    typedef Error<error::tag::Trigger> TriggerType;
public:
    typedef error::defn::type::Char CharType;
    typedef error::defn::type::Output OutputValueType;
private:
    TTrigger m_trigger;
public:
    Error() noexcept;
    template<typename... TArgs>
    Error(const TTrigger& trigger, const error::id::Catch& id, 
        TArgs&&... args) noexcept;
public:
    Error(const Error<error::tag::Catch<TTrigger>>& cpy) noexcept;
    Error(Error<error::tag::Catch<TTrigger>>&& mov) noexcept;
public:
    Error<error::tag::Catch<TTrigger>>& 
        operator=(const Error<error::tag::Catch<TTrigger>>&) = delete;
    Error<error::tag::Catch<TTrigger>>& 
        operator=(Error<error::tag::Catch<TTrigger>>&&) = delete;
public:
    const CharType * Message() const noexcept;
public:
    const TTrigger & Trigger() const noexcept;
protected:
    OutputValueType & Output(OutputValueType& out) const noexcept;
};

template<typename TTrigger>
Error<error::tag::Catch<TTrigger>>::Error() noexcept :
    TriggerType(),
    m_trigger()
{}

template<typename TTrigger>
template<typename... TArgs>
Error<error::tag::Catch<TTrigger>>::Error(const TTrigger& trigger, 
    const error::id::Catch& id, TArgs&&... args) noexcept :
        m_trigger(trigger),
        TriggerType(id, std::forward<TArgs>(args)...)
{}

template<typename TTrigger>
Error<error::tag::Catch<TTrigger>>::
    Error(const Error<error::tag::Catch<TTrigger>>& cpy) noexcept :
        m_trigger(cpy.m_trigger),
        TriggerType(cpy)

{}

template<typename TTrigger>
Error<error::tag::Catch<TTrigger>>::
    Error(Error<error::tag::Catch<TTrigger>>&& mov) noexcept :
        m_trigger(std::move(mov.m_trigger)),
        TriggerType(std::move(mov))
{}

template<typename TTrigger>
const typename Error<error::tag::Catch<TTrigger>>::CharType * 
Error<error::tag::Catch<TTrigger>>::Message() const noexcept
{
    return "";
}

template<typename TTrigger>
const TTrigger& Error<error::tag::Catch<TTrigger>>::Trigger() const noexcept
{
    return m_trigger;
}

template<typename TTrigger>
typename Error<error::tag::Catch<TTrigger>>::OutputValueType & 
Error<error::tag::Catch<TTrigger>>::Output(OutputValueType& out) const noexcept
{
    error::output::Operator(out, "in catch ");
    TriggerType::Output(out);
    return out;
}

} //!basic

#endif //!BASIC_ERROR_TAG_CATCH_H_

#endif //!BASIC_ERROR_H__FORWARD_DECLARATION_
