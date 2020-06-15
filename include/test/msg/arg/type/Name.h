#ifndef BASIC_TEST_MSG_ARG_TYPE_NAME_H_
#define BASIC_TEST_MSG_ARG_TYPE_NAME_H_

#include "../../Argument.h"

#include "../../../Variable.h"
#include "../../../var/Element.h"
#include "../../../type/Name.h"

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

template<std::size_t>
struct Name{};

} //!type

} //!arg

template<typename TCaseId, std::size_t I, typename... TArgs>
class Argument<TCaseId, arg::type::Name<I>, TArgs...> :
    public Argument<TCaseId, TArgs...>
{
public:
    template<typename TVar>
    using ElementType = typename Argument<TCaseId>::
        template ElementType<I, TVar>;
public:
    template<typename TVar>
    using CharType = typename std::remove_const<typename decltype(test::type::
        Name<ElementType<TVar>>::CStr())::CharType>::type;
public:
    template<typename TVar>
    using GetType = test::CString<CharType<TVar>>;
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
    template<typename... TVarArgs, typename TGet = typename Argument<TCaseId, 
        arg::type::Name<I>, TArgs...>::template GetType<test::Variable<
        TVarArgs...>>>
    TGet Get(test::Variable<TVarArgs...>& var);
#else
    template<typename... TVarArgs>
    GetType<test::Variable<TVarArgs...>> 
        Get(test::Variable<TVarArgs...>& var);
#endif
};

template<typename TCaseId, std::size_t I, typename... TArgs>
Argument<TCaseId, arg::type::Name<I>, TArgs...>::Argument()
{}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<std::size_t ICaseId, typename TRet, typename TFuncMmbr, 
    typename TDerived, typename... TFuncMmbrArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::type::Name<I>, TArgs...>::
    Filler(TFuncMmbr func_mmbr, TDerived& d, test::Variable<TVarArgs...>& var,
    TFuncMmbrArgs&&... args)
{
    return Argument<TCaseId, TArgs...>::template Filler<ICaseId,
        TRet>(func_mmbr, d, var, std::forward<TFuncMmbrArgs>(args)..., 
        std::move(Get(var)));
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<std::size_t ICaseId, typename TRet, typename TFunc, 
    typename... TFuncArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::type::Name<I>, TArgs...>::
    Filler(TFunc func, test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
{   
    return Argument<TCaseId, TArgs...>::template Filler<ICaseId, 
        TRet>(func, var, std::forward<TFuncArgs>(args)..., 
        std::move(Get(var)));
}

template<typename TCaseId, std::size_t I, typename... TArgs>
#ifdef _WIN32
template<typename TRet, typename TDerived, typename... TFuncMmbrArgs,
        typename... TVarArgs, typename TFuncMmbr>
TRet Argument<TCaseId, arg::type::Name<I>, TArgs...>::
    Call(TFuncMmbr func_mmbr,
        TDerived& d, test::Variable<TVarArgs...>& var, 
        TFuncMmbrArgs&&... args)
#else
template<typename TRet, typename TDerived, typename... TFuncMmbrArgs,
        typename... TVarArgs>
TRet Argument<TCaseId, arg::type::Name<I>, TArgs...>::
    Call(PointerFunctionMemberType<0, TRet, TDerived, 
        test::Variable<TVarArgs...>, TFuncMmbrArgs...> func_mmbr, 
        TDerived& d, test::Variable<TVarArgs...>& var, 
        TFuncMmbrArgs&&... args)
#endif
{
    return Filler<0, TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
#ifdef _WIN32
template<typename TRet, typename... TFuncArgs, typename... TVarArgs,
    typename TFunc>
TRet Argument<TCaseId, arg::type::Name<I>, TArgs...>::
    Call(TFunc func, test::Variable<TVarArgs...>& var,
        TFuncArgs&&... args)
#else
template<typename TRet, typename... TFuncArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::type::Name<I>, TArgs...>::
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
TRet Argument<TCaseId, arg::type::Name<I>, TArgs...>::
    Call(const type::Index<TCaseId, ICaseId>&, TFuncMmbr func_mmbr,
        TDerived& d, test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
#else
template<typename TRet, typename TDerived, typename... TFuncMmbrArgs, 
    std::size_t ICaseId, typename... TVarArgs>
TRet Argument<TCaseId, arg::type::Name<I>, TArgs...>::
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
TRet Argument<TCaseId, arg::type::Name<I>, TArgs...>::
    Call(const type::Index<TCaseId, ICaseId>&, TFunc func,
        test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
#else
template<typename TRet, typename... TFuncArgs, std::size_t ICaseId, 
    typename... TVarArgs>
TRet Argument<TCaseId, arg::type::Name<I>, TArgs...>::
    Call(const type::Index<TCaseId, ICaseId>&, PointerFunctionType<ICaseId, 
        TRet, test::Variable<TVarArgs...>, TFuncArgs...> func, 
        test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
#endif
{
    return Filler<ICaseId, TRet>(func, var, std::forward<TFuncArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
#ifdef _WIN32
template<typename... TVarArgs, typename TGet>
TGet Argument<TCaseId, arg::type::Name<I>, TArgs...>::
    Get(test::Variable<TVarArgs...>& var)
#else
template<typename... TVarArgs>
typename Argument<TCaseId, arg::type::Name<I>, TArgs...>::
    template GetType<test::Variable<TVarArgs...>> 
        Argument<TCaseId, arg::type::Name<I>, TArgs...>::
            Get(test::Variable<TVarArgs...>& var)
#endif
{
    return std::move(test::type::Name<typename Argument<TCaseId>::
        template ElementType<I, test::Variable<TVarArgs...>>>::CStr());
}

} //!msg

} //!test

} //!basic

#endif //!BASIC_TEST_MSG_ARG_TYPE_NAME_H_