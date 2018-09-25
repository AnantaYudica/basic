#ifndef BASIC_TEST_VARIABLE_H_
#define BASIC_TEST_VARIABLE_H_

#include <utility>
#include <type_traits>

namespace basic
{
namespace test
{

template<typename... TArgs>
class Variable
{
public:
    template<typename... TValArgs>
    Variable(TValArgs&&... val_args);
    Variable(const Variable<TArgs...>& cpy) = delete;
    Variable(Variable<TArgs...>&&) = delete;
public:
    Variable<TArgs...>& operator=(const Variable<TArgs...>& cpy);
    Variable<TArgs...>& operator=(Variable<TArgs...>&&) = delete;
public:
    int Get() = delete;
    int Get() const = delete;
};

template<typename TArg, typename... TArgs>
class Variable<TArg, TArgs...> :
    public Variable<TArgs...>
{
public:
    template<typename... TValArgs>
    Variable(TValArgs&&... val_args);
    Variable(const Variable<TArg, TArgs...>& cpy) = delete;
    Variable(Variable<TArg, TArgs...>&&) = delete;
public:
    Variable<TArg, TArgs...>& operator=(const Variable<TArg, TArgs...>& cpy);
    Variable<TArg, TArgs...>& operator=(Variable<TArg, TArgs...>&&) = delete;
public:
    int Get() = delete;
    int Get() const = delete;
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
    typename std::enable_if<decltype(LValue<typename Definition<I, TArg, 
        TArgs...>::Type>(0))::value && I != 0, 
            typename Definition<I, TArg, TArgs...>::ValueType>::type GetValue()
    {
        return Variable<TArgs...>::template GetValue<I - 1>();
    }
// end todo
};

template<typename... TArgs>
template<typename... TValArgs>
Variable<TArgs...>::Variable(TValArgs&&... val_args)
{}

template<typename... TArgs>
Variable<TArgs...>& Variable<TArgs...>::
    operator=(const Variable<TArgs...>& cpy)
{
    return *this;
}

template<typename TArg, typename... TArgs>
template<typename... TValArgs>
Variable<TArg, TArgs...>::Variable(TValArgs&&... val_args) :
    Variable<TArgs...>(std::forward<TValArgs>(val_args)...)
{}

template<typename TArg, typename... TArgs>
Variable<TArg, TArgs...>& Variable<TArg, TArgs...>::
    operator=(const Variable<TArg, TArgs...>& cpy)
{
    Variable<TArgs...>::operator=(cpy);
    return *this;
}

} //!test

} //!basic

#endif //!BASIC_TEST_VARIABLE_H_
