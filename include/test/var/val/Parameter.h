#ifndef BASIC_TEST_VAR_VAL_PARAMETER_H_
#define BASIC_TEST_VAR_VAL_PARAMETER_H_

#include "../../Variable.h"

#include "../../type/Parameter.h"
#include "../../val/Parameter.h"

namespace basic
{
namespace test
{

template<typename... TValuesArg, typename... TArgs>
class Variable<test::val::Parameter<
    test::type::Parameter<TValuesArg...>>, TArgs...> :
        public Variable<TArgs...>
{
private:
    test::val::Parameter<test::type::Parameter<TValuesArg...>> m_value;
public:
    template<typename... TValArgs>
    Variable(TValuesArg&&... vals_arg, TValArgs&&... val_args);
    Variable(const Variable<test::val::Parameter<
        test::type::Parameter<TValuesArg...>>, TArgs...>& cpy) = delete;
    Variable(Variable<test::val::Parameter<
        test::type::Parameter<TValuesArg...>>, TArgs...>&&) = delete;
public:
    Variable<test::val::Parameter<test::type::Parameter<TValuesArg...>>, 
        TArgs...>& operator=(const Variable<test::val::Parameter<
            test::type::Parameter<TValuesArg...>>, TArgs...>& cpy);
    Variable<test::val::Parameter<test::type::Parameter<TValuesArg...>>, 
        TArgs...>& operator=(Variable<test::val::Parameter<
            test::type::Parameter<TValuesArg...>>, TArgs...>&&) = delete;
public:
    test::val::Parameter<test::type::Parameter<TValuesArg...>>& operator*();
    const test::val::Parameter<test::type::Parameter<TValuesArg...>>& 
        operator*() const;
};

template<typename... TValuesArg, typename... TArgs>
template<typename... TValArgs>
Variable<test::val::Parameter<test::type::Parameter<TValuesArg...>>, 
    TArgs...>::Variable(TValuesArg&&... vals_arg, TValArgs&&... val_args) :
        Variable<TArgs...>(std::forward<TValArgs>(val_args)...),
        m_value(std::forward<TValuesArg>(vals_arg)...)
{}

template<typename... TValuesArg, typename... TArgs>
Variable<test::val::Parameter<test::type::Parameter<TValuesArg...>>, 
    TArgs...>& Variable<test::val::Parameter<
        test::type::Parameter<TValuesArg...>>, TArgs...>::
            operator=(const Variable<test::val::Parameter<
                test::type::Parameter<TValuesArg...>>, TArgs...>& cpy)
{
    Variable<TArgs...>::operator=(cpy);
    m_value = cpy.m_value;
    return *this;
}

template<typename... TValuesArg, typename... TArgs>
test::val::Parameter<test::type::Parameter<TValuesArg...>>& 
    Variable<test::val::Parameter<test::type::Parameter<TValuesArg...>>, 
        TArgs...>::operator*()
{
    return m_value;
}

template<typename... TValuesArg, typename... TArgs>
const test::val::Parameter<test::type::Parameter<TValuesArg...>>& 
    Variable<test::val::Parameter<test::type::Parameter<TValuesArg...>>, 
        TArgs...>::operator*() const
{
    return m_value;
}

} //!test

} //!basic

#endif //!BASIC_TEST_VAR_VAL_PARAMETER_H_