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
};


template<typename T, T TValue, T... TValues>
class Sequence<T, TValue, TValues...>
{
public:
    typedef T Type;
    typedef Type ConstAtType;
public:
    static constexpr std::size_t Size = sizeof...(TValues) + 1;
public:
    template<std::size_t I>
    constexpr typename std::enable_if<I == 0, ConstAtType>::type At() const;
    template<std::size_t I>
    constexpr typename std::enable_if<I != 0, ConstAtType>::type At() const;
};

template<typename T, T TValue, T... TValues>
template<std::size_t I>
constexpr typename std::enable_if<I == 0, 
    typename Sequence<T, TValue, TValues...>::ConstAtType>::type 
        Sequence<T, TValue, TValues...>::At() const
{
    return TValue;
}

template<typename T, T TValue, T... TValues>
template<std::size_t I>
constexpr typename std::enable_if<I != 0, 
    typename Sequence<T, TValue, TValues...>::ConstAtType>::type 
        Sequence<T, TValue, TValues...>::At() const
{
    return Sequence<T, TValues...>{}.template At<I - 1>();
}

} //!val

} //!type

} //!test

} //!basic

#endif //!BASIC_TEST_TYPE_VAL_SEQUENCE_H_

