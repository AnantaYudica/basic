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
public:
    typedef test::Value<TArg>& GetType;
    typedef const test::Value<TArg>& ConstGetType;
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
    GetType Get();
    ConstGetType Get() const;
// todo : Remove when next release
#ifndef REMOVED_DEPRECATED
#define REMOVED_DEPRECATED
#endif //!REMOVED_DEPRECATED
    template<std::size_t I, typename TDefArg, typename... TDefArgs>
    struct Definition
    {
        typedef typename Definition<I - 1, TDefArgs...>::ValueType ValueType;
        typedef typename Definition<I - 1, TDefArgs...>::Type Type;
    };
    template<typename TDefArg, typename... TDefArgs>
    struct Definition<0, TDefArg, TDefArgs...>
    {
        typedef typename TDefArg::Type ValueType;
        typedef TDefArg Type;
    };
    template<typename TVar>
    static constexpr auto LValue(int) -> decltype(
        static_cast<typename TVar::GetType(TVar::*)()>(&TVar::Get), 
            std::true_type());
    template<typename TVar>
    static constexpr std::false_type LValue(...);
public:
    template<std::size_t I>
    typename std::enable_if<decltype(LValue<typename Definition<I, test::Value<TArg>, 
        TArgs...>::Type>(0))::value
        && I != 0, typename Definition<I, test::Value<TArg>, TArgs...>::ValueType>::
        type GetValue()
    {
        return Variable<TArgs...>::template GetValue<I - 1>();
    }
    template<std::size_t I>
    typename std::enable_if<decltype(LValue<typename Definition<I, test::Value<TArg>, 
        TArgs...>::Type>(0))::value
        && I == 0, typename Definition<I, test::Value<TArg>, TArgs...>::ValueType>::
        type GetValue()
    {
        return m_value.Get();
    }
// end todo
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
typename Variable<test::Value<TArg>, TArgs...>::GetType 
    Variable<test::Value<TArg>, TArgs...>::Get()
{
    return m_value;
}

template<typename TArg, typename... TArgs>
typename Variable<test::Value<TArg>, TArgs...>::ConstGetType 
    Variable<test::Value<TArg>, TArgs...>::Get() const
{
    return m_value;
}

} //!test

} //!basic

#endif //!BASIC_TEST_VAR_VALUE_H_