#ifndef BASIC_TEST_VAR_ELEMENT_H_
#define BASIC_TEST_VAR_ELEMENT_H_

#include "../Variable.h"

#include <cstddef>

namespace basic
{
namespace test
{
namespace var
{

template<std::size_t I, typename T>
struct Element
{};

template<std::size_t I, typename TArg, typename... TArgs>
struct Element<I, test::Variable<TArg, TArgs...>>
{
    using Type = typename Element<I - 1, 
        test::Variable<TArgs...>>::Type;
};

template<typename TArg, typename... TArgs>
struct Element<0, test::Variable<TArg, TArgs...>>
{
    using Type = TArg;
};

} //!var

} //!test

} //!basic

#endif //!BASIC_TEST_VAR_ELEMENT_H_
