#ifndef BASIC_TEST_VAR_VAL_SEQUENCE_H_
#define BASIC_TEST_VAR_VAL_SEQUENCE_H_

#include "../../Variable.h"

#include "../../val/Sequence.h"

#include <utility>

namespace basic
{
namespace test
{
namespace var
{
namespace val
{

template<typename TValue, std::size_t S, typename TVariable, std::size_t I = S,
    typename... TValues>
class Sequence :
    public Sequence<TValue, S, TVariable, I - 1, TValue, TValues...>
{
public:
    typedef typename Sequence<TValue, S, TVariable, I - 1, TValue,
        TValues...>::GetType GetType;
    typedef typename Sequence<TValue, S, TVariable, I - 1, TValue,
        TValues...>::ConstGetType ConstGetType;
public:
    template<typename... TValArgs>
    Sequence(TValArgs&&... val_args);
    Sequence(const Sequence<TValue, S, TVariable, I, 
        TValues...>& cpy) = delete;
    Sequence(Sequence<TValue, S, TVariable, I, TValues...>&&) = delete;
public:
    Sequence<TValue, S, TVariable, I, TValues...>& 
        operator=(const Sequence<TValue, S, TVariable, I, TValues...>& cpy);
    Sequence<TValue, S, TVariable, I, TValues...>& 
        operator=(Sequence<TValue, S, TVariable, I, TValues...>&&) = delete;
protected:
    using Sequence<TValue, S, TVariable, I - 1, TValue, TValues...>::Get;
};

template<typename TValue, std::size_t S, typename TVariable, 
    typename... TValues>
class Sequence<TValue, S, TVariable, 0, TValues...> :
    public TVariable
{
public:
    typedef test::val::Sequence<TValue, S>& GetType;
    typedef const test::val::Sequence<TValue, S>& ConstGetType;
private:
    test::val::Sequence<TValue, S> m_values;
public:
    template<typename... TValArgs>
    Sequence(TValues&&... vals, TValArgs&&... val_args);
    Sequence(const Sequence<TValue, S, TVariable, 0, 
        TValues...>& cpy) = delete;
    Sequence(Sequence<TValue, S, TVariable, 0, TValues...>&&) = delete;
public:
    Sequence<TValue, S, TVariable, 0, TValues...>& 
        operator=(const Sequence<TValue, S, TVariable, 0, TValues...>& cpy);
    Sequence<TValue, S, TVariable, 0, TValues...>& 
        operator=(Sequence<TValue, S, TVariable, 0, TValues...>&&) = delete;
protected:
    GetType Get();
    ConstGetType Get() const;
};

template<typename TValue, std::size_t S, typename TVariable, std::size_t I,
    typename... TValues>
template<typename... TValArgs>
Sequence<TValue, S, TVariable, I, TValues...>::
    Sequence(TValArgs&&... val_args) :
        Sequence<TValue, S, TVariable, I - 1, TValue, 
            TValues...>(std::forward<TValArgs>(val_args)...)
{}

template<typename TValue, std::size_t S, typename TVariable, std::size_t I,
    typename... TValues>
Sequence<TValue, S, TVariable, I, TValues...>& 
    Sequence<TValue, S, TVariable, I, TValues...>::
        operator=(const Sequence<TValue, S, TVariable, I, TValues...>& cpy)
{
    Sequence<TValue, S, TVariable, I, TValue, TValues...>::operator=(cpy);
    return *this;
}

template<typename TValue, std::size_t S, typename TVariable, 
    typename... TValues>
template<typename... TValArgs>
Sequence<TValue, S, TVariable, 0, TValues...>::
    Sequence(TValues&&... vals, TValArgs&&... val_args) :
        TVariable(std::forward<TValArgs>(val_args)...),
        m_values(std::forward<TValues>(vals)...)
{}

template<typename TValue, std::size_t S, typename TVariable, 
    typename... TValues>
Sequence<TValue, S, TVariable, 0, TValues...>& 
    Sequence<TValue, S, TVariable, 0, TValues...>::
        operator=(const Sequence<TValue, S, TVariable, 0, TValues...>& cpy)
{
    TVariable::operator=(cpy);
    m_values = cpy.m_values;
    return *this;
}

template<typename TValue, std::size_t S, typename TVariable, 
    typename... TValues>
typename Sequence<TValue, S, TVariable, 0, TValues...>::GetType 
    Sequence<TValue, S, TVariable, 0, TValues...>::Get()
{
    return m_values;
}

template<typename TValue, std::size_t S, typename TVariable, 
    typename... TValues>
typename Sequence<TValue, S, TVariable, 0, TValues...>::ConstGetType 
    Sequence<TValue, S, TVariable, 0, TValues...>::Get() const
{
    return m_values;
}


} //!val

} //!var

template<typename TArg, std::size_t S, typename... TArgs>
class Variable<test::val::Sequence<TArg, S>, TArgs...> :
    public test::var::val::Sequence<TArg, S, Variable<TArgs...>>
{
public:
    typedef typename test::var::val::Sequence<TArg, S, 
        Variable<TArgs...>>::GetType GetType;
    typedef typename test::var::val::Sequence<TArg, S, 
        Variable<TArgs...>>::ConstGetType ConstGetType;
public:
    template<typename... TValArgs>
    Variable(TValArgs&&... val_args);
    Variable(const Variable<test::val::Sequence<TArg, S>, 
        TArgs...>& cpy) = delete;
    Variable(Variable<test::val::Sequence<TArg, S>, TArgs...>&&) = delete;
public:
    Variable<test::val::Sequence<TArg, S>, TArgs...>& 
        operator=(const Variable<test::val::Sequence<TArg, S>, TArgs...>& cpy);
    Variable<test::val::Sequence<TArg, S>, TArgs...>& 
        operator=(Variable<test::val::Sequence<TArg, S>, TArgs...>&&) = delete;
public:
    using test::var::val::Sequence<TArg, S, Variable<TArgs...>>::Get;
};

template<typename TArg, std::size_t S, typename... TArgs>
template<typename... TValArgs>
Variable<test::val::Sequence<TArg, S>, TArgs...>::
    Variable(TValArgs&&... val_args) :
        test::var::val::Sequence<TArg, S, 
            Variable<TArgs...>>(std::forward<TValArgs>(val_args)...)
{}

template<typename TArg, std::size_t S, typename... TArgs>
Variable<test::val::Sequence<TArg, S>, TArgs...>& 
    Variable<test::val::Sequence<TArg, S>, TArgs...>::
        operator=(const Variable<test::val::Sequence<TArg, S>, TArgs...>& cpy)
{
    test::var::val::Sequence<TArg, S, Variable<TArgs...>>::operator=(cpy);
    return *this;
}
} //!test

} //!basic

#endif //!BASIC_TEST_VAR_VAL_SEQUENCE_H_