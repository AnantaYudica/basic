#ifndef BASIC_TEST_VAR_VAL_PARAMETER_H_
#define BASIC_TEST_VAR_VAL_PARAMETER_H_

#include "../../Variable.h"

#include "../../val/Parameter.h"

namespace basic
{
namespace test
{

template<typename... TValuesArg, typename... TArgs>
class Variable<test::val::Parameter<TValuesArg...>, TArgs...> :
        public Variable<TArgs...>
{
public:
    typedef test::val::Parameter<TValuesArg...>& GetType;
    typedef const test::val::Parameter<test::type::
        Parameter<TValuesArg...>>& ConstGetType;
private:
    test::val::Parameter<TValuesArg...> m_value;
public:
    template<typename... TValArgs>
    Variable(TValuesArg&&... vals_arg, TValArgs&&... val_args);
    Variable(const Variable<test::val::Parameter<
        TValuesArg...>, TArgs...>& cpy) = delete;
    Variable(Variable<test::val::Parameter<
        TValuesArg...>, TArgs...>&&) = delete;
public:
    Variable<test::val::Parameter<TValuesArg...>, 
        TArgs...>& operator=(const Variable<test::val::Parameter<
            TValuesArg...>, TArgs...>& cpy);
    Variable<test::val::Parameter<TValuesArg...>, 
        TArgs...>& operator=(Variable<test::val::Parameter<
            TValuesArg...>, TArgs...>&&) = delete;
public:
    GetType Get();
    ConstGetType Get() const;
};

template<typename... TValuesArg, typename... TArgs>
template<typename... TValArgs>
Variable<test::val::Parameter<TValuesArg...>, TArgs...>::
    Variable(TValuesArg&&... vals_arg, TValArgs&&... val_args) :
        Variable<TArgs...>(std::forward<TValArgs>(val_args)...),
        m_value(std::forward<TValuesArg>(vals_arg)...)
{}

template<typename... TValuesArg, typename... TArgs>
Variable<test::val::Parameter<TValuesArg...>, TArgs...>& 
    Variable<test::val::Parameter<TValuesArg...>, TArgs...>::
        operator=(const Variable<test::val::Parameter<
            TValuesArg...>, TArgs...>& cpy)
{
    Variable<TArgs...>::operator=(cpy);
    m_value = cpy.m_value;
    return *this;
}

template<typename... TValuesArg, typename... TArgs>
typename Variable<test::val::Parameter<TValuesArg...>, 
    TArgs...>::GetType Variable<test::val::Parameter<TValuesArg...>, 
        TArgs...>::Get()
{
    return m_value;
}

template<typename... TValuesArg, typename... TArgs>
typename Variable<test::val::Parameter<TValuesArg...>,
    TArgs...>::ConstGetType Variable<test::val::Parameter<TValuesArg...>, 
        TArgs...>::Get() const
{
    return m_value;
}

} //!test

} //!basic

#endif //!BASIC_TEST_VAR_VAL_PARAMETER_H_