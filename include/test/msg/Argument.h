#ifndef BASIC_TEST_MSG_ARGUMENT_H_
#define BASIC_TEST_MSG_ARGUMENT_H_

#include "../Variable.h"

#include <cstddef>
#include <utility>

namespace basic
{
namespace test
{
namespace msg
{

template<typename TCaseId, typename... TArgs>
class Argument
{
public:
    template<typename TRet, typename TDerived, typename... TFuncMmbrArgs>
    using PointerFunctionMemberType = TRet(TDerived::*)(TFuncMmbrArgs...);
    template<typename TRet, typename... TFuncArgs>
    using PointerFunctionType = TRet(*)(TFuncArgs...);
public:
    Argument();
protected:
    template<typename TRet, typename TFuncMmbr, typename TDerived, 
        typename... TFuncMmbrArgs, typename... TVarArgs>
    TRet Filler(TFuncMmbr func_mmbr, TDerived& d,
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args);
    template<typename TRet, typename TFunc, typename... TFuncArgs,
        typename... TVarArgs>
    TRet Filler(TFunc func, test::Variable<TVarArgs...>& var, 
        TFuncArgs&&... args);
public:
    template<typename TRet, typename TDerived, typename... TFuncMmbrArgs,
        typename... TVarArgs>
    TRet Call(PointerFunctionMemberType<TRet, TDerived, TFuncMmbrArgs...> func_mmbr, 
        TDerived& d, test::Variable<TVarArgs...>& var, 
        TFuncMmbrArgs&&... args);
    template<typename TRet, typename... TFuncArgs, typename... TVarArgs>
    TRet Call(PointerFunctionType<TRet, TFuncArgs...> func, 
        test::Variable<TVarArgs...>& var, TFuncArgs&&... args);
};

template<typename TCaseId, typename... TArgs>
Argument<TCaseId, TArgs...>::Argument()
{};

template<typename TCaseId, typename... TArgs>
template<typename TRet, typename TFuncMmbr, typename TDerived, 
    typename... TFuncMmbrArgs, typename... TVarArgs>
TRet Argument<TCaseId, TArgs...>::Filler(TFuncMmbr func_mmbr, TDerived& d,
    test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return (d.*func_mmbr)(std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, typename... TArgs>
template<typename TRet, typename TFunc, typename... TFuncArgs,
    typename... TVarArgs>
TRet Argument<TCaseId, TArgs...>::Filler(TFunc func, 
    test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
{
    return func(std::forward<TFuncArgs>(args)...);
}

template<typename TCaseId, typename... TArgs>
template<typename TRet, typename TDerived, typename... TFuncMmbrArgs,
    typename... TVarArgs>
TRet Argument<TCaseId, TArgs...>::Call(PointerFunctionMemberType<TRet, 
    TDerived, TFuncMmbrArgs...> func_mmbr, TDerived& d, 
    test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return Filler<TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, typename... TArgs>
template<typename TRet, typename... TFuncArgs, typename... TVarArgs>
TRet Argument<TCaseId, TArgs...>::Call(PointerFunctionType<TRet, 
    TFuncArgs...> func, test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
{
    return Filler<TRet>(func, var, std::forward<TFuncArgs>(args)...);
}

} //!msg

} //!test

} //!basic

#endif //!BASIC_TEST_MSG_ARGUMENT_H_
