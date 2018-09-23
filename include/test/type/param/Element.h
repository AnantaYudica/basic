#ifndef BASIC_TEST_TYPE_PARAM_ELEMENT_H_
#define BASIC_TEST_TYPE_PARAM_ELEMENT_H_

#include "../Parameter.h"

#include <cstddef>

namespace basic
{
namespace test
{
namespace type
{
namespace param
{

template<std::size_t I, typename T>
struct Element
{};

template<typename TArg, typename... TArgs>
struct Element<0, type::Parameter<TArg, TArgs...>>
{
    typedef TArg Type;
};

template<std::size_t I, typename TArg, typename... TArgs>
struct Element<I, type::Parameter<TArg, TArgs...>>
{
    typedef typename Element<I - 1, test::type::
        Parameter<TArgs...>>::Type Type;
};

} //!param

} //!type

} //!test

} //!basic

#endif //!BASIC_TEST_TYPE_PARAM_ELEMENT_H_
