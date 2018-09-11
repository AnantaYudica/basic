#ifndef BASIC_TEST_TYPE_PARAMETER_H_
#define BASIC_TEST_TYPE_PARAMETER_H_

#include "param/Name.h"

#include <utility>

namespace basic
{
namespace test
{
namespace type
{

template<typename... TArgs>
struct Parameter
{
    using NameType = param::Name<TArgs...>;
    template<template<typename...> class TT>
    using FilledType = TT<TArgs...>;
    template<typename TRet>
    using PointerFunctionType = TRet(*)(TArgs...);
    template<typename TRet, typename TDerived>
    using PointerFunctionMemberType = TRet(TDerived::*)(TArgs...);
    template<typename TRet, typename TDerived>
    using PointerFunctionConstMemberType = TRet(TDerived::*)(TArgs...) const;
    template<typename TRet>
    static TRet Call(PointerFunctionType<TRet> ptr_func, TArgs&&... args);
    template<typename TRet, typename TDerived>
    static TRet Call(PointerFunctionMemberType<TRet, TDerived> ptr_func_mmbr,
        TDerived& d, TArgs&&... args);
    template<typename TRet, typename TDerived>
    static TRet Call(PointerFunctionConstMemberType<TRet, 
        TDerived> ptr_func_cosnt_mmbr, const TDerived& d, TArgs&&... args);
};

template<typename... TArgs>
template<typename TRet>
TRet Parameter<TArgs...>::Call(PointerFunctionType<TRet> ptr_func, 
    TArgs&&... args)
{
    return ptr_func(std::forward<TArgs>(args)...);
}

template<typename... TArgs>
template<typename TRet, typename TDerived>
TRet Parameter<TArgs...>::Call(PointerFunctionMemberType<TRet, 
    TDerived> ptr_func_mmbr, TDerived& d, TArgs&&... args)
{
    return (d.*ptr_func_mmbr)(std::forward<TArgs>(args)...);
}

template<typename... TArgs>
template<typename TRet, typename TDerived>
TRet Parameter<TArgs...>::Call(PointerFunctionConstMemberType<TRet,
    TDerived> ptr_func_cosnt_mmbr, const TDerived& d, TArgs&&... args)
{
    return (d.*ptr_func_cosnt_mmbr)(std::forward<TArgs>(args)...);
}

} //!type

} //!test

} //!basic

#endif //!BASIC_TEST_TYPE_PARAMETER_H_

