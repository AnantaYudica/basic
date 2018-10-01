#ifndef BASIC_TEST_VALUE_H_
#define BASIC_TEST_VALUE_H_

#include <utility>

namespace basic
{
namespace test
{

template<typename T>
class Value
{
public:
    typedef T Type;
    typedef Type& GetType;
    typedef const Type& ConstGetType;
private:
    T m_value;
public:
    Value();
    Value(const T& val);
    Value(const Value<T>& cpy);
    Value(Value<T>&& mov);
public:
    Value<T>& operator=(const Value<T>& cpy);
    Value<T>& operator=(Value<T>&& mov);
public:
    GetType Get();
    ConstGetType Get() const;
};

template<typename T>
Value<T>::Value()
{};

template<typename T>
Value<T>::Value(const T& val) :
    m_value(val)
{}

template<typename T>
Value<T>::Value(const Value<T>& cpy) :
    m_value(cpy.m_value)
{}

template<typename T>
Value<T>::Value(Value<T>&& mov) :
    m_value(std::move(mov.m_value))
{}

template<typename T>
Value<T>& Value<T>::operator=(const Value<T>& cpy)
{
    m_value = cpy.m_value;
    return *this;
}

template<typename T>
Value<T>& Value<T>::operator=(Value<T>&& mov)
{
    m_value = std::move(mov);
    return *this;
}

template<typename T>
typename Value<T>::GetType Value<T>::Get()
{
    return m_value;
}

template<typename T>
typename Value<T>::ConstGetType Value<T>::Get() const
{
    return m_value;
}

} //!test

}//!basic

#endif //!BASIC_TEST_VALUE_H_
