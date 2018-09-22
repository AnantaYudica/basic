#ifndef BASIC_TEST_VAR_VALUE_H_
#define BASIC_TEST_VAR_VALUE_H_

// todo : Remove when next release
#ifndef REMOVED_DEPRECATED
#define REMOVED_DEPRECATED
#endif //!REMOVED_DEPRECATED

#include "../Value.h"

namespace basic
{
namespace test
{
namespace var
{

template<typename T>
using Value = basic::test::Value<T>;

} //!var

} //!test

} //!basic

// end todo

#include "../Variable.h"

#include "../Value.h"

namespace basic
{
namespace test
{

template<typename TArg, typename... TArgs>
class Variable<test::Value<TArg>, TArgs...> :
    public Variable<TArgs...>
{
private:
    test::Value<TArg> m_value;
public:
    template<typename TValArg, typename... TValArgs>
    Variable(TValArg&& val_arg, TValArgs&&... val_args);
    Variable(const Variable<test::Value<TArg>, TArgs...>& cpy) = delete;
    Variable(Variable<test::Value<TArg>, TArgs...>&&) = delete;
public:
    Variable<test::Value<TArg>, TArgs...>& 
        operator=(const Variable<test::Value<TArg>, TArgs...>& cpy);
    Variable<test::Value<TArg>, TArgs...>& 
        operator=(Variable<test::Value<TArg>, TArgs...>&&) = delete;
public:
    test::Value<TArg>& operator*();
    const test::Value<TArg>& operator*() const;
};

template<typename TArg, typename... TArgs>
template<typename TValArg, typename... TValArgs>
Variable<test::Value<TArg>, TArgs...>::Variable(TValArg&& val_arg, 
    TValArgs&&... val_args) :
        Variable<TArgs...>(std::forward<TValArgs>(val_args)...),
        m_value(std::forward<TValArg>(val_arg))
{}

template<typename TArg, typename... TArgs>
Variable<test::Value<TArg>, TArgs...>& Variable<test::Value<TArg>, TArgs...>::
    operator=(const Variable<test::Value<TArg>, TArgs...>& cpy)
{
    Variable<TArgs...>::operator=(cpy);
    m_value = cpy.m_value;
    return *this;
}


template<typename TArg, typename... TArgs>
test::Value<TArg>& Variable<test::Value<TArg>, TArgs...>::operator*()
{
    return m_value;
}

template<typename TArg, typename... TArgs>
const test::Value<TArg>& Variable<test::Value<TArg>, TArgs...>::
    operator*() const
{
    return m_value;
}

} //!test

} //!basic

#endif //!BASIC_TEST_VAR_VALUE_H_