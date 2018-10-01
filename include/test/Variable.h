#ifndef BASIC_TEST_VARIABLE_H_
#define BASIC_TEST_VARIABLE_H_

#include <utility>
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
public:
    int Get() = delete;
    int Get() const = delete;
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
    int Get() = delete;
    int Get() const = delete;
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

} //!test

} //!basic

#endif //!BASIC_TEST_VARIABLE_H_
