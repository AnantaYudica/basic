#ifndef BASIC_TEST_VAR_VAL_PARAMETER_H_
#define BASIC_TEST_VAR_VAL_PARAMETER_H_

#include "../Variable.h"

#include "../Parameter.h"

namespace basic
{
namespace test
{

template<typename... TValuesArg, typename... TArgs>
class Variable<test::Parameter<TValuesArg...>, TArgs...> :
        public Variable<TArgs...>
{
public:
    typedef test::Parameter<TValuesArg...>& GetType;
    typedef const test::Parameter<test::type::
        Parameter<TValuesArg...>>& ConstGetType;
private:
    test::Parameter<TValuesArg...> m_value;
public:
    template<typename... TValArgs>
    Variable(TValuesArg&&... vals_arg, TValArgs&&... val_args);
    Variable(const Variable<test::Parameter<
        TValuesArg...>, TArgs...>& cpy) = delete;
    Variable(Variable<test::Parameter<
        TValuesArg...>, TArgs...>&&) = delete;
public:
    Variable<test::Parameter<TValuesArg...>, 
        TArgs...>& operator=(const Variable<test::Parameter<
            TValuesArg...>, TArgs...>& cpy);
    Variable<test::Parameter<TValuesArg...>, 
        TArgs...>& operator=(Variable<test::Parameter<
            TValuesArg...>, TArgs...>&&) = delete;
public:
    GetType Get();
    ConstGetType Get() const;
};

template<typename... TValuesArg, typename... TArgs>
template<typename... TValArgs>
Variable<test::Parameter<TValuesArg...>, TArgs...>::
    Variable(TValuesArg&&... vals_arg, TValArgs&&... val_args) :
        Variable<TArgs...>(std::forward<TValArgs>(val_args)...),
        m_value(std::forward<TValuesArg>(vals_arg)...)
{}

template<typename... TValuesArg, typename... TArgs>
Variable<test::Parameter<TValuesArg...>, TArgs...>& 
    Variable<test::Parameter<TValuesArg...>, TArgs...>::
        operator=(const Variable<test::Parameter<
            TValuesArg...>, TArgs...>& cpy)
{
    Variable<TArgs...>::operator=(cpy);
    m_value = cpy.m_value;
    return *this;
}

template<typename... TValuesArg, typename... TArgs>
typename Variable<test::Parameter<TValuesArg...>, 
    TArgs...>::GetType Variable<test::Parameter<TValuesArg...>, 
        TArgs...>::Get()
{
    return m_value;
}

template<typename... TValuesArg, typename... TArgs>
typename Variable<test::Parameter<TValuesArg...>,
    TArgs...>::ConstGetType Variable<test::Parameter<TValuesArg...>, 
        TArgs...>::Get() const
{
    return m_value;
}

} //!test

} //!basic

#endif //!BASIC_TEST_VAR_VAL_PARAMETER_H_