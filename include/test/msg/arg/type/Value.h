#ifndef BASIC_TEST_MSG_ARG_TYPE_VALUE_H_
#define BASIC_TEST_MSG_ARG_TYPE_VALUE_H_

#include "../../Argument.h"

#include "../../../Variable.h"
#include "../../../var/type/Value.h"
#include "../../../var/Element.h"
#include "../../../var/At.h"
#include "../../../type/Value.h"

#include <cstddef>

namespace basic
{
namespace test
{
namespace msg
{
namespace arg
{
namespace type
{

template<std::size_t>
struct Value{};

} //!type

} //!arg

template<typename TCaseId, std::size_t I, typename... TArgs>
class Argument<TCaseId, arg::type::Value<I>, TArgs...> :
    public Argument<TCaseId, TArgs...>
{
public:
    template<typename TVar>
    using ValueType = typename Argument<TCaseId>::
        template ElementType<I, TVar>::Type;
public:
    template<typename TRet, typename TDerived, typename TVar, 
        typename... TFuncMmbrArgs>
    using PointerFunctionMemberType = typename Argument<TCaseId, TArgs...>::
        template PointerFunctionMemberType<TRet, TDerived, TVar, 
        TFuncMmbrArgs..., ValueType<TVar>&&>;
    template<typename TRet, typename TVar, typename... TFuncArgs>
    using PointerFunctionType = typename Argument<TCaseId, TArgs...>::
        template PointerFunctionType<TRet, TVar, TFuncArgs..., 
        ValueType<TVar>&&>;
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

template<typename TCaseId, std::size_t I, typename... TArgs>
Argument<TCaseId, arg::type::Value<I>, TArgs...>::Argument()
{}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TFuncMmbr, typename TDerived, 
    typename... TFuncMmbrArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::type::Value<I>, TArgs...>::
    Filler(TFuncMmbr func_mmbr, TDerived& d, test::Variable<TVarArgs...>& var, 
        TFuncMmbrArgs&&... args)
{
    return Argument<TCaseId, TArgs...>:: template Filler<TRet>(func_mmbr, d, 
        var, std::forward<TFuncMmbrArgs>(args)..., 
        std::move(test::var::At<I>(var).Get().Get()));
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TFunc, typename... TFuncArgs,
    typename... TVarArgs>
TRet Argument<TCaseId, arg::type::Value<I>, TArgs...>::
    Filler(TFunc func, test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
{
    return Argument<TCaseId, TArgs...>:: template Filler<TRet>(func, var, 
        std::forward<TFuncArgs>(args)..., 
        std::move(test::var::At<I>(var).Get().Get()));
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TDerived, typename... TFuncMmbrArgs,
    typename... TVarArgs>
TRet Argument<TCaseId, arg::type::Value<I>, TArgs...>::
    Call(PointerFunctionMemberType<TRet, TDerived, test::Variable<TVarArgs...>,
        TFuncMmbrArgs...> func_mmbr, TDerived& d, 
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return Filler<TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename... TFuncArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::type::Value<I>, TArgs...>::
    Call(PointerFunctionType<TRet, test::Variable<TVarArgs...>, 
        TFuncArgs...> func, test::Variable<TVarArgs...>& var, 
        TFuncArgs&&... args)
{
    return Filler<TRet>(func, var, std::forward<TFuncArgs>(args)...);
}


} //!msg

} //!test

} //!basic

#endif //!BASIC_TEST_MSG_ARG_TYPE_VALUE_H_
