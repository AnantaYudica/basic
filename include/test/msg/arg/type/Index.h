#ifndef BASIC_TEST_MSG_ARG_TYPE_INDEX_H_
#define BASIC_TEST_MSG_ARG_TYPE_INDEX_H_

#include "../../Argument.h"

#include "../../../Variable.h"
#include "../../../var/At.h"
#include "../../../var/Element.h"
#include "../../../type/Index.h"

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
template<std::size_t I, template<std::size_t, 
    std::size_t> class TTArgArg>
struct Index{};

} //!type

} //!arg

template<typename TCaseId, std::size_t I, template<std::size_t, 
    std::size_t> class TTArgArg, typename... TArgs>
class Argument<TCaseId, arg::type::Index<I, TTArgArg>, TArgs...> :
        public Argument<TCaseId, TArgs...>
{
public:
    template<typename TVar>
    using ElementType = typename Argument<TCaseId>::
        template ElementType<I, TVar>;
public:
    template<std::size_t ICaseId, typename TVar>
    using GetType = typename Argument<TCaseId, TTArgArg<I, ICaseId>>::
        template GetType<TVar>;
public:
    template<std::size_t ICaseId, typename TRet, typename TDerived, 
        typename TVar, typename... TFuncMmbrArgs>
    using PointerFunctionMemberType = typename Argument<TCaseId, TArgs...>::
        template PointerFunctionMemberType<ICaseId, TRet, TDerived, TVar, 
        TFuncMmbrArgs..., GetType<ICaseId, TVar>&&>;
    template<std::size_t ICaseId, typename TRet, typename TVar, 
        typename... TFuncArgs>
    using PointerFunctionType = typename Argument<TCaseId, TArgs...>::
        template PointerFunctionType<ICaseId, TRet, TVar, TFuncArgs...,
        GetType<ICaseId, TVar>&&>;
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
    template<std::size_t ICaseId, typename... TVarArgs>
    GetType<ICaseId, test::Variable<TVarArgs...>> 
        Get(test::Variable<TVarArgs...>& var);
};

template<typename TCaseId, std::size_t I, template<std::size_t, 
    std::size_t> class TTArgArg, typename... TArgs>
Argument<TCaseId, arg::type::Index<I, TTArgArg>, TArgs...>::Argument()
{}

template<typename TCaseId, std::size_t I, template<std::size_t, 
    std::size_t> class TTArgArg, typename... TArgs>
template<std::size_t ICaseId, typename TRet, typename TFuncMmbr, 
    typename TDerived, typename... TFuncMmbrArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::type::Index<I, TTArgArg>, TArgs...>::
    Filler(TFuncMmbr func_mmbr, TDerived& d, test::Variable<TVarArgs...>& var, 
        TFuncMmbrArgs&&... args)
{
    return Argument<TCaseId, TArgs...>::template Filler<ICaseId,
        TRet>(func_mmbr, d, var, std::forward<TFuncMmbrArgs>(args)..., 
        std::move(Get<ICaseId>(var)));
}

template<typename TCaseId, std::size_t I, template<std::size_t, 
    std::size_t> class TTArgArg, typename... TArgs>
template<std::size_t ICaseId, typename TRet, typename TFunc, 
    typename... TFuncArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::type::Index<I, TTArgArg>, TArgs...>::
    Filler(TFunc func, test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
{
    return Argument<TCaseId, TArgs...>::template Filler<ICaseId, TRet>(func, 
        var, std::forward<TFuncArgs>(args)..., std::move(Get<ICaseId>(var)));
}

template<typename TCaseId, std::size_t I, template<std::size_t, 
    std::size_t> class TTArgArg, typename... TArgs>
template<typename TRet, typename TDerived, typename... TFuncMmbrArgs,
    typename... TVarArgs>
TRet Argument<TCaseId, arg::type::Index<I, TTArgArg>, TArgs...>::
    Call(PointerFunctionMemberType<0, TRet, TDerived, 
        test::Variable<TVarArgs...>, TFuncMmbrArgs...> func_mmbr, TDerived& d,
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return Filler<0, TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, template<std::size_t, 
    std::size_t> class TTArgArg, typename... TArgs>
template<typename TRet, typename... TFuncArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::type::Index<I, TTArgArg>, TArgs...>::
    Call(PointerFunctionType<0, TRet, test::Variable<TVarArgs...>, 
        TFuncArgs...> func, test::Variable<TVarArgs...>& var, 
        TFuncArgs&&... args)
{
    return Filler<0, TRet>(func, var, std::forward<TFuncArgs>(args)...);
}

template<typename TCaseId, std::size_t I, template<std::size_t, 
    std::size_t> class TTArgArg, typename... TArgs>
template<typename TRet, std::size_t ICaseId, typename TDerived, 
        typename... TFuncMmbrArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::type::Index<I, TTArgArg>, TArgs...>::
    Call(const type::Index<TCaseId, ICaseId>&, 
        PointerFunctionMemberType<ICaseId, TRet, TDerived, 
            test::Variable<TVarArgs...>, TFuncMmbrArgs...> func_mmbr, 
        TDerived& d, test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return Filler<ICaseId, TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, template<std::size_t, 
    std::size_t> class TTArgArg, typename... TArgs>
    template<typename TRet, std::size_t ICaseId, typename... TFuncArgs, 
        typename... TVarArgs>
TRet Argument<TCaseId, arg::type::Index<I, TTArgArg>, TArgs...>::
    Call(const type::Index<TCaseId, ICaseId>&, PointerFunctionType<ICaseId, 
        TRet, test::Variable<TVarArgs...>, TFuncArgs...> func, 
        test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
{
    return Filler<ICaseId, TRet>(func, var, std::forward<TFuncArgs>(args)...);
}
template<typename TCaseId, std::size_t I, template<std::size_t, 
    std::size_t> class TTArgArg, typename... TArgs>
template<std::size_t ICaseId, typename... TVarArgs>
typename Argument<TCaseId, arg::type::Index<I, TTArgArg>, TArgs...>::
    template GetType<ICaseId, test::Variable<TVarArgs...>> 
        Argument<TCaseId, arg::type::Index<I, TTArgArg>, TArgs...>::
            Get(test::Variable<TVarArgs...>& var)
{
    return std::move(Argument<TCaseId, TTArgArg<I, ICaseId>>{}.Get(var));
}


} //!msg

} //!test

} //!basic

#endif //!BASIC_TEST_MSG_ARG_TYPE_INDEX_H_
