#ifndef BASIC_TEST_MSG_ARG_TYPE_PARAM_NAME_AT_H_
#define BASIC_TEST_MSG_ARG_TYPE_PARAM_NAME_AT_H_

#include "../../../../Argument.h"

#include "../../../../../Variable.h"
#include "../../../../../var/Element.h"
#include "../../../../../type/Parameter.h"
#include "../../../../../type/param/Element.h"
#include "../../../../../type/Name.h"

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
namespace param
{
namespace name
{

template<std::size_t, std::size_t>
struct At{};

} //!name

} //!param

} //!type

} //!arg

template<typename TCaseId, std::size_t I, std::size_t IAt, typename... TArgs>
class Argument<TCaseId, arg::type::param::name::At<I, IAt>, TArgs...> :
    public Argument<TCaseId, TArgs...>
{
public:
    template<typename TVar>
    using ElementType = typename Argument<TCaseId>::template ElementType<I, 
        TVar>;
    template<typename TVar>
    using CharType = typename decltype(type::Name<typename type::param::
        Element<IAt, ElementType<TVar>>::Type>::CStr())::CharType;
public:
    template<typename TRet, typename TDerived, typename TVar, 
        typename... TFuncMmbrArgs>
    using PointerFunctionMemberType = typename Argument<TCaseId, TArgs...>::
        template PointerFunctionMemberType<TRet, TDerived, TVar, 
        TFuncMmbrArgs..., const CharType<TVar>*&&>;
    template<typename TRet, typename TVar, typename... TFuncArgs>
    using PointerFunctionType = typename Argument<TCaseId, TArgs...>::
        template PointerFunctionType<TRet, TVar, TFuncArgs...,
        const CharType<TVar>*&&>;
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

template<typename TCaseId, std::size_t I, std::size_t IAt, typename... TArgs>
Argument<TCaseId, arg::type::param::name::At<I, IAt>, TArgs...>::Argument()
{}

template<typename TCaseId, std::size_t I, std::size_t IAt, typename... TArgs>
template<typename TRet, typename TFuncMmbr, typename TDerived, 
    typename... TFuncMmbrArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::type::param::name::At<I, IAt>, TArgs...>::
    Filler(TFuncMmbr func_mmbr, TDerived& d,
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    test::CString<CharType<test::Variable<TVarArgs...>>> cstr = 
        std::move(type::Name<typename test::type::param::Element<IAt, 
            ElementType<test::Variable<TVarArgs...>>>::Type>::CStr());
    return Argument<TCaseId, TArgs...>:: template Filler<TRet>(func_mmbr, d, 
        var, std::forward<TFuncMmbrArgs>(args)..., *cstr);
}

template<typename TCaseId, std::size_t I, std::size_t IAt, typename... TArgs>
template<typename TRet, typename TFunc, typename... TFuncArgs,
    typename... TVarArgs>
TRet Argument<TCaseId, arg::type::param::name::At<I, IAt>, TArgs...>::
    Filler(TFunc func, test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
{
    test::CString<CharType<test::Variable<TVarArgs...>>> cstr = 
        std::move(type::Name<typename test::type::param::Element<IAt, 
            ElementType<test::Variable<TVarArgs...>>>::Type>::CStr());
    return Argument<TCaseId, TArgs...>:: template Filler<TRet>(func, var, 
        std::forward<TFuncArgs>(args)..., *cstr);
}

template<typename TCaseId, std::size_t I, std::size_t IAt, typename... TArgs>
template<typename TRet, typename TDerived, typename... TFuncMmbrArgs,
    typename... TVarArgs>
TRet Argument<TCaseId, arg::type::param::name::At<I, IAt>, TArgs...>::
    Call(PointerFunctionMemberType<TRet, TDerived, test::Variable<TVarArgs...>, 
        TFuncMmbrArgs...> func_mmbr, TDerived& d, 
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return Filler<TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, std::size_t IAt, typename... TArgs>
template<typename TRet, typename... TFuncArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::type::param::name::At<I, IAt>, TArgs...>::
    Call(PointerFunctionType<TRet, test::Variable<TVarArgs...>, 
        TFuncArgs...> func, test::Variable<TVarArgs...>& var, 
        TFuncArgs&&... args)
{
    return Filler<TRet>(func, var, std::forward<TFuncArgs>(args)...);
}

} //!msg

} //!test

} //!basic


#endif //!BASIC_TEST_MSG_ARG_TYPE_PARAM_NAME_AT_H_
