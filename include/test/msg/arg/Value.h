#ifndef BASIC_TEST_MSG_ARG_VALUE_H_
#define BASIC_TEST_MSG_ARG_VALUE_H_

#include "../Argument.h"

#include "../../Variable.h"
#include "../../var/Value.h"
#include "../../var/Element.h"
#include "../../var/At.h"
#include "../../Value.h"

#include <cstddef>

namespace basic
{
namespace test
{
namespace msg
{
namespace arg
{

template<std::size_t>
struct Value{};

} //!arg

template<typename TCaseId, std::size_t I, typename... TArgs>
class Argument<TCaseId, arg::Value<I>, TArgs...> :
    public Argument<TCaseId, TArgs...>
{
public:
    template<typename TVar>
    using ElementType = typename Argument<TCaseId>::
        template ElementType<I, TVar>;
public:
    template<typename TVar>
    using GetType = typename ElementType<TVar>::Type;
public:
    template<std::size_t ICaseId, typename TRet, typename TDerived, 
        typename TVar, typename... TFuncMmbrArgs>
    using PointerFunctionMemberType = typename Argument<TCaseId, TArgs...>::
        template PointerFunctionMemberType<ICaseId, TRet, TDerived, TVar, 
        TFuncMmbrArgs..., GetType<TVar>&&>;
    template<std::size_t ICaseId, typename TRet, typename TVar, 
        typename... TFuncArgs>
    using PointerFunctionType = typename Argument<TCaseId, TArgs...>::
        template PointerFunctionType<ICaseId, TRet, TVar, TFuncArgs..., 
        GetType<TVar>&&>;
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
public:
    template<typename... TVarArgs>
    GetType<test::Variable<TVarArgs...>> 
        Get(test::Variable<TVarArgs...>& var);
};

template<typename TCaseId, std::size_t I, typename... TArgs>
Argument<TCaseId, arg::Value<I>, TArgs...>::Argument()
{}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<std::size_t ICaseId, typename TRet, typename TFuncMmbr, 
    typename TDerived, typename... TFuncMmbrArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::Value<I>, TArgs...>::
    Filler(TFuncMmbr func_mmbr, TDerived& d, test::Variable<TVarArgs...>& var,
        TFuncMmbrArgs&&... args)
{
    return Argument<TCaseId, TArgs...>:: template Filler<ICaseId,
        TRet>(func_mmbr, d, var, std::forward<TFuncMmbrArgs>(args)..., 
        std::move(Get(var)));
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<std::size_t ICaseId, typename TRet, typename TFunc, 
    typename... TFuncArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::Value<I>, TArgs...>::
    Filler(TFunc func, test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
{
    return Argument<TCaseId, TArgs...>:: template Filler<ICaseId,
        TRet>(func, var, std::forward<TFuncArgs>(args)..., 
        std::move(Get(var)));
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TDerived, typename... TFuncMmbrArgs,
    typename... TVarArgs>
TRet Argument<TCaseId, arg::Value<I>, TArgs...>::
    Call(PointerFunctionMemberType<0, TRet, TDerived, 
        test::Variable<TVarArgs...>, TFuncMmbrArgs...> func_mmbr, TDerived& d, 
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return Filler<0, TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename... TFuncArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::Value<I>, TArgs...>::
    Call(PointerFunctionType<0, TRet, test::Variable<TVarArgs...>, 
        TFuncArgs...> func, test::Variable<TVarArgs...>& var, 
        TFuncArgs&&... args)
{
    return Filler<0, TRet>(func, var, std::forward<TFuncArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, std::size_t ICaseId, typename TDerived, 
    typename... TFuncMmbrArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::Value<I>, TArgs...>::
    Call(const type::Index<TCaseId, ICaseId>&, 
        PointerFunctionMemberType<ICaseId, TRet, TDerived, 
            test::Variable<TVarArgs...>, TFuncMmbrArgs...> func_mmbr, 
        TDerived& d, test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return Filler<ICaseId, TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, std::size_t ICaseId, typename... TFuncArgs, 
    typename... TVarArgs>
TRet Argument<TCaseId, arg::Value<I>, TArgs...>::
    Call(const type::Index<TCaseId, ICaseId>&, PointerFunctionType<ICaseId, 
        TRet, test::Variable<TVarArgs...>, TFuncArgs...> func, 
        test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
{
    return Filler<ICaseId, TRet>(func, var, std::forward<TFuncArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename... TVarArgs>
typename Argument<TCaseId, arg::Value<I>, TArgs...>::
    template GetType<test::Variable<TVarArgs...>> Argument<TCaseId, 
        arg::Value<I>, TArgs...>::Get(test::Variable<TVarArgs...>& var)
{
    return std::move(basic::test::var::At<I>(var).Get().Get());
}

} //!msg

} //!test

} //!basic

#endif //!BASIC_TEST_MSG_ARG_VALUE_H_
