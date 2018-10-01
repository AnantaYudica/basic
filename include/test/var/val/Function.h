#ifndef BASIC_TEST_VAR_VAL_FUNCTION_H_
#define BASIC_TEST_VAR_VAL_FUNCTION_H_

#include "../../Variable.h"

#include "../../val/Function.h"

#include <utility>

namespace basic
{
namespace test
{

template<typename TRet, typename... TArgsFunc, typename... TArgs>
class Variable<test::val::Function<TRet(TArgsFunc...)>, TArgs...> :
        public Variable<TArgs...>
{
public:
    typedef test::val::Function<TRet(TArgsFunc...)>& GetType;
    typedef const test::val::Function<TRet(TArgsFunc...)>& ConstGetType;
private:
    test::val::Function<TRet(TArgsFunc...)> m_value;
public:
    template<typename... TValArgs>
    Variable(TRet(*&&func)(TArgsFunc...), TValArgs&&... val_args);
    Variable(const Variable<test::val::Function<TRet(TArgsFunc...)>, 
        TArgs...>& cpy) = delete;
    Variable(Variable<test::val::Function<TRet(TArgsFunc...)>, 
        TArgs...>&&) = delete;
public:
    Variable<test::val::Function<TRet(TArgsFunc...)>, TArgs...>& 
        operator=(const Variable<test::val:: Function<TRet(TArgsFunc...)>, 
            TArgs...>& cpy);
    Variable<test::val::Function<TRet(TArgsFunc...)>, TArgs...>& 
        operator=(Variable<test::val::Function<TRet(TArgsFunc...)>, 
            TArgs...>&&) = delete;
public:
    GetType Get();
    ConstGetType Get() const;
};

template<typename TRet, typename... TArgsFunc, typename... TArgs>
template<typename... TValArgs>
Variable<test::val::Function<TRet(TArgsFunc...)>, TArgs...>::
    Variable(TRet(*&&func)(TArgsFunc...), TValArgs&&... val_args) :
        Variable<TArgs...>(std::forward<TValArgs>(val_args)...),
        m_value(std::forward<TRet(*)(TArgsFunc...)>(func))
{}

template<typename TRet, typename... TArgsFunc, typename... TArgs>
Variable<test::val::Function<TRet(TArgsFunc...)>, TArgs...>& 
    Variable<test::val::Function<TRet(TArgsFunc...)>, TArgs...>::
        operator=(const Variable<test::val::Function<TRet(TArgsFunc...)>, 
            TArgs...>& cpy)
{
    Variable<TArgs...>::operator=(cpy);
    m_value = cpy.m_value;
    return *this;
}

template<typename TRet, typename... TArgsFunc, typename... TArgs>
typename Variable<test::val::Function<TRet(TArgsFunc...)>, 
    TArgs...>::GetType Variable<test::val::Function<TRet(TArgsFunc...)>, 
        TArgs...>::Get()
{
    return m_value;
}

template<typename TRet, typename... TArgsFunc, typename... TArgs>
typename Variable<test::val::Function<TRet(TArgsFunc...)>,
    TArgs...>::ConstGetType Variable<test::val::Function<TRet(TArgsFunc...)>, 
        TArgs...>::Get() const
{
    return m_value;
}

} //!test

} //!basic

#endif //!BASIC_TEST_VAR_VAL_FUNCTION_H_
