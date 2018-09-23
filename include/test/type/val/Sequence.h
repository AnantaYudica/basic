#ifndef BASIC_TEST_TYPE_VAL_SEQUENCE_H_
#define BASIC_TEST_TYPE_VAL_SEQUENCE_H_

#include <utility>
#include <type_traits>

namespace basic
{
namespace test
{
namespace type
{
namespace val
{

template<typename T, T... TValues>
class Sequence
{
public:
    typedef T Type;
public:
    static constexpr std::size_t Size = sizeof...(TValues);
    static constexpr std::size_t size = sizeof...(TValues);
};


template<typename T, T TValue, T... TValues>
class Sequence<T, TValue, TValues...>
{
public:
    typedef T Type;
public:
    static constexpr std::size_t Size = sizeof...(TValues) + 1;
    static constexpr std::size_t size = sizeof...(TValues) + 1;
public:
    template<std::size_t I>
    static constexpr typename std::enable_if<I == 0, T>::type Get();
    template<std::size_t I>
    static constexpr typename std::enable_if<I != 0, T>::type Get();
};

template<typename T, T TValue, T... TValues>
template<std::size_t I>
constexpr typename std::enable_if<I == 0, T>::type 
    Sequence<T, TValue, TValues...>::Get()
{
    return TValue;
}

template<typename T, T TValue, T... TValues>
template<std::size_t I>
constexpr typename std::enable_if<I != 0, T>::type 
    Sequence<T, TValue, TValues...>::Get()
{
    return Sequence<T, TValues...>::template Get<I - 1>();
}

} //!val

} //!type

} //!test

} //!basic

#endif //!BASIC_TEST_TYPE_VAL_SEQUENCE_H_

