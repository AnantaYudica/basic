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
    ConstGetType Get() const;
// todo : Remove when next release
#ifndef REMOVED_DEPRECATED
#define REMOVED_DEPRECATED
#endif //!REMOVED_DEPRECATED
    template<std::size_t I, typename TDefArg, typename... TDefArgs>
    struct _Definition
    {
        typedef typename _Definition<I - 1, TDefArgs...>::ValueType ValueType;
        typedef typename _Definition<I - 1, TDefArgs...>::Type Type;
    };
    template<typename TDefArg, typename... TDefArgs>
    struct _Definition<0, TDefArg, TDefArgs...>
    {
        typedef typename TDefArg::Type ValueType;
        typedef TDefArg Type;
    };
    template<typename TVar>
    static constexpr auto _LValue(int) -> decltype(
        static_cast<typename TVar::GetType(TVar::*)()>(&TVar::Get), 
            std::true_type());
    template<typename TVar>
    static constexpr std::false_type _LValue(...);
public:
    template<std::size_t I>
    typename std::enable_if<decltype(_LValue<typename _Definition<I, 
        test::type::Value<TArg, TArgValue>, TArgs...>::Type>(0))::value && 
            I != 0, typename _Definition<I, TArg, TArgs...>::ValueType>::type 
                GetValue()
    {
        return Variable<TArgs...>::template GetValue<I - 1>();
    }
// end todo
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
