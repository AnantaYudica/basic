#ifndef BASIC_TEST_VAR_TYPE_VAL_SEQUENCE_H_
#define BASIC_TEST_VAR_TYPE_VAL_SEQUENCE_H_

#include "../../../Variable.h"

#include "../../../type/val/Sequence.h"

namespace basic
{
namespace test
{

template<typename TArg, TArg... TArgValues, typename... TArgs>
class Variable<test::type::val::Sequence<TArg, TArgValues...>, TArgs...> :
    public Variable<TArgs...>
{
public:
    typedef test::type::val::Sequence<TArg, TArgValues...>&& ConstGetType;
public:
    template<typename... TValArgs>
    Variable(TValArgs&&... val_args);
    Variable(const Variable<test::type::val::Sequence<TArg, 
        TArgValues...>, TArgs...>& cpy) = delete;
    Variable(Variable<test::type::val::Sequence<TArg, 
        TArgValues...>, TArgs...>&&) = delete;
public:
    Variable<test::type::val::Sequence<TArg, TArgValues...>, TArgs...>& 
        operator=(const Variable<test::type::val::Sequence<TArg, 
            TArgValues...>, TArgs...>& cpy);
    Variable<test::type::val::Sequence<TArg, TArgValues...>, TArgs...>& 
        operator=(Variable<test::type::val::Sequence<TArg, TArgValues...>, 
            TArgs...>&&) = delete;
public:
    ConstGetType Get() const;
};

template<typename TArg, TArg... TArgValues, typename... TArgs>
template<typename... TValArgs>
Variable<test::type::val::Sequence<TArg, TArgValues...>, TArgs...>::
    Variable(TValArgs&&... val_args) :
        Variable<TArgs...>(std::forward<TValArgs>(val_args)...)
{}

template<typename TArg, TArg... TArgValues, typename... TArgs>
Variable<test::type::val::Sequence<TArg, TArgValues...>, TArgs...>& 
    Variable<test::type::val::Sequence<TArg, TArgValues...>, TArgs...>::
        operator=(const Variable<test::type::val::Sequence<TArg, 
            TArgValues...>, TArgs...>& cpy)
{
    Variable<TArgs...>::operator=(cpy);
    return *this;
}

template<typename TArg, TArg... TArgValues, typename... TArgs>
typename Variable<test::type::val::Sequence<TArg, TArgValues...>, TArgs...>::
    ConstGetType Variable<test::type::val::Sequence<TArg, TArgValues...>, 
        TArgs...>::Get() const
{
    return std::move(test::type::val::Sequence<TArg, TArgValues...>{});
}

} //!test

} //!basic


#endif //!BASIC_TEST_VAR_TYPE_VAL_SEQUENCE_H_
