#ifndef BASIC_TEST_TYPE_PARAM_FUNCTION_H_
#define BASIC_TEST_TYPE_PARAM_FUNCTION_H_

#include "../Parameter.h"

#include <utility>

namespace basic
{
namespace test
{
namespace type
{
namespace param
{

template<typename T>
class Function
{};

template<typename... TArgs>
class Function<type::Parameter<TArgs...>>
{
public:
    template<typename TRet>
    using PointerType = TRet(*)(TArgs...);
public:
    template<typename TRet>
    static TRet Call(PointerType<TRet> ptr_func, TArgs&&... args);
};

template<typename... TArgs>
template<typename TRet>
TRet Function<type::Parameter<TArgs...>>::
    Call(PointerType<TRet> ptr_func, TArgs&&... args)
{
    return ptr_func(std::forward<TArgs>(args)...);
}

} //!param

} //!type

} //!test

} //!basic

#endif //!BASIC_TEST_TYPE_PARAM_FUNCTION_H_
