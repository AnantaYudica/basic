#ifndef BASIC_TEST_MSG_ARG_TYPE_NAME_H_
#define BASIC_TEST_MSG_ARG_TYPE_NAME_H_

#include "../../Argument.h"

#include "../../../Variable.h"
#include "../../../var/Element.h"
#include "../../../type/Name.h"

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
struct Name{};

} //!type

} //!arg

template<typename TCaseId, std::size_t I, typename... TArgs>
class Argument<TCaseId, arg::type::Name<I>, TArgs...> :
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
    using CharType = typename decltype(test::type::Name<
        ElementType<TVarArgs...>>::CStr())::CharType;
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
        const CharType<TVarArgs...>*&&> func_mmbr, TDerived& d, 
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args);
    template<typename TRet, typename... TFuncArgs, typename... TVarArgs>
    TRet Call(PointerFunctionType<TRet, TFuncArgs..., 
        const CharType<TVarArgs...>*&&> func, 
        test::Variable<TVarArgs...>& var, TFuncArgs&&... args);
};

template<typename TCaseId, std::size_t I, typename... TArgs>
Argument<TCaseId, arg::type::Name<I>, TArgs...>::Argument()
{}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TFuncMmbr, typename TDerived, 
        typename... TFuncMmbrArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::type::Name<I>, TArgs...>::
    Filler(TFuncMmbr func_mmbr, TDerived& d, test::Variable<TVarArgs...>& var,
    TFuncMmbrArgs&&... args)
{
    test::CString<CharType<TVarArgs...>> cstr = 
        std::move(test::type::Name<ElementType<TVarArgs...>>::CStr());
    return Argument<TCaseId, TArgs...>::template Filler<TRet>(func_mmbr, 
        d, var, std::forward<TFuncMmbrArgs>(args)..., *cstr);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TFunc, typename... TFuncArgs,
        typename... TVarArgs>
TRet Argument<TCaseId, arg::type::Name<I>, TArgs...>::
    Filler(TFunc func, test::Variable<TVarArgs...>& var, TFuncArgs&&... args)
{
    test::CString<CharType<TVarArgs...>> cstr = 
        std::move(test::type::Name<ElementType<TVarArgs...>>::CStr());
    return Argument<TCaseId, TArgs...>::template Filler<TRet>(func, var,
        std::forward<TFuncArgs>(args)..., *cstr);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TDerived, typename... TFuncMmbrArgs,
        typename... TVarArgs>
TRet Argument<TCaseId, arg::type::Name<I>, TArgs...>::
    Call(PointerFunctionMemberType<TRet, TDerived, TFuncMmbrArgs..., 
        const CharType<TVarArgs...>*&&> func_mmbr, TDerived& d, 
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return Filler<TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename... TFuncArgs, typename... TVarArgs>
TRet Argument<TCaseId, arg::type::Name<I>, TArgs...>::
    Call(PointerFunctionType<TRet, TFuncArgs..., 
        const CharType<TVarArgs...>*&&> func, test::Variable<TVarArgs...>& var,
        TFuncArgs&&... args)
{
    return Filler<TRet>(func, var, std::forward<TFuncArgs>(args)...);
}

} //!msg

} //!test

} //!basic

#endif //!BASIC_TEST_MSG_ARG_TYPE_NAME_H_