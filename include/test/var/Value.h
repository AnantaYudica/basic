#ifndef BASIC_TEST_VAR_VALUE_H_
#define BASIC_TEST_VAR_VALUE_H_

#include <utility>

namespace basic
{
namespace test
{
namespace var
{

template<typename T>
class Value
{
private:
    T m_value;
public:
    Value(const T& val);
    Value(const Value<T>& cpy);
    Value(Value<T>&& mov);
public:
    Value<T>& operator=(const Value<T>& cpy);
    Value<T>& operator=(Value<T>&& mov);
public:
    T Get();
    const T& Get() const;
};

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
T Value<T>::Get()
{
    return m_value;
}

template<typename T>
const T& Value<T>::Get() const
{
    return m_value;
}

} //!var

} //!test

}//!basic

#endif //!BASIC_TEST_VAR_VALUE_H_
