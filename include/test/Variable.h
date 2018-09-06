#ifndef BASIC_TEST_VARIABLE_H_
#define BASIC_TEST_VARIABLE_H_

#include "var/Value.h"
#include "var/val/Definition.h"

#include <cstddef>
#include <type_traits>

namespace basic
{
namespace test
{

template<typename... TArgs>
class Variable
{
public:
    template<typename... TValArgs>
    Variable(TValArgs&&... val_args);
    Variable(const Variable<TArgs...>& cpy) = delete;
    Variable(Variable<TArgs...>&&) = delete;
public:
    Variable<TArgs...>& operator=(const Variable<TArgs...>& cpy);
    Variable<TArgs...>& operator=(Variable<TArgs...>&&) = delete;
};

template<typename TArg, typename... TArgs>
class Variable<TArg, TArgs...> :
    public Variable<TArgs...>
{
public:
    template<typename... TValArgs>
    Variable(TValArgs&&... val_args);
    Variable(const Variable<TArg, TArgs...>& cpy) = delete;
    Variable(Variable<TArg, TArgs...>&&) = delete;
public:
    Variable<TArg, TArgs...>& operator=(const Variable<TArg, TArgs...>& cpy);
    Variable<TArg, TArgs...>& operator=(Variable<TArg, TArgs...>&&) = delete;
public:
    template<std::size_t I>
    typename std::enable_if<var::val::Definition<I, TArg, TArgs...>::HasValue
        && I != 0, typename var::val::Definition<I, TArg, TArgs...>::Type>::
        type GetValue();
};

template<typename TArg, typename... TArgs>
class Variable<var::Value<TArg>, TArgs...> :
    public Variable<TArgs...>
{
private:
    var::Value<TArg> m_value;
public:
    template<typename TValArg, typename... TValArgs>
    Variable(TValArg&& val_arg, TValArgs&&... val_args);
    Variable(const Variable<var::Value<TArg>, TArgs...>& cpy) = delete;
    Variable(Variable<var::Value<TArg>, TArgs...>&&) = delete;
public:
    Variable<var::Value<TArg>, TArgs...>& 
        operator=(const Variable<var::Value<TArg>, TArgs...>& cpy);
    Variable<var::Value<TArg>, TArgs...>& 
        operator=(Variable<var::Value<TArg>, TArgs...>&&) = delete;
public:
    template<std::size_t I>
    typename std::enable_if<var::val::Definition<I, var::Value<TArg>, 
        TArgs...>::HasValue && I != 0, typename var::val::Definition<I, 
        var::Value<TArg>, TArgs...>::Type>::type GetValue();
    template<std::size_t I>
    typename std::enable_if<var::val::Definition<I, var::Value<TArg>, 
        TArgs...>::HasValue && I == 0, typename var::val::Definition<I, 
        var::Value<TArg>, TArgs...>::Type>::type GetValue();
};

template<typename... TArgs>
template<typename... TValArgs>
Variable<TArgs...>::Variable(TValArgs&&... val_args)
{}

template<typename... TArgs>
Variable<TArgs...>& Variable<TArgs...>::
    operator=(const Variable<TArgs...>& cpy)
{
    return *this;
}

template<typename TArg, typename... TArgs>
template<typename... TValArgs>
Variable<TArg, TArgs...>::Variable(TValArgs&&... val_args) :
    Variable<TArgs...>(std::forward<TValArgs>(val_args)...)
{}

template<typename TArg, typename... TArgs>
Variable<TArg, TArgs...>& Variable<TArg, TArgs...>::
    operator=(const Variable<TArg, TArgs...>& cpy)
{
    Variable<TArgs...>::operator=(cpy);
    return *this;
}

template<typename TArg, typename... TArgs>
template<std::size_t I>
typename std::enable_if<var::val::Definition<I, TArg, TArgs...>::HasValue
    && I != 0, typename var::val::Definition<I, TArg, TArgs...>::Type>::type
    Variable<TArg, TArgs...>::GetValue()
{
    return Variable<TArgs...>::template GetValue<I - 1>();
}

template<typename TArg, typename... TArgs>
template<typename TValArg, typename... TValArgs>
Variable<var::Value<TArg>, TArgs...>::Variable(TValArg&& val_arg, 
    TValArgs&&... val_args) :
        Variable<TArgs...>(std::forward<TValArgs>(val_args)...),
        m_value(std::forward<TValArg>(val_arg))
{}

template<typename TArg, typename... TArgs>
Variable<var::Value<TArg>, TArgs...>& Variable<var::Value<TArg>, TArgs...>::
    operator=(const Variable<var::Value<TArg>, TArgs...>& cpy)
{
    Variable<TArgs...>::operator=(cpy);
    m_value = cpy.m_value;
    return *this;
}

template<typename TArg, typename... TArgs>
template<std::size_t I>
typename std::enable_if<var::val::Definition<I, var::Value<TArg>, 
    TArgs...>::HasValue && I != 0, typename var::val::Definition<I, 
    var::Value<TArg>, TArgs...>::Type>::type 
    Variable<var::Value<TArg>, TArgs...>::GetValue()
{
    return Variable<TArgs...>::template GetValue<I - 1>();
}

template<typename TArg, typename... TArgs>
template<std::size_t I>
typename std::enable_if<var::val::Definition<I, var::Value<TArg>, TArgs...>::HasValue
    && I == 0, typename var::val::Definition<I, var::Value<TArg>, TArgs...>::Type>::type
    Variable<var::Value<TArg>, TArgs...>::GetValue()
{
    return m_value.Get();
}

} //!test

} //!basic

#endif //!BASIC_TEST_VARIABLE_H_
