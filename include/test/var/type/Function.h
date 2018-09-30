#ifndef BASIC_TEST_VAR_TYPE_FUNCTION_H_
#define BASIC_TEST_VAR_TYPE_FUNCTION_H_

#include "../../Variable.h"

#include "../../type/Function.h"

namespace basic
{
namespace test
{

template<typename TRet, typename... TArgsFunc, 
    TRet(*TPtrFunc)(TArgsFunc...), typename... TArgs>
class Variable<test::type::Function<TRet(TArgsFunc...), TPtrFunc>, TArgs...> :
    public Variable<TArgs...>
{
public:
    typedef test::type::Function<TRet(TArgsFunc...), TPtrFunc>&& ConstGetType;
public:
    template<typename... TValArgs>
    Variable(TValArgs&&... val_args);
    Variable(const Variable<test::type::Function<TRet(TArgsFunc...), TPtrFunc>,
        TArgs...>& cpy) = delete;
    Variable(Variable<test::type::Function<TRet(TArgsFunc...), TPtrFunc>, 
        TArgs...>&&) = delete;
public:
    Variable<test::type::Function<TRet(TArgsFunc...), TPtrFunc>, TArgs...>& 
        operator=(const Variable<test::type::Function<TRet(TArgsFunc...), 
            TPtrFunc>, TArgs...>& cpy);
    Variable<test::type::Function<TRet(TArgsFunc...), TPtrFunc>, TArgs...>& 
        operator=(Variable<test::type::Function<TRet(TArgsFunc...), TPtrFunc>, 
            TArgs...>&&) = delete;
public:
    ConstGetType Get() const;
};

template<typename TRet, typename... TArgsFunc, 
    TRet(*TPtrFunc)(TArgsFunc...), typename... TArgs>
template<typename... TValArgs>
Variable<test::type::Function<TRet(TArgsFunc...), TPtrFunc>, TArgs...>::
    Variable(TValArgs&&... val_args) :
        Variable<TArgs...>(std::forward<TValArgs>(val_args)...)
{}

template<typename TRet, typename... TArgsFunc, 
    TRet(*TPtrFunc)(TArgsFunc...), typename... TArgs>
Variable<test::type::Function<TRet(TArgsFunc...), TPtrFunc>, TArgs...>& 
    Variable<test::type::Function<TRet(TArgsFunc...), TPtrFunc>, TArgs...>::
        operator=(const Variable<test::type::Function<TRet(TArgsFunc...), 
            TPtrFunc>, TArgs...>& cpy)
{
    Variable<TArgs...>::operator=(cpy);
    return *this;
}

template<typename TRet, typename... TArgsFunc, 
    TRet(*TPtrFunc)(TArgsFunc...), typename... TArgs>
typename Variable<test::type::Function<TRet(TArgsFunc...), TPtrFunc>, 
    TArgs...>::ConstGetType Variable<test::type::Function<TRet(TArgsFunc...), 
        TPtrFunc>, TArgs...>::Get() const
{
    return std::move(test::type::Function<TRet(TArgsFunc...), TPtrFunc>{});
}

} //!test

} //!basic


#endif //!BASIC_TEST_VAR_TYPE_FUNCTION_H_
