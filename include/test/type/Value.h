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
    typedef Type GetType;
public:
    static constexpr GetType Get();
public:
    Value();
    T operator*() const;
};

template<typename T, T ValueT>
constexpr typename Value<T, ValueT>::GetType 
    Value<T, ValueT>::Get()
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

