#ifndef BASIC_TEST_OUT_ARGUMENT_H_
#define BASIC_TEST_OUT_ARGUMENT_H_

#include <type_traits>

namespace basic
{
namespace test
{
namespace out
{

template<typename T>
struct Argument
{
    static T&& Value(typename std::remove_reference<T>::type & val);
    static T&& Value(typename std::remove_reference<T>::type && val);
};

template<typename T>
T&& Argument<T>::Value(typename std::remove_reference<T>::type & val)
{
    return static_cast<T&&>(val);
}

template<typename T>
T&& Argument<T>::Value(typename std::remove_reference<T>::type && val)
{
    return static_cast<T&&>(val);
}

} //!out

} //!test

} //!basic

#endif //!BASIC_TEST_OUT_ARGUMENT_H_
