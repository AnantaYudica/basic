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

template<template<typename...> class TTParam, typename TArg, 
    typename... TArgs>
struct Element<0, TTParam<TArg, TArgs...>>
{
    typedef TArg Type;
};

template<std::size_t I, template<typename...> class TTParam, typename TArg, 
    typename... TArgs>
struct Element<I, TTParam<TArg, TArgs...>>
{
    typedef typename Element<I - 1, TTParam<TArgs...>>::Type Type;
};

} //!param

} //!type

} //!test

} //!basic

#endif //!BASIC_TEST_TYPE_PARAM_ELEMENT_H_
