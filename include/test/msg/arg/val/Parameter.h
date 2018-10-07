#ifndef BASIC_TEST_MSG_ARG_VAL_PARAMETER_H_
#define BASIC_TEST_MSG_ARG_VAL_PARAMETER_H_

#include "../../Argument.h"

#include "../../../Variable.h"
#include "../../../var/val/Parameter.h"
#include "../../../var/Element.h"
#include "../../../var/At.h"
#include "../../../val/Parameter.h"
#include "../../../type/param/Size.h"
#include "../../../type/param/Element.h"

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
    template<std::size_t IAt, typename TVar>
    using GetType = typename test::type::param::Element<IAt, 
        ElementType<TVar>>::Type;
public:
    template<std::size_t ICaseId, typename TRet, typename TDerived, 
        typename TVar, typename... TFuncMmbrArgs>
    using PointerFunctionMemberType = typename Pointer<ElementType<TVar>>::
        template FunctionMemberType<ICaseId, TRet, TDerived, TVar, 
            TFuncMmbrArgs...>;
    template<std::size_t ICaseId, typename TRet, typename TVar, 
        typename... TFuncArgs>
    using PointerFunctionType = typename Pointer<ElementType<TVar>>::
        template FunctionType<ICaseId, TRet, TVar, TFuncArgs...>;
public:
    Argument();
protected:
    template<std::size_t ICaseId, std::size_t S, typename TRet, 
        std::size_t IAt = S, typename TFuncMmbr, typename TDerived, 
        typename... TFuncMmbrArgs, typename... TVarArgs>
    typename std::enable_if<IAt != 0, TRet>::type FillerAt(TFuncMmbr func_mmbr, 
        TDerived& d, test::Variable<TVarArgs...>& var, 
        TFuncMmbrArgs&&... args);
    template<std::size_t ICaseId, std::size_t S, typename TRet, 
        std::size_t IAt = S, typename TFuncMmbr, typename TDerived, 
        typename... TFuncMmbrArgs, typename... TVarArgs>
    typename std::enable_if<IAt == 0, TRet>::type FillerAt(TFuncMmbr func_mmbr, 
        TDerived& d, test::Variable<TVarArgs...>& var, 
        TFuncMmbrArgs&&... args);
    template<std::size_t ICaseId, std::size_t S, typename TRet, 
        std::size_t IAt = S, typename TFunc, typename... TFuncArgs, 
        typename... TVarArgs>
    typename std::enable_if<IAt != 0, TRet>::type FillerAt(TFunc func, 
        test::Variable<TVarArgs...>& var, TFuncArgs&&... args);
    template<std::size_t ICaseId, std::size_t S, typename TRet, 
        std::size_t IAt = S, typename TFunc, typename... TFuncArgs, 
        typename... TVarArgs>
    typename std::enable_if<IAt == 0, TRet>::type FillerAt(TFunc func, 
        test::Variable<TVarArgs...>& var, TFuncArgs&&... args);
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
#ifdef _WIN32
    template<typename TRet, typename TDerived, typename... TFuncMmbrArgs,
        typename... TVarArgs, typename TFuncMmbr = PointerFunctionMemberType<0,
        TRet, TDerived, test::Variable<TVarArgs...>, TFuncMmbrArgs...>>
    TRet Call(TFuncMmbr func_mmbr, TDerived& d,
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args);
#else
    template<typename TRet, typename TDerived, typename... TFuncMmbrArgs,
        typename... TVarArgs>
    TRet Call(PointerFunctionMemberType<0, TRet, TDerived, 
        test::Variable<TVarArgs...>, TFuncMmbrArgs...> func_mmbr, TDerived& d,
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args);
#endif
#ifdef _WIN32
    template<typename TRet, typename... TFuncArgs, typename... TVarArgs,
        typename TFunc = PointerFunctionType<0, TRet, 
        test::Variable<TVarArgs...>, TFuncArgs...>>
    TRet Call(TFunc func, test::Variable<TVarArgs...>& var,
        TFuncArgs&&... args);
#else
    template<typename TRet, typename... TFuncArgs, typename... TVarArgs>
    TRet Call(PointerFunctionType<0, TRet, test::Variable<TVarArgs...>, 
        TFuncArgs...> func, test::Variable<TVarArgs...>& var, 
        TFuncArgs&&... args);
#endif
public:
#ifdef _WIN32
    template<typename TRet, typename TDerived, typename... TFuncMmbrArgs, 
        std::size_t ICaseId, typename... TVarArgs, typename TFuncMmbr = 
        PointerFunctionMemberType<ICaseId, TRet, TDerived,
        test::Variable<TVarArgs...>, TFuncMmbrArgs...>>
    TRet Call(const type::Index<TCaseId, ICaseId>&, TFuncMmbr func_mmbr,
        TDerived& d, test::Variable<TVarArgs...>& var, 
        TFuncMmbrArgs&&... args);
#else
    template<typename TRet, typename TDerived, typename... TFuncMmbrArgs, 
        std::size_t ICaseId, typename... TVarArgs>
    TRet Call(const type::Index<TCaseId, ICaseId>&, 
        PointerFunctionMemberType<ICaseId, TRet, TDerived, 
            test::Variable<TVarArgs...>, TFuncMmbrArgs...> func_mmbr, 
        TDerived& d, test::Variable<TVarArgs...>& var, 
        TFuncMmbrArgs&&... args);
#endif
#ifdef _WIN32
    template<typename TRet, typename... TFuncArgs, std::size_t ICaseId, 
        typename... TVarArgs, typename TFunc = PointerFunctionType<ICaseId,
        TRet, test::Variable<TVarArgs...>, TFuncArgs...>>
    TRet Call(const type::Index<TCaseId, ICaseId>&, TFunc func,
        test::Variable<TVarArgs...>& var, TFuncArgs&&... args);
#else
    template<typename TRet, typename... TFuncArgs, std::size_t ICaseId, 
        typename... TVarArgs>
    TRet Call(const type::Index<TCaseId, ICaseId>&, PointerFunctionType<ICaseId, 
        TRet, test::Variable<TVarArgs...>, TFuncArgs...> func, 
        test::Variable<TVarArgs...>& var, TFuncArgs&&... args);
#endif
public:
#ifdef _WIN32
    template<std::size_t IAt, typename... TVarArgs, typename TGet = 
        typename Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
        template GetType<IAt, test::Variable<TVarArgs...>>>
    TGet Get(test::Variable<TVarArgs...>& var);
#else
    template<std::size_t IAt, typename... TVarArgs>
    GetType<IAt, test::Variable<TVarArgs...>> 
        Get(test::Variable<TVarArgs...>& var);
#endif
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
    template<std::size_t ICaseId, typename TRet, typename TDerived, 
        typename TVar, typename... TFuncMmbrArgs>
    using FunctionMemberType = typename Argument<TCaseId, TArgs...>::
        template PointerFunctionMemberType<ICaseId, TRet, TDerived, TVar, 
        TFuncMmbrArgs..., TParamArgs&&...>;
    template<std::size_t ICaseId, typename TRet, typename TVar, 
        typename... TFuncArgs>
    using FunctionType = typename Argument<TCaseId, TArgs...>::
        template PointerFunctionType<ICaseId, TRet, TVar, TFuncArgs..., 
        TParamArgs&&...>;
};

template<typename TCaseId, std::size_t I, typename... TArgs>
Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::Argument()
{}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<std::size_t ICaseId, std::size_t S, typename TRet, std::size_t IAt, 
    typename TFuncMmbr, typename TDerived, typename... TFuncMmbrArgs, 
    typename... TVarArgs>
typename std::enable_if<IAt != 0, TRet>::type 
    Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
        FillerAt(TFuncMmbr func_mmbr, TDerived& d, 
            test::Variable<TVarArgs...>& var, 
            TFuncMmbrArgs&&... args)
{
    return FillerAt<ICaseId, S, TRet, IAt - 1>(func_mmbr, d, var,
        std::forward<TFuncMmbrArgs>(args)..., std::move(Get<S - IAt>(var)));
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<std::size_t ICaseId, std::size_t S, typename TRet, std::size_t IAt, 
    typename TFuncMmbr, typename TDerived, typename... TFuncMmbrArgs, 
    typename... TVarArgs>
typename std::enable_if<IAt == 0, TRet>::type 
    Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
        FillerAt(TFuncMmbr func_mmbr, TDerived& d, 
            test::Variable<TVarArgs...>& var, 
            TFuncMmbrArgs&&... args)
{
    return Argument<TCaseId, TArgs...>:: template Filler<ICaseId,
        TRet>(func_mmbr, d, var, std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<std::size_t ICaseId, std::size_t S, typename TRet, std::size_t IAt, 
    typename TFunc, typename... TFuncArgs, typename... TVarArgs>
typename std::enable_if<IAt != 0, TRet>::type 
    Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
        FillerAt(TFunc func, test::Variable<TVarArgs...>& var, 
            TFuncArgs&&... args)
{
    return FillerAt<ICaseId, S, TRet, IAt - 1>(func, var,
        std::forward<TFuncArgs>(args)..., std::move(Get<S - IAt>(var)));
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<std::size_t ICaseId, std::size_t S, typename TRet, std::size_t IAt, 
    typename TFunc, typename... TFuncArgs, typename... TVarArgs>
typename std::enable_if<IAt == 0, TRet>::type 
    Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
        FillerAt(TFunc func, test::Variable<TVarArgs...>& var, 
            TFuncArgs&&... args)
{
    return Argument<TCaseId, TArgs...>:: template Filler<ICaseId,
        TRet>(func, var, std::forward<TFuncArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<std::size_t ICaseId, typename TRet, typename TFuncMmbr, 
    typename TDerived, typename... TFuncMmbrArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
    Filler(TFuncMmbr func_mmbr, TDerived& d, test::Variable<TVarArgs...>& var, 
        TFuncMmbrArgs&&... args)
{
    return FillerAt<ICaseId, test::type::param::Size<ElementType<test::
        Variable<TVarArgs...>>>::Value, TRet>(func_mmbr, d, var, 
            std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<std::size_t ICaseId, typename TRet, typename TFunc, 
    typename... TFuncArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
    Filler(TFunc func, test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
{
    return FillerAt<ICaseId, test::type::param::Size<ElementType<test::
        Variable<TVarArgs...>>>::Value, TRet>(func, var, 
            std::forward<TFuncArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
#ifdef _WIN32
template<typename TRet, typename TDerived, typename... TFuncMmbrArgs,
    typename... TVarArgs, typename TFuncMmbr>
TRet Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
    Call(TFuncMmbr func_mmbr, TDerived& d,
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
#else
template<typename TRet, typename TDerived, typename... TFuncMmbrArgs,
    typename... TVarArgs>
TRet Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
    Call(PointerFunctionMemberType<0, TRet, TDerived, 
        test::Variable<TVarArgs...>, TFuncMmbrArgs...> func_mmbr, TDerived& d, 
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
#endif
{
    return Filler<0, TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
#ifdef _WIN32
template<typename TRet, typename... TFuncArgs, typename... TVarArgs,
    typename TFunc>
TRet Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
    Call(TFunc func, test::Variable<TVarArgs...>& var,
        TFuncArgs&&... args)
#else
template<typename TRet, typename... TFuncArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
    Call(PointerFunctionType<0, TRet, test::Variable<TVarArgs...>, 
        TFuncArgs...> func, test::Variable<TVarArgs...>& var, 
        TFuncArgs&&... args)
#endif
{
    return Filler<0, TRet>(func, var, std::forward<TFuncArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
#ifdef _WIN32
template<typename TRet, typename TDerived, typename... TFuncMmbrArgs, 
    std::size_t ICaseId, typename... TVarArgs, typename TFuncMmbr>
TRet Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
    Call(const type::Index<TCaseId, ICaseId>&, TFuncMmbr func_mmbr,
        TDerived& d, test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
#else
template<typename TRet, typename TDerived, typename... TFuncMmbrArgs, 
    std::size_t ICaseId, typename... TVarArgs>
TRet Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
    Call(const type::Index<TCaseId, ICaseId>&, 
        PointerFunctionMemberType<ICaseId, TRet, TDerived, 
            test::Variable<TVarArgs...>, TFuncMmbrArgs...> func_mmbr, 
        TDerived& d, test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
#endif
{
    return Filler<ICaseId, TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
#ifdef _WIN32
template<typename TRet, typename... TFuncArgs, std::size_t ICaseId, 
    typename... TVarArgs, typename TFunc>
TRet Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
    Call(const type::Index<TCaseId, ICaseId>&, TFunc func,
        test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
#else
template<typename TRet, typename... TFuncArgs, std::size_t ICaseId, 
    typename... TVarArgs>
TRet Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
    Call(const type::Index<TCaseId, ICaseId>&, PointerFunctionType<ICaseId, 
        TRet, test::Variable<TVarArgs...>, TFuncArgs...> func, 
        test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
#endif
{
    return Filler<ICaseId, TRet>(func, var, std::forward<TFuncArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
#ifdef _WIN32
template<std::size_t IAt, typename... TVarArgs, typename TGet>
TGet Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
    Get(test::Variable<TVarArgs...>& var)
#else
template<std::size_t IAt, typename... TVarArgs>
typename Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
    template GetType<IAt, test::Variable<TVarArgs...>> 
        Argument<TCaseId, arg::val::Parameter<I>, TArgs...>::
            Get(test::Variable<TVarArgs...>& var)
#endif
{
    return std::move(test::var::At<I>(var).Get().template At<IAt>());
}

} //!msg

} //!test

} //!basic

#endif //!BASIC_TEST_MSG_ARG_VAL_PARAMETER_H_
