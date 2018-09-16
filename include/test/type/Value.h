#ifndef BASIC_TEST_TYPE_VALUE_H_
#define BASIC_TEST_TYPE_VALUE_H_

namespace basic
{
namespace test
{
namespace type
{

template<typename T, T ValueT>
class Value
{
public:
    typedef T Type;
public:
    static constexpr T Get();
public:
    Value();
    T operator*() const;
};

template<typename T, T ValueT>
constexpr T Value<T, ValueT>::Get()
{
    return ValueT;
}

template<typename T, T ValueT>
Value<T, ValueT>::Value()
{};

template<typename T, T ValueT>
T Value<T, ValueT>::operator*() const
{
    return ValueT;
}


} //!type

} //!test

} //!basic

#endif //!BASIC_TEST_TYPE_VALUE_H_

