#ifndef BASIC_TEST_VAR_TYPE_VALUE_H_
#define BASIC_TEST_VAR_TYPE_VALUE_H_

#include "../../Variable.h"

#include "../../type/Value.h"

namespace basic
{
namespace test
{

template<typename TArg, TArg TArgValue, typename... TArgs>
class Variable<test::type::Value<TArg, TArgValue>, TArgs...> :
    public Variable<TArgs...>
{
public:
    typedef test::type::Value<TArg, TArgValue>&& ConstGetType;
public:
    template<typename... TValArgs>
    Variable(TValArgs&&... val_args);
    Variable(const Variable<test::type::Value<TArg, TArgValue>, 
        TArgs...>& cpy) = delete;
    Variable(Variable<test::type::Value<TArg, TArgValue>, 
        TArgs...>&&) = delete;
public:
    Variable<test::type::Value<TArg, TArgValue>, TArgs...>& 
        operator=(const Variable<test::type::Value<TArg, TArgValue>, 
            TArgs...>& cpy);
    Variable<test::type::Value<TArg, TArgValue>, TArgs...>& 
        operator=(Variable<test::type::Value<TArg, TArgValue>, 
            TArgs...>&&) = delete;
public:
    void Get() = delete;
    ConstGetType Get() const;
};

template<typename TArg, TArg TArgValue, typename... TArgs>
template<typename... TValArgs>
Variable<test::type::Value<TArg, TArgValue>, TArgs...>::
    Variable(TValArgs&&... val_args) :
        Variable<TArgs...>(std::forward<TValArgs>(val_args)...)
{}

template<typename TArg, TArg TArgValue, typename... TArgs>
Variable<test::type::Value<TArg, TArgValue>, TArgs...>& 
    Variable<test::type::Value<TArg, TArgValue>, TArgs...>::
        operator=(const Variable<test::type::Value<TArg, TArgValue>, 
            TArgs...>& cpy)
{
    Variable<TArgs...>::operator=(cpy);
    return *this;
}

template<typename TArg, TArg TArgValue, typename... TArgs>
typename Variable<test::type::Value<TArg, TArgValue>, TArgs...>::ConstGetType 
    Variable<test::type::Value<TArg, TArgValue>, TArgs...>::Get() const
{
    return std::move(test::type::Value<TArg, TArgValue>{});
}

} //!test

} //!basic


#endif //!BASIC_TEST_VAR_TYPE_VALUE_H_
