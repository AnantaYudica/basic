#ifndef BASIC_TEST_MSG_ARG_VAL_PARAMETER_H_
#define BASIC_TEST_MSG_ARG_VAL_PARAMETER_H_

#include "../../Argument.h"

#include "../../../Variable.h"
#include "../../../var/val/Parameter.h"
#include "../../../var/Element.h"
#include "../../../var/At.h"
#include "../../../val/Parameter.h"
#include "../../../type/param/Size.h"

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

template<std::size_t>
struct Parameter{};

} //!val

} //!arg

template<typename TCaseId, std::size_t I, typename... TArgs>
class Argument<TCaseId, arg::val::Parameter<I>, TArgs...> :
    public Argument<TCaseId, TArgs...>
{
private:
    template<typename TVar>
    struct Pointer;
    template<typename... TParamArgs>
    struct Pointer<test::val::Parameter<TParamArgs...>>;
public:
    template<typename TVar>
    using ElementType = typename Argument<TCaseId>::
        template ElementType<I, TVar>;
public:
    template<typename TRet, typename TDerived, typename TVar, 
        typename... TFuncMmbrArgs>
    using PointerFunctionMemberType = typename Pointer<ElementType<TVar>>::
        template FunctionMemberType<TRet, TDerived, TVar, 
            TFuncMmbrArgs...>;
    template<typename TRet, typename TVar, typename... TFuncArgs>
    using PointerFunctionType = typename Pointer<ElementType<TVar>>::
        template FunctionType<TRet, TVar, TFuncArgs...>;
public:
    Argument();
protected:
    template<std::size_t S, typename TRet, std::size_t IAt = S, 
        typename TFuncMmbr, typename TDerived, typename... TFuncMmbrArgs, 
        typename... TVarArgs>
    typename std::enable_if<IAt != 0, TRet>::type FillerAt(TFuncMmbr func_mmbr, 
        TDerived& d, test::Variable<TVarArgs...>& var, 
        TFuncMmbrArgs&&... args);
    template<std::size_t S, typename TRet, std::size_t IAt = S, 
        typename TFuncMmbr, typename TDerived, typename... TFuncMmbrArgs, 
        typename... TVarArgs>
    typename std::enable_if<IAt == 0, TRet>::type FillerAt(TFuncMmbr func_mmbr, 
        TDerived& d, test::Variable<TVarArgs...>& var, 
        TFuncMmbrArgs&&... args);
    template<std::size_t S, typename TRet, std::size_t IAt = S, typename TFunc, 
        typename... TFuncArgs, typename... TVarArgs>
    typename std::enable_if<IAt != 0, TRet>::type FillerAt(TFunc func, 
        test::Variable<TVarArgs...>& var, TFuncArgs&&... args);
    template<std::size_t S, typename TRet, std::size_t IAt = S, typename TFunc, 
        typename... TFuncArgs, typename... TVarArgs>
    typename std::enable_if<IAt == 0, TRet>::type FillerAt(TFunc func, 
        test::Variable<TVarArgs...>& var, TFuncArgs&&... args);
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
template<typename TVar>
struct Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::Pointer
{};

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename... TParamArgs>
struct Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
    Pointer<test::val::Parameter<TParamArgs...>>
{
    template<typename TRet, typename TDerived, typename TVar, 
        typename... TFuncMmbrArgs>
    using FunctionMemberType = typename Argument<TCaseId, TArgs...>::
        template PointerFunctionMemberType<TRet, TDerived, TVar, 
        TFuncMmbrArgs..., TParamArgs&&...>;
    template<typename TRet, typename TVar, typename... TFuncArgs>
    using FunctionType = typename Argument<TCaseId, TArgs...>::
        template PointerFunctionType<TRet, TVar, TFuncArgs..., 
        TParamArgs&&...>;
};

template<typename TCaseId, std::size_t I, typename... TArgs>
Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::Argument()
{}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<std::size_t S, typename TRet, std::size_t IAt, 
    typename TFuncMmbr, typename TDerived, typename... TFuncMmbrArgs, 
    typename... TVarArgs>
typename std::enable_if<IAt != 0, TRet>::type 
    Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
        FillerAt(TFuncMmbr func_mmbr, TDerived& d, 
            test::Variable<TVarArgs...>& var, 
            TFuncMmbrArgs&&... args)
{
    return FillerAt<S, TRet, IAt - 1>(func_mmbr, d, var,
        std::forward<TFuncMmbrArgs>(args)..., 
        std::move(test::var::At<I>(var).Get().template At<S - IAt>()));
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<std::size_t S, typename TRet, std::size_t IAt, 
    typename TFuncMmbr, typename TDerived, typename... TFuncMmbrArgs, 
    typename... TVarArgs>
typename std::enable_if<IAt == 0, TRet>::type 
    Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
        FillerAt(TFuncMmbr func_mmbr, TDerived& d, 
            test::Variable<TVarArgs...>& var, 
            TFuncMmbrArgs&&... args)
{
    return Argument<TCaseId, TArgs...>:: template Filler<TRet>(func_mmbr, d, 
        var, std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<std::size_t S, typename TRet, std::size_t IAt, typename TFunc, 
    typename... TFuncArgs, typename... TVarArgs>
typename std::enable_if<IAt != 0, TRet>::type 
    Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
        FillerAt(TFunc func, test::Variable<TVarArgs...>& var, 
            TFuncArgs&&... args)
{
    return FillerAt<S, TRet, IAt - 1>(func, var,
        std::forward<TFuncArgs>(args)..., 
        std::move(test::var::At<I>(var).Get().template At<S - IAt>()));
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<std::size_t S, typename TRet, std::size_t IAt, typename TFunc, 
    typename... TFuncArgs, typename... TVarArgs>
typename std::enable_if<IAt == 0, TRet>::type 
    Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
        FillerAt(TFunc func, test::Variable<TVarArgs...>& var, 
            TFuncArgs&&... args)
{
    return Argument<TCaseId, TArgs...>:: template Filler<TRet>(func, var, 
        std::forward<TFuncArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TFuncMmbr, typename TDerived, 
    typename... TFuncMmbrArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
    Filler(TFuncMmbr func_mmbr, TDerived& d, test::Variable<TVarArgs...>& var, 
        TFuncMmbrArgs&&... args)
{
    return FillerAt<test::type::param::Size<ElementType<test::
        Variable<TVarArgs...>>>::Value, TRet>(func_mmbr, d, var, 
            std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TFunc, typename... TFuncArgs,
    typename... TVarArgs>
TRet Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
    Filler(TFunc func, test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
{
    return FillerAt<test::type::param::Size<ElementType<test::
        Variable<TVarArgs...>>>::Value, TRet>(func, var, 
            std::forward<TFuncArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TDerived, typename... TFuncMmbrArgs,
    typename... TVarArgs>
TRet Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
    Call(PointerFunctionMemberType<TRet, TDerived, test::Variable<TVarArgs...>,
        TFuncMmbrArgs...> func_mmbr, TDerived& d, 
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return Filler<TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename... TFuncArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
    Call(PointerFunctionType<TRet, test::Variable<TVarArgs...>, 
        TFuncArgs...> func, test::Variable<TVarArgs...>& var, 
        TFuncArgs&&... args)
{
    return Filler<TRet>(func, var, std::forward<TFuncArgs>(args)...);
}

} //!msg

} //!test

} //!basic

#endif //!BASIC_TEST_MSG_ARG_VAL_PARAMETER_H_
