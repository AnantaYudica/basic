#ifndef BASIC_TEST_MSG_ARG_TYPE_VAL_SEQUENCE_H_
#define BASIC_TEST_MSG_ARG_TYPE_VAL_SEQUENCE_H_

#include "../../../Argument.h"

#include "../../../../Variable.h"
#include "../../../../var/type/val/Sequence.h"
#include "../../../../var/Element.h"
#include "../../../../var/At.h"
#include "../../../../type/val/Sequence.h"

#include <cstddef>
#include <type_traits>

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
namespace val
{

template<std::size_t>
struct Sequence{};

} //!val

} //!type

} //!arg

template<typename TCaseId, std::size_t I, typename... TArgs>
class Argument<TCaseId, arg::type::val::Sequence<I>, TArgs...> :
    public Argument<TCaseId, TArgs...>
{
private:
    template<std::size_t S, typename... TSeqArgs>
    struct Pointer;
    template<typename... TSeqArgs>
    struct Pointer<0, TSeqArgs...>;
public:
    template<typename TVar>
    using ElementType = typename Argument<TCaseId>::
        template ElementType<I, TVar>;
public:
    template<typename TVar>
    using GetType = typename ElementType<TVar>::Type;
public:
    template<typename TRet, typename TDerived, typename TVar, 
        typename... TFuncMmbrArgs>
    using PointerFunctionMemberType = typename Pointer<ElementType<TVar>::
        Size>::template FunctionMemberType<TRet, TDerived, TVar, 
            TFuncMmbrArgs...>;
    template<typename TRet, typename TVar, typename... TFuncArgs>
    using PointerFunctionType = typename Pointer<ElementType<TVar>::
        Size>::template FunctionType<TRet, TVar, TFuncArgs...>;
public:
    Argument();
private:
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
public:
    template<std::size_t IAt, typename... TVarArgs>
    GetType<test::Variable<TVarArgs...>> 
        Get(test::Variable<TVarArgs...>& var);
};

template<typename TCaseId, std::size_t I, typename... TArgs>
template<std::size_t S, typename... TSeqArgs>
struct Argument<TCaseId, arg::type::val::Sequence<I>, TArgs...>::Pointer
{
    template<typename TRet, typename TDerived, typename TVar, 
        typename... TFuncMmbrArgs>
    using FunctionMemberType = typename Pointer<S - 1, GetType<TVar>&&,
        TSeqArgs...>::template FunctionMemberType<TRet, TDerived, TVar,
            TFuncMmbrArgs...>;
    template<typename TRet, typename TVar, typename... TFuncArgs>
    using FunctionType = typename Pointer<S - 1, GetType<TVar>&&,
        TSeqArgs...>::template FunctionType<TRet, TVar, TFuncArgs...>;
};

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename... TSeqArgs>
struct Argument<TCaseId, arg::type::val::Sequence<I>, TArgs...>::
    Pointer<0, TSeqArgs...>
{
    template<typename TRet, typename TDerived, typename TVar, 
        typename... TFuncMmbrArgs>
    using FunctionMemberType = typename Argument<TCaseId, TArgs...>::
        template PointerFunctionMemberType<TRet, TDerived, TVar, 
        TFuncMmbrArgs..., TSeqArgs&&...>;
    template<typename TRet, typename TVar, typename... TFuncArgs>
    using FunctionType = typename Argument<TCaseId, TArgs...>::
        template PointerFunctionType<TRet, TVar, TFuncArgs..., 
        TSeqArgs&&...>;
};

template<typename TCaseId, std::size_t I, typename... TArgs>
Argument<TCaseId, arg::type::val::Sequence<I>, TArgs...>::Argument()
{}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<std::size_t S, typename TRet, std::size_t IAt, 
    typename TFuncMmbr, typename TDerived, typename... TFuncMmbrArgs, 
    typename... TVarArgs>
typename std::enable_if<IAt != 0, TRet>::type 
    Argument<TCaseId, arg::type::val::Sequence<I>, TArgs...>::
        FillerAt(TFuncMmbr func_mmbr, TDerived& d, 
            test::Variable<TVarArgs...>& var, 
            TFuncMmbrArgs&&... args)
{
    return FillerAt<S, TRet, IAt - 1>(func_mmbr, d, var,
        std::forward<TFuncMmbrArgs>(args)..., std::move(Get<S - IAt>(var)));
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<std::size_t S, typename TRet, std::size_t IAt, 
    typename TFuncMmbr, typename TDerived, typename... TFuncMmbrArgs, 
    typename... TVarArgs>
typename std::enable_if<IAt == 0, TRet>::type 
    Argument<TCaseId, arg::type::val::Sequence<I>, TArgs...>::
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
    Argument<TCaseId, arg::type::val::Sequence<I>, TArgs...>::
        FillerAt(TFunc func, test::Variable<TVarArgs...>& var, 
            TFuncArgs&&... args)
{
    return FillerAt<S, TRet, IAt - 1>(func, var,
        std::forward<TFuncArgs>(args)..., std::move(Get<S - IAt>(var)));
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<std::size_t S, typename TRet, std::size_t IAt, typename TFunc, 
    typename... TFuncArgs, typename... TVarArgs>
typename std::enable_if<IAt == 0, TRet>::type 
    Argument<TCaseId, arg::type::val::Sequence<I>, TArgs...>::
        FillerAt(TFunc func, test::Variable<TVarArgs...>& var, 
            TFuncArgs&&... args)
{
    return Argument<TCaseId, TArgs...>:: template Filler<TRet>(func, var, 
        std::forward<TFuncArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TFuncMmbr, typename TDerived, 
    typename... TFuncMmbrArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::type::val::Sequence<I>, TArgs...>::
    Filler(TFuncMmbr func_mmbr, TDerived& d, test::Variable<TVarArgs...>& var, 
        TFuncMmbrArgs&&... args)
{
    return FillerAt<ElementType<test::Variable<TVarArgs...>>::Size, 
        TRet>(func_mmbr, d, var, std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TFunc, typename... TFuncArgs,
    typename... TVarArgs>
TRet Argument<TCaseId, arg::type::val::Sequence<I>, TArgs...>::
    Filler(TFunc func, test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
{
    return FillerAt<ElementType<test::Variable<TVarArgs...>>::Size, 
        TRet>(func, var, std::forward<TFuncArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TDerived, typename... TFuncMmbrArgs,
    typename... TVarArgs>
TRet Argument<TCaseId, arg::type::val::Sequence<I>, TArgs...>::
    Call(PointerFunctionMemberType<TRet, TDerived, test::Variable<TVarArgs...>,
        TFuncMmbrArgs...> func_mmbr, TDerived& d, 
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return Filler<TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename... TFuncArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::type::val::Sequence<I>, TArgs...>::
    Call(PointerFunctionType<TRet, test::Variable<TVarArgs...>, 
        TFuncArgs...> func, test::Variable<TVarArgs...>& var, 
        TFuncArgs&&... args)
{
    return Filler<TRet>(func, var, std::forward<TFuncArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<std::size_t IAt, typename... TVarArgs>
typename Argument<TCaseId, arg::type::val::Sequence<I>, TArgs...>::
    template GetType<test::Variable<TVarArgs...>> 
        Argument<TCaseId, arg::type::val::Sequence<I>, TArgs...>::
            Get(test::Variable<TVarArgs...>& var)
{
    return std::move(test::var::At<I>(var).Get().template At<IAt>());
}

} //!msg

} //!test

} //!basic

#endif //!BASIC_TEST_MSG_ARG_TYPE_VAL_SEQUENCE_H_