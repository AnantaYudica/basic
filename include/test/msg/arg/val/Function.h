#ifndef BASIC_TEST_MSG_ARG_VAL_FUNCTION_H_
#define BASIC_TEST_MSG_ARG_VAL_FUNCTION_H_

#include "../../Argument.h"

#include "../../../Variable.h"
#include "../../../var/val/Function.h"
#include "../../../var/At.h"
#include "../../../var/Element.h"
#include "../../../val/Function.h"

#include <cstddef>

namespace basic
{
namespace test
{
namespace msg
{
namespace arg
{
namespace val
{

template<std::size_t I, typename... TArgArgs>
struct Function{};

} //!val

} //!arg

template<typename TCaseId, std::size_t I, typename... TArgArgs, 
    typename... TArgs>
class Argument<TCaseId, arg::val::Function<I, TArgArgs...>, TArgs...> :
    public Argument<TCaseId, TArgs...>
{
public:
    template<typename TVar>
    using ElementType = typename Argument<TCaseId>::
        template ElementType<I, TVar>;
    template<typename TVar>
    using ReturnType = typename ElementType<TVar>::ReturnType;
    
public:
    template<typename TRet, typename TDerived, typename TVar, 
        typename... TFuncMmbrArgs>
    using PointerFunctionMemberType = typename Argument<TCaseId, TArgs...>::
        template PointerFunctionMemberType<TRet, TDerived, TVar, 
        TFuncMmbrArgs..., ReturnType<TVar>&&>;
    template<typename TRet, typename TVar, typename... TFuncArgs>
    using PointerFunctionType = typename Argument<TCaseId, TArgs...>::
        template PointerFunctionType<TRet, TVar, TFuncArgs..., 
        ReturnType<TVar>&&>;
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
    TRet Call(PointerFunctionMemberType<TRet, TDerived, 
        test::Variable<TVarArgs...>, TFuncMmbrArgs...> func_mmbr, TDerived& d,
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args);
    template<typename TRet, typename... TFuncArgs, typename... TVarArgs>
    TRet Call(PointerFunctionType<TRet, test::Variable<TVarArgs...>, 
        TFuncArgs...> func, test::Variable<TVarArgs...>& var, 
        TFuncArgs&&... args);
};

template<typename TCaseId, std::size_t I, typename... TArgArgs, 
    typename... TArgs>
Argument<TCaseId, arg::val::Function<I, TArgArgs...>, TArgs...>::Argument()
{}

template<typename TCaseId, std::size_t I, typename... TArgArgs, 
    typename... TArgs>
template<typename TRet, typename TFuncMmbr, typename TDerived, 
    typename... TFuncMmbrArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::val::Function<I, TArgArgs...>, TArgs...>::
    Filler(TFuncMmbr func_mmbr, TDerived& d, test::Variable<TVarArgs...>& var, 
        TFuncMmbrArgs&&... args)
{
    Argument<TCaseId, TArgArgs...> arg_func;
    typedef ReturnType<test::Variable<TVarArgs...>> TRetFunc;
    auto& value = test::var::At<I>(var).Get();
    TRetFunc&& result = std::move(arg_func.template Call<TRetFunc>(value.Get(), var));
    return Argument<TCaseId, TArgs...>:: template Filler<TRet>(func_mmbr, d, 
        var, std::forward<TFuncMmbrArgs>(args)..., 
        std::forward<TRetFunc>(result));
}

template<typename TCaseId, std::size_t I, typename... TArgArgs, 
    typename... TArgs>
template<typename TRet, typename TFunc, typename... TFuncArgs,
    typename... TVarArgs>
TRet Argument<TCaseId, arg::val::Function<I, TArgArgs...>, TArgs...>::
    Filler(TFunc func, test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
{
    Argument<TCaseId, TArgArgs...> arg_func;
    typedef ReturnType<test::Variable<TVarArgs...>> TRetFunc;
    auto& value = test::var::At<I>(var).Get();
    TRetFunc&& result = std::move(arg_func.template Call<TRetFunc>(value.Get(), var));
    return Argument<TCaseId, TArgs...>:: template Filler<TRet>(func, var, 
        std::forward<TFuncArgs>(args)..., std::forward<TRetFunc>(result));
}

template<typename TCaseId, std::size_t I, typename... TArgArgs, 
    typename... TArgs>
template<typename TRet, typename TDerived, typename... TFuncMmbrArgs,
    typename... TVarArgs>
TRet Argument<TCaseId, arg::val::Function<I, TArgArgs...>, TArgs...>::
    Call(PointerFunctionMemberType<TRet, TDerived, test::Variable<TVarArgs...>,
        TFuncMmbrArgs...> func_mmbr, TDerived& d, 
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return Filler<TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgArgs, 
    typename... TArgs>
template<typename TRet, typename... TFuncArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::val::Function<I, TArgArgs...>, TArgs...>::
    Call(PointerFunctionType<TRet, test::Variable<TVarArgs...>, 
        TFuncArgs...> func, test::Variable<TVarArgs...>& var, 
        TFuncArgs&&... args)
{
    return Filler<TRet>(func, var, std::forward<TFuncArgs>(args)...);
}


} //!msg

} //!test

} //!basic

#endif //!BASIC_TEST_MSG_ARG_VAL_FUNCTION_H_
