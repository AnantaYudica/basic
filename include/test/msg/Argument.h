#ifndef BASIC_TEST_MSG_ARGUMENT_H_
#define BASIC_TEST_MSG_ARGUMENT_H_

#include "../CString.h"

#include "../Variable.h"
#include "../var/Element.h"
#include "../var/Value.h"

#include "../type/Name.h"
#include "../type/param/Name.h"
#include "../type/Value.h"

#include <cstddef>
#include <utility>


namespace basic
{
namespace test
{
namespace msg
{

namespace arg
{

template<std::size_t I>
struct TypeName {};

template<std::size_t I>
struct TypeParamName {};

template<std::size_t I>
struct TypeValue {};

template<std::size_t I>
struct VarValue {};

}

template<typename TCaseId, typename... TArgs>
class Argument
{
public:
    template<typename TRet, typename TDerived, typename... TFuncMmbrArgs>
    using FunctionMemberType = TRet(TDerived::*)(TFuncMmbrArgs...);
public:
    Argument();
protected:
    template<typename TRet, typename TFunc, typename TDerived, 
        typename... TVarArgs, typename... TFuncMmbrArgs>
    TRet Filler(TFunc func_mmbr, TDerived& d,
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args);
public:
    template<typename TRet, typename TDerived, typename... TVarArgs,
        typename... TFuncMmbrArgs>
    TRet Call(FunctionMemberType<TRet, TDerived, TFuncMmbrArgs...> func_mmbr, 
        TDerived& d, test::Variable<TVarArgs...>& var, 
        TFuncMmbrArgs&&... args);
};

template<typename TCaseId, std::size_t I, typename... TArgs>
class Argument<TCaseId, arg::TypeName<I>, TArgs...> :
    public Argument<TCaseId, TArgs...>
{
public:
    template<typename TRet, typename TDerived, typename... TFuncMmbrArgs>
    using FunctionMemberType = typename Argument<TCaseId, TArgs...>::
        template FunctionMemberType<TRet, TDerived, TFuncMmbrArgs...>;
    template<typename... TVarArgs>
    using ElementType = typename test::var::Element<I, 
        test::Variable<TVarArgs...>>::Type;
    template<typename... TVarArgs>
    using CharType = typename decltype(test::type::Name<
        ElementType<TVarArgs...>>::CStr())::CharType;
public:
    Argument();
protected:
    template<typename TRet, typename TFunc, typename TDerived, 
        typename... TVarArgs, typename... TFuncMmbrArgs>
    TRet Filler(TFunc func_mmbr, TDerived& d,
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args);
public:
    template<typename TRet, typename TDerived, typename... TVarArgs,
        typename... TFuncMmbrArgs>
    TRet Call(FunctionMemberType<TRet, TDerived, TFuncMmbrArgs..., 
        const CharType<TVarArgs...>*&&> func_mmbr, TDerived& d, 
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args);
};

template<typename TCaseId, std::size_t I, typename... TArgs>
class Argument<TCaseId, arg::TypeParamName<I>, TArgs...> :
    public Argument<TCaseId, TArgs...>
{
public:
    template<typename TRet, typename TDerived, typename... TFuncMmbrArgs>
    using FunctionMemberType = typename Argument<TCaseId, TArgs...>::
        template FunctionMemberType<TRet, TDerived, TFuncMmbrArgs...>;
    template<typename... TVarArgs>
    using ElementType = typename test::var::Element<I, 
        test::Variable<TVarArgs...>>::Type;
    template<typename... TVarArgs>
    using CharType = typename decltype(ElementType<TVarArgs...>::
        NameType::CStr())::CharType;
public:
    Argument();
protected:
    template<typename TRet, typename TFunc, typename TDerived, 
        typename... TVarArgs, typename... TFuncMmbrArgs>
    TRet Filler(TFunc func_mmbr, TDerived& d,
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args);
public:
    template<typename TRet, typename TDerived, typename... TVarArgs,
        typename... TFuncMmbrArgs>
    TRet Call(FunctionMemberType<TRet, TDerived, TFuncMmbrArgs..., 
        const CharType<TVarArgs...>*&&> func_mmbr, TDerived& d, 
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args);
};

template<typename TCaseId, std::size_t I, typename... TArgs>
class Argument<TCaseId, arg::TypeValue<I>, TArgs...> :
    public Argument<TCaseId, TArgs...>
{
public:
    template<typename TRet, typename TDerived, typename... TFuncMmbrArgs>
    using FunctionMemberType = typename Argument<TCaseId, TArgs...>::
        template FunctionMemberType<TRet, TDerived, TFuncMmbrArgs...>;
    template<typename... TVarArgs>
    using ElementType = typename test::var::Element<I, 
        test::Variable<TVarArgs...>>::Type;
    template<typename... TVarArgs>
    using ValueType = typename ElementType<TVarArgs...>::Type;
public:
    Argument();
protected:
    template<typename TRet, typename TFunc, typename TDerived, 
        typename... TVarArgs, typename... TFuncMmbrArgs>
    TRet Filler(TFunc func_mmbr, TDerived& d,
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args);
public:
    template<typename TRet, typename TDerived, typename... TVarArgs,
        typename... TFuncMmbrArgs>
    TRet Call(FunctionMemberType<TRet, TDerived, TFuncMmbrArgs..., 
        ValueType<TVarArgs...>&&> func_mmbr, TDerived& d, 
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args);
};

template<typename TCaseId, std::size_t I, typename... TArgs>
class Argument<TCaseId, arg::VarValue<I>, TArgs...> :
    public Argument<TCaseId, TArgs...>
{
public:
    template<typename TRet, typename TDerived, typename... TFuncMmbrArgs>
    using FunctionMemberType = typename Argument<TCaseId, TArgs...>::
        template FunctionMemberType<TRet, TDerived, TFuncMmbrArgs...>;
    template<typename... TVarArgs>
    using ElementType = typename test::var::Element<I, 
        test::Variable<TVarArgs...>>::Type;
    template<typename... TVarArgs>
    using ValueType = typename ElementType<TVarArgs...>::Type;
public:
    Argument();
protected:
    template<typename TRet, typename TFunc, typename TDerived, 
        typename... TVarArgs, typename... TFuncMmbrArgs>
    TRet Filler(TFunc func_mmbr, TDerived& d,
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args);
public:
    template<typename TRet, typename TDerived, typename... TVarArgs,
        typename... TFuncMmbrArgs>
    TRet Call(FunctionMemberType<TRet, TDerived, TFuncMmbrArgs..., 
        ValueType<TVarArgs...>&&> func_mmbr, TDerived& d, 
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args);
};

template<typename TCaseId, typename... TArgs>
Argument<TCaseId, TArgs...>::Argument()
{};

template<typename TCaseId, typename... TArgs>
template<typename TRet, typename TFunc, typename TDerived, 
    typename... TVarArgs, typename... TFuncMmbrArgs>
TRet Argument<TCaseId, TArgs...>::Filler(TFunc func_mmbr, TDerived& d,
    test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return (d.*func_mmbr)(std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, typename... TArgs>
template<typename TRet, typename TDerived, typename... TVarArgs,
    typename... TFuncMmbrArgs>
TRet Argument<TCaseId, TArgs...>::Call(FunctionMemberType<TRet, 
    TDerived, TFuncMmbrArgs...> func_mmbr, TDerived& d, 
    test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return Filler<TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
Argument<TCaseId, arg::TypeName<I>, TArgs...>::Argument()
{}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TFunc, typename TDerived, 
    typename... TVarArgs, typename... TFuncMmbrArgs>
TRet Argument<TCaseId, arg::TypeName<I>, TArgs...>::Filler(TFunc func_mmbr,
    TDerived& d, test::Variable<TVarArgs...>& var, 
    TFuncMmbrArgs&&... args)
{
    test::CString<CharType<TVarArgs...>> cstr = 
        std::move(test::type::Name<ElementType<TVarArgs...>>::CStr());
    return Argument<TCaseId, TArgs...>::template Filler<TRet>(
        func_mmbr, d, var, std::forward<TFuncMmbrArgs>(args)..., *cstr);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TDerived, typename... TVarArgs,
    typename... TFuncMmbrArgs>
TRet Argument<TCaseId, arg::TypeName<I>, TArgs...>::
    Call(FunctionMemberType<TRet, TDerived, TFuncMmbrArgs..., 
        const CharType<TVarArgs...>*&&> func_mmbr, TDerived& d, 
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return Filler<TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
Argument<TCaseId, arg::TypeParamName<I>, TArgs...>::Argument()
{}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TFunc, typename TDerived, 
    typename... TVarArgs, typename... TFuncMmbrArgs>
TRet Argument<TCaseId, arg::TypeParamName<I>, TArgs...>::
    Filler(TFunc func_mmbr, TDerived& d,
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    test::CString<CharType<TVarArgs...>> cstr = 
        std::move(ElementType<TVarArgs...>::NameType::CStr());
    return Argument<TCaseId, TArgs...>:: template Filler<TRet>(func_mmbr, d, 
        var, std::forward<TFuncMmbrArgs>(args)..., *cstr);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TDerived, typename... TVarArgs,
    typename... TFuncMmbrArgs>
TRet Argument<TCaseId, arg::TypeParamName<I>, TArgs...>::
    Call(FunctionMemberType<TRet, TDerived, TFuncMmbrArgs...,
        const CharType<TVarArgs...>*&&> func_mmbr, TDerived& d, 
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return Filler<TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
Argument<TCaseId, arg::TypeValue<I>, TArgs...>::Argument()
{}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TFunc, typename TDerived, 
    typename... TVarArgs, typename... TFuncMmbrArgs>
TRet Argument<TCaseId, arg::TypeValue<I>, TArgs...>::
    Filler(TFunc func_mmbr, TDerived& d, test::Variable<TVarArgs...>& var, 
        TFuncMmbrArgs&&... args)
{
    return Argument<TCaseId, TArgs...>:: template Filler<TRet>(func_mmbr, d, 
        var, std::forward<TFuncMmbrArgs>(args)..., 
        std::move(ElementType<TVarArgs...>::Get()));
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TDerived, typename... TVarArgs,
    typename... TFuncMmbrArgs>
TRet Argument<TCaseId, arg::TypeValue<I>, TArgs...>::
    Call(FunctionMemberType<TRet, TDerived, TFuncMmbrArgs..., 
        ValueType<TVarArgs...>&&> func_mmbr, TDerived& d, 
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return Filler<TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

template<typename TCaseId, std::size_t I, typename... TArgs>
Argument<TCaseId, arg::VarValue<I>, TArgs...>::Argument()
{}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TFunc, typename TDerived, 
    typename... TVarArgs, typename... TFuncMmbrArgs>
TRet Argument<TCaseId, arg::VarValue<I>, TArgs...>::
    Filler(TFunc func_mmbr, TDerived& d, test::Variable<TVarArgs...>& var, 
        TFuncMmbrArgs&&... args)
{
    return Argument<TCaseId, TArgs...>:: template Filler<TRet>(func_mmbr, d, 
        var, std::forward<TFuncMmbrArgs>(args)..., 
        std::move(var.template GetValue<I>()));
}

template<typename TCaseId, std::size_t I, typename... TArgs>
template<typename TRet, typename TDerived, typename... TVarArgs,
    typename... TFuncMmbrArgs>
TRet Argument<TCaseId, arg::VarValue<I>, TArgs...>::
    Call(FunctionMemberType<TRet, TDerived, TFuncMmbrArgs..., 
        ValueType<TVarArgs...>&&> func_mmbr, TDerived& d, 
        test::Variable<TVarArgs...>& var, TFuncMmbrArgs&&... args)
{
    return Filler<TRet>(func_mmbr, d, var, 
        std::forward<TFuncMmbrArgs>(args)...);
}

} //!msg

} //!test

} //!basic

#endif //!BASIC_TEST_MSG_ARGUMENT_H_
