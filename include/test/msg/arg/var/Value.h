#ifndef BASIC_TEST_MSG_ARG_VAR_VALUE_H_
#define BASIC_TEST_MSG_ARG_VAR_VALUE_H_

#include "../../Argument.h"

#include "../../../Variable.h"
#include "../../../var/Element.h"
#include "../../../var/Value.h"

#include <cstddef>

namespace basic
{
namespace test
{
namespace msg
{
namespace arg
{
namespace var
{

template<std::size_t>
struct Value{};

} //!val

} //!arg


template<typename TCaseId, std::size_t I, typename... TArgs>
class Argument<TCaseId, arg::var::Value<I>, TArgs...> :
    public Argument<TCaseId, TArgs...>
{
public:
    template<typename TRet, typename TDerived, typename... TFuncMmbrArgs>
    using PointerFunctionMemberType = typename Argument<TCaseId, TArgs...>::
        template PointerFunctionMemberType<TRet, TDerived, TFuncMmbrArgs...>;
    template<typename TRet, typename... TFuncMmbrArgs>
    using PointerFunctionType = typename Argument<TCaseId, TArgs...>::
        template PointerFunctionType<TRet, TFuncMmbrArgs...>;
public:
    template<typename... TVarArgs>
    using ElementType = typename test::var::Element<I, 
        test::Variable<TVarArgs...>>::Type;
    template<typename... TVarArgs>
    using ValueType = typename ElementType<TVarArgs...>::Type;
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
    TRet Call(PointerFunctionMemberType<TRet, TDerived, TFuncMmbrArgs..., 
        ValueType<TVarArgs...>&&> func_mmbr, TDerived& d, 
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args);
    template<typename TRet, typename... TFuncArgs, typename... TVarArgs>
    TRet Call(PointerFunctionType<TRet, TFuncArgs..., 
        ValueType<TVarArgs...>&&> func, 
        test::Variable<TVarArgs...>& var, TFuncArgs&&... args);
};

template<typename TCaseId, std::size_t I, typename... TArgs>
Argument<TCaseId, arg::var::Value<I>, TArgs...>::Argument()
{}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TFuncMmbr, typename TDerived, 
    typename... TFuncMmbrArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::var::Value<I>, TArgs...>::
    Filler(TFuncMmbr func_mmbr, TDerived& d, test::Variable<TVarArgs...>& var,
        TFuncMmbrArgs&&... args)
{
    return Argument<TCaseId, TArgs...>:: template Filler<TRet>(func_mmbr, d, 
        var, std::forward<TFuncMmbrArgs>(args)..., 
        std::move(var.template GetValue<I>()));
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TFunc, typename... TFuncArgs,
    typename... TVarArgs>
TRet Argument<TCaseId, arg::var::Value<I>, TArgs...>::
    Filler(TFunc func, test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
{
    return Argument<TCaseId, TArgs...>:: template Filler<TRet>(func, var, 
        std::forward<TFuncArgs>(args)..., 
        std::move(var.template GetValue<I>()));
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TDerived, typename... TFuncMmbrArgs,
    typename... TVarArgs>
TRet Argument<TCaseId, arg::var::Value<I>, TArgs...>::
    Call(PointerFunctionMemberType<TRet, TDerived, TFuncMmbrArgs..., 
        ValueType<TVarArgs...>&&> func_mmbr, TDerived& d, 
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return Filler<TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename... TFuncArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::var::Value<I>, TArgs...>::
    Call(PointerFunctionType<TRet, TFuncArgs..., 
        ValueType<TVarArgs...>&&> func, test::Variable<TVarArgs...>& var, 
        TFuncArgs&&... args)
{
    return Filler<TRet>(func, var, std::forward<TFuncArgs>(args)...);
}

} //!msg

} //!test

} //!basic


#endif //!BASIC_TEST_MSG_ARG_VAR_VALUE_H_
