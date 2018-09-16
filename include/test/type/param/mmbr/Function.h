#ifndef BASIC_TEST_TYPE_PARAM_MMBR_FUNCTION_H_
#define BASIC_TEST_TYPE_PARAM_MMBR_FUNCTION_H_

#include "../../Parameter.h"

#include <utility>
#include <type_traits>

namespace basic
{
namespace test
{
namespace type
{
namespace param
{
namespace mmbr
{

template<typename T>
class Function
{};

template<typename... TArgs>
class Function<type::Parameter<TArgs...>>
{
public:
    template<typename TRet, typename TDerived>
    using PointerType = TRet(TDerived::*)(TArgs...);
    template<typename TRet, typename TDerived>
    using PointerConstType = TRet(TDerived::*)(TArgs...) const;
    template<typename TRet, typename TDerived>
    using PointerVolatileType = TRet(TDerived::*)(TArgs...) volatile;
    template<typename TRet, typename TDerived>
    using PointerConstVolatileType = TRet(TDerived::*)(TArgs...)
        const volatile;
    template<typename TRet, typename TDerived>
    using PointerLValType = TRet(TDerived::*)(TArgs...) &;
    template<typename TRet, typename TDerived>
    using PointerConstLValType = TRet(TDerived::*)(TArgs...) const &;
    template<typename TRet, typename TDerived>
    using PointerVolatileLValType = TRet(TDerived::*)(TArgs...) volatile &;
    template<typename TRet, typename TDerived>
    using PointerConstVolatileLValType = TRet(TDerived::*)(TArgs...) 
        const volatile &;
    template<typename TRet, typename TDerived>
    using PointerRValType = TRet(TDerived::*)(TArgs...) &&;
    template<typename TRet, typename TDerived>
    using PointerConstRValType = TRet(TDerived::*)(TArgs...) const &&;
    template<typename TRet, typename TDerived>
    using PointerVolatileRValType = TRet(TDerived::*)(TArgs...) volatile &&;
    template<typename TRet, typename TDerived>
    using PointerConstVolatileRValType = TRet(TDerived::*)(TArgs...) 
        const volatile &&;
private:
    template<typename TRet, typename TDerived, typename TPointer>
    static typename std::enable_if<std::is_pointer<TDerived>::value, 
        TRet>::type _Call(TPointer ptr_func_mmbr, TDerived d, TArgs&&... args);
    template<typename TRet, typename TDerived, typename TPointer>
    static typename std::enable_if<!std::is_pointer<TDerived>::value, 
        TRet>::type _Call(TPointer ptr_func_mmbr, TDerived d, TArgs&&... args);
public:
    template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
    static TRet Call(PointerType<TRet, TDerivedFuncMmbr> ptr_func_mmbr, 
        TDerived d, TArgs&&... args);
    template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
    static TRet Call(PointerConstType<TRet, TDerivedFuncMmbr> ptr_func_mmbr,
        TDerived d, TArgs&&... args);
    template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
    static TRet Call(PointerVolatileType<TRet, TDerivedFuncMmbr> ptr_func_mmbr,
        TDerived d, TArgs&&... args);
    template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
    static TRet Call(PointerConstVolatileType<TRet, 
        TDerivedFuncMmbr> ptr_func_mmbr, TDerived d, TArgs&&... args);
    template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
    static TRet Call(PointerLValType<TRet, TDerivedFuncMmbr> ptr_func_mmbr, 
        TDerived d, TArgs&&... args);
    template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
    static TRet Call(PointerConstLValType<TRet, 
        TDerivedFuncMmbr> ptr_func_mmbr, TDerived d, TArgs&&... args);
    template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
    static TRet Call(PointerVolatileLValType<TRet, 
        TDerivedFuncMmbr> ptr_func_mmbr, TDerived d, TArgs&&... args);
    template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
    static TRet Call(PointerConstVolatileLValType<TRet, 
        TDerivedFuncMmbr> ptr_func_mmbr, TDerived d, TArgs&&... args);
    template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
    static TRet Call(PointerRValType<TRet, TDerivedFuncMmbr> ptr_func_mmbr, 
        TDerived d, TArgs&&... args);
    template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
    static TRet Call(PointerConstRValType<TRet, 
        TDerivedFuncMmbr> ptr_func_mmbr, TDerived d, TArgs&&... args);
    template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
    static TRet Call(PointerVolatileRValType<TRet, 
        TDerivedFuncMmbr> ptr_func_mmbr, TDerived d, TArgs&&... args);
    template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
    static TRet Call(PointerConstVolatileRValType<TRet, 
        TDerivedFuncMmbr> ptr_func_mmbr, TDerived d, TArgs&&... args);
};

template<typename... TArgs>
template<typename TRet, typename TDerived, typename TPointer>
typename std::enable_if<std::is_pointer<TDerived>::value, TRet>::type 
    Function<type::Parameter<TArgs...>>::
        _Call(TPointer ptr_func_mmbr, TDerived d, TArgs&&... args)
{
    return (d->*ptr_func_mmbr)(std::forward<TArgs>(args)...);
}

template<typename... TArgs>
template<typename TRet, typename TDerived, typename TPointer>
typename std::enable_if<!std::is_pointer<TDerived>::value, TRet>::type 
    Function<type::Parameter<TArgs...>>::
        _Call(TPointer ptr_func_mmbr, TDerived d, TArgs&&... args)
{
    return (d.*ptr_func_mmbr)(std::forward<TArgs>(args)...);
}

template<typename... TArgs>
template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
TRet Function<type::Parameter<TArgs...>>::
    Call(PointerType<TRet, TDerivedFuncMmbr> ptr_func_mmbr, TDerived d, 
        TArgs&&... args)
{
    return _Call<TRet>(ptr_func_mmbr, d, std::forward<TArgs>(args)...);
}

template<typename... TArgs>
template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
TRet Function<type::Parameter<TArgs...>>::
    Call(PointerConstType<TRet, TDerivedFuncMmbr> ptr_func_mmbr, TDerived d, 
        TArgs&&... args)
{
    return _Call<TRet>(ptr_func_mmbr, d, std::forward<TArgs>(args)...);
}

template<typename... TArgs>
template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
TRet Function<type::Parameter<TArgs...>>::
    Call(PointerVolatileType<TRet, TDerivedFuncMmbr> ptr_func_mmbr, TDerived d,
        TArgs&&... args)
{
    return _Call<TRet>(ptr_func_mmbr, d, std::forward<TArgs>(args)...);
}

template<typename... TArgs>
template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
TRet Function<type::Parameter<TArgs...>>::
    Call(PointerConstVolatileType<TRet, TDerivedFuncMmbr> ptr_func_mmbr, 
        TDerived d, TArgs&&... args)
{
    return _Call<TRet>(ptr_func_mmbr, d, std::forward<TArgs>(args)...);
}

template<typename... TArgs>
template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
TRet Function<type::Parameter<TArgs...>>::
    Call(PointerLValType<TRet, TDerivedFuncMmbr> ptr_func_mmbr, TDerived d, 
        TArgs&&... args)
{
    return _Call<TRet>(ptr_func_mmbr, d, std::forward<TArgs>(args)...);
}

template<typename... TArgs>
template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
TRet Function<type::Parameter<TArgs...>>::
    Call(PointerConstLValType<TRet, TDerivedFuncMmbr> ptr_func_mmbr, 
        TDerived d, TArgs&&... args)
{
    return _Call<TRet>(ptr_func_mmbr, d, std::forward<TArgs>(args)...);
}

template<typename... TArgs>
template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
TRet Function<type::Parameter<TArgs...>>::
    Call(PointerVolatileLValType<TRet, TDerivedFuncMmbr> ptr_func_mmbr, 
        TDerived d, TArgs&&... args)
{
    return _Call<TRet>(ptr_func_mmbr, d, std::forward<TArgs>(args)...);
}

template<typename... TArgs>
template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
TRet Function<type::Parameter<TArgs...>>::
    Call(PointerConstVolatileLValType<TRet, TDerivedFuncMmbr> ptr_func_mmbr, 
        TDerived d, TArgs&&... args)
{
    return _Call<TRet>(ptr_func_mmbr, d, std::forward<TArgs>(args)...);
}

template<typename... TArgs>
template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
TRet Function<type::Parameter<TArgs...>>::
    Call(PointerRValType<TRet, TDerivedFuncMmbr> ptr_func_mmbr, TDerived d,
        TArgs&&... args)
{
    return _Call<TRet>(ptr_func_mmbr, d, std::forward<TArgs>(args)...);
}

template<typename... TArgs>
template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
TRet Function<type::Parameter<TArgs...>>::
    Call(PointerConstRValType<TRet, TDerivedFuncMmbr> ptr_func_mmbr, 
        TDerived d, TArgs&&... args)
{
    return _Call<TRet>(ptr_func_mmbr, d, std::forward<TArgs>(args)...);
}

template<typename... TArgs>
template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
TRet Function<type::Parameter<TArgs...>>::
    Call(PointerVolatileRValType<TRet, TDerivedFuncMmbr> ptr_func_mmbr, 
        TDerived d, TArgs&&... args)
{
    return _Call<TRet>(ptr_func_mmbr, d, std::forward<TArgs>(args)...);
}

template<typename... TArgs>
template<typename TRet, typename TDerived, typename TDerivedFuncMmbr>
TRet Function<type::Parameter<TArgs...>>::
    Call(PointerConstVolatileRValType<TRet, TDerivedFuncMmbr> ptr_func_mmbr, 
        TDerived d, TArgs&&... args)
{
    return _Call<TRet>(ptr_func_mmbr, d, std::forward<TArgs>(args)...);
}

} //!mmbr

} //!param

} //!type

} //!test

} //!basic

#endif //!BASIC_TEST_TYPE_PARAM_MMBR_FUNCTION_H_
