#ifndef BASIC_TEST_MSG_ARGUMENT_H_
#define BASIC_TEST_MSG_ARGUMENT_H_

#include "../Variable.h"
#include "../var/Element.h"
#include "../type/Index.h"

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
    template<std::size_t I, typename TVar>
    using ElementType = typename test::var::Element<I, TVar>::Type;
public:
    template<std::size_t ICaseId, typename TRet, typename TDerived, 
        typename TVar, typename... TFuncMmbrArgs>
    using PointerFunctionMemberType = TRet(TDerived::*)(TFuncMmbrArgs...);
    template<std::size_t ICaseId, typename TRet, typename TVar, 
        typename... TFuncArgs>
    using PointerFunctionType = TRet(*)(TFuncArgs...);
public:
    Argument();
protected:
    template<std::size_t ICaseId, typename TRet, typename TFuncMmbr, 
        typename TDerived, typename... TFuncMmbrArgs, typename... TVarArgs>
    TRet Filler(TFuncMmbr func_mmbr, TDerived& d,
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args);
    template<std::size_t ICaseId, typename TRet, typename TFunc, 
        typename... TFuncArgs, typename... TVarArgs>
    TRet Filler(TFunc func, test::Variable<TVarArgs...>& var, 
        TFuncArgs&&... args);
public:
    template<typename TRet, typename TDerived, typename... TFuncMmbrArgs,
        typename... TVarArgs>
    TRet Call(PointerFunctionMemberType<0, TRet, TDerived, 
        test::Variable<TVarArgs...>, TFuncMmbrArgs...> func_mmbr, TDerived& d,
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args);
    template<typename TRet, typename... TFuncArgs, typename... TVarArgs>
    TRet Call(PointerFunctionType<0, TRet, test::Variable<TVarArgs...>, 
        TFuncArgs...> func, test::Variable<TVarArgs...>& var, 
        TFuncArgs&&... args);
public:
    template<typename TRet, std::size_t ICaseId, typename TDerived, 
        typename... TFuncMmbrArgs, typename... TVarArgs>
    TRet Call(const type::Index<TCaseId, ICaseId>&, 
        PointerFunctionMemberType<ICaseId, TRet, TDerived, 
            test::Variable<TVarArgs...>, TFuncMmbrArgs...> func_mmbr, 
        TDerived& d, test::Variable<TVarArgs...>& var, 
        TFuncMmbrArgs&&... args);
    template<typename TRet, std::size_t ICaseId, typename... TFuncArgs, 
        typename... TVarArgs>
    TRet Call(const type::Index<TCaseId, ICaseId>&, PointerFunctionType<ICaseId, 
        TRet, test::Variable<TVarArgs...>, TFuncArgs...> func, 
        test::Variable<TVarArgs...>& var, TFuncArgs&&... args);
};

template<typename TCaseId, typename... TArgs>
Argument<TCaseId, TArgs...>::Argument()
{};

template<typename TCaseId, typename... TArgs>
template<std::size_t ICaseId, typename TRet, typename TFuncMmbr, 
    typename TDerived, typename... TFuncMmbrArgs, typename... TVarArgs>
TRet Argument<TCaseId, TArgs...>::Filler(TFuncMmbr func_mmbr, TDerived& d,
    test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return (d.*func_mmbr)(std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, typename... TArgs>
template<std::size_t ICaseId, typename TRet, typename TFunc, 
    typename... TFuncArgs, typename... TVarArgs>
TRet Argument<TCaseId, TArgs...>::Filler(TFunc func, 
    test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
{
    return func(std::forward<TFuncArgs>(args)...);
}

template<typename TCaseId, typename... TArgs>
template<typename TRet, typename TDerived, typename... TFuncMmbrArgs,
    typename... TVarArgs>
TRet Argument<TCaseId, TArgs...>::Call(PointerFunctionMemberType<0, TRet, 
    TDerived, test::Variable<TVarArgs...>, TFuncMmbrArgs...> func_mmbr, 
    TDerived& d, test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return Filler<0, TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, typename... TArgs>
template<typename TRet, typename... TFuncArgs, typename... TVarArgs>
TRet Argument<TCaseId, TArgs...>::Call(PointerFunctionType<0, TRet, 
    test::Variable<TVarArgs...>, TFuncArgs...> func, 
    test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
{
    return Filler<0, TRet>(func, var, std::forward<TFuncArgs>(args)...);
}

template<typename TCaseId, typename... TArgs>
template<typename TRet, std::size_t ICaseId, typename TDerived, 
    typename... TFuncMmbrArgs, typename... TVarArgs>
TRet Argument<TCaseId, TArgs...>::Call(const type::Index<TCaseId, ICaseId>&, 
    PointerFunctionMemberType<ICaseId, TRet, TDerived, 
        test::Variable<TVarArgs...>, TFuncMmbrArgs...> func_mmbr, 
    TDerived& d, test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return Filler<ICaseId, TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, typename... TArgs>
template<typename TRet, std::size_t ICaseId, typename... TFuncArgs, 
    typename... TVarArgs>
TRet Argument<TCaseId, TArgs...>::Call(const type::Index<TCaseId, ICaseId>&, 
    PointerFunctionType<ICaseId, TRet, test::Variable<TVarArgs...>, 
    TFuncArgs...> func, test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
{
    return Filler<TCaseId, TRet>(func, var, std::forward<TFuncArgs>(args)...);
}

} //!msg

} //!test

} //!basic

#endif //!BASIC_TEST_MSG_ARGUMENT_H_
