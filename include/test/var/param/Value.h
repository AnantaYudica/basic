#ifndef BASIC_TEST_VAR_PARAM_VALUE_H_
#define BASIC_TEST_VAR_PARAM_VALUE_H_

#include "../../type/Parameter.h"
#include "../../type/param/Element.h"

#include <utility>
#include <type_traits>

namespace basic
{
namespace test
{
namespace var
{
namespace param
{

template<typename TParam>
class Value
{
public:
    Value();
    Value(const Value<TParam>& cpy);
    Value(Value<TParam>&& mov);
public:
    Value<TParam>& operator=(const Value<TParam>& cpy);
    Value<TParam>& operator=(Value<TParam>&& mov);
protected:
    template<typename TRet, typename TFunc, typename... TValues>
    TRet FillerFunc(TFunc func, TValues&&... values);
    template<typename TRet, typename TDerived, typename TFuncMmbr, 
        typename... TValues>
    typename std::enable_if<std::is_pointer<TDerived>::value, TRet>::type 
        FillerFuncMmbr(TFuncMmbr func_mmbr, TDerived derived, 
            TValues&&... values);
    template<typename TRet, typename TDerived, typename TFuncMmbr, 
        typename... TValues>
    typename std::enable_if<!std::is_pointer<TDerived>::value, TRet>::type 
        FillerFuncMmbr(TFuncMmbr func_mmbr, TDerived derived, 
            TValues&&... values);
    template<typename TRet, typename... TValues>
    TRet&& FillerConstruct(TValues&&... values);
public:
    template<typename TRet, typename TFunc>
    TRet Fill(TFunc func);
    template<typename TRet, typename TDerived, typename TFuncMmbr>
    TRet Fill(TFuncMmbr func_mmbr, TDerived derived);
    template<typename TDerived>
    TDerived&& Fill();
};

template<typename TArg, typename... TArgs>
class Value<test::type::Parameter<TArg, TArgs...>> :
    Value<test::type::Parameter<TArgs...>>
{
private:
    TArg m_value;
public:
    Value(const TArg& val, const TArgs&... vals);
    Value(const Value<test::type::Parameter<TArg, TArgs...>>& cpy);
    Value(Value<test::type::Parameter<TArg, TArgs...>>&& mov);
public:
    Value<test::type::Parameter<TArg, TArgs...>>& 
        operator=(const Value<test::type::Parameter<TArg, TArgs...>>& cpy);
    Value<test::type::Parameter<TArg, TArgs...>>& 
        operator=(Value<test::type::Parameter<TArg, TArgs...>>&& mov);
protected:
    template<typename TRet, typename TFunc, typename... TValues>
    TRet FillerFunc(TFunc func, TValues&&... values);
    template<typename TRet, typename TDerived, typename TFuncMmbr, 
        typename... TValues>
    TRet FillerFuncMmbr(TFuncMmbr func_mmbr, TDerived derived, 
        TValues&&... values);
    template<typename TRet, typename... TValues>
    TRet&& FillerConstruct(TValues&&... values);
public:
    template<typename TRet, typename TFunc>
    TRet Fill(TFunc func);
    template<typename TRet, typename TDerived, typename TFuncMmbr>
    TRet Fill(TFuncMmbr func_mmbr, TDerived derived);
    template<typename TDerived>
    TDerived&& Fill();
public:
    template<std::size_t I>
    typename std::enable_if<I == 0, typename test::type::param::Element<I, 
        test::type::Parameter<TArg, TArgs...>>::Type>::type& Get();
    template<std::size_t I>
    typename std::enable_if<I != 0, typename test::type::param::Element<I, 
        test::type::Parameter<TArg, TArgs...>>::Type>::type& Get();
    template<std::size_t I>
    const typename std::enable_if<I == 0, typename test::type::param::
        Element<I,test::type::Parameter<TArg, TArgs...>>::Type>::type& 
            Get() const;
    template<std::size_t I>
    const typename std::enable_if<I != 0, typename test::type::param::
        Element<I,test::type::Parameter<TArg, TArgs...>>::Type>::type& 
            Get() const;
};

template<typename TParam>
Value<TParam>::Value()
{}

template<typename TParam>
Value<TParam>::Value(const Value<TParam>& cpy)
{}

template<typename TParam>
Value<TParam>::Value(Value<TParam>&& mov)
{}

template<typename TParam>
Value<TParam>& Value<TParam>::operator=(const Value<TParam>& cpy)
{
    return *this;
}

template<typename TParam>
Value<TParam>& Value<TParam>::operator=(Value<TParam>&& mov)
{
    return *this;
}

template<typename TParam>
template<typename TRet, typename TFunc, typename... TValues>
TRet Value<TParam>::FillerFunc(TFunc func, TValues&&... values)
{
    return func(std::forward<TValues>(values)...);
}

template<typename TParam>
template<typename TRet, typename TDerived, typename TFuncMmbr, 
    typename... TValues>
typename std::enable_if<std::is_pointer<TDerived>::value, TRet>::type 
    Value<TParam>::FillerFuncMmbr(TFuncMmbr func_mmbr, TDerived derived, 
        TValues&&... values)
{
    return (derived->*func_mmbr)(std::forward<TValues>(values)...);
}

template<typename TParam>
template<typename TRet, typename TDerived, typename TFuncMmbr, 
    typename... TValues>
typename std::enable_if<!std::is_pointer<TDerived>::value, TRet>::type 
    Value<TParam>::FillerFuncMmbr(TFuncMmbr func_mmbr, TDerived derived, 
        TValues&&... values)
{
    return (derived.*func_mmbr)(std::forward<TValues>(values)...);
}

template<typename TParam>
template<typename TRet, typename... TValues>
TRet&& Value<TParam>::FillerConstruct(TValues&&... values)
{
    return std::move(TRet{std::forward<TValues>(values)...});
}

template<typename TParam>
template<typename TRet, typename TFunc>
TRet Value<TParam>::Fill(TFunc func)
{
    return FillerFunc<TRet>(func);
}

template<typename TParam>
template<typename TRet, typename TDerived, typename TFuncMmbr>
TRet Value<TParam>::Fill(TFuncMmbr func_mmbr, TDerived derived)
{
    return FillerFuncMmbr<TRet>(func_mmbr, derived);
}

template<typename TParam>
template<typename TDerived>
TDerived&& Value<TParam>::Fill()
{
    return std::move(FillerConstruct<TDerived>());
}

template<typename TArg, typename... TArgs>
Value<test::type::Parameter<TArg, TArgs...>>::
    Value(const TArg& val, const TArgs&... vals) :
        Value<test::type::Parameter<TArgs...>>(vals...),
        m_value(val)
{}

template<typename TArg, typename... TArgs>
Value<test::type::Parameter<TArg, TArgs...>>::
    Value(const Value<test::type::Parameter<TArg, TArgs...>>& cpy) :
        Value<test::type::Parameter<TArgs...>>(cpy),
        m_value(cpy.m_value)
{}

template<typename TArg, typename... TArgs>
Value<test::type::Parameter<TArg, TArgs...>>::
    Value(Value<test::type::Parameter<TArg, TArgs...>>&& mov) :
        Value<test::type::Parameter<TArgs...>>(std::move(mov)),
        m_value(std::move(mov.m_value))
{}

template<typename TArg, typename... TArgs>
Value<test::type::Parameter<TArg, TArgs...>>& 
    Value<test::type::Parameter<TArg, TArgs...>>::
        operator=(const Value<test::type::Parameter<TArg, TArgs...>>& cpy)
{
    Value<test::type::Parameter<TArgs...>>::operator=(cpy);
    m_value = cpy.m_value;
    return *this;
}

template<typename TArg, typename... TArgs>
Value<test::type::Parameter<TArg, TArgs...>>& 
    Value<test::type::Parameter<TArg, TArgs...>>::
        operator=(Value<test::type::Parameter<TArg, TArgs...>>&& mov)
{
    Value<test::type::Parameter<TArgs...>>::operator=(std::move(mov));
    m_value = std::move(mov.m_value);
    return *this;
}

template<typename TArg, typename... TArgs>
template<typename TRet, typename TFunc, typename... TValues>
TRet Value<test::type::Parameter<TArg, TArgs...>>::
    FillerFunc(TFunc func, TValues&&... values)
{
    return Value<test::type::Parameter<TArgs...>>::
        template FillerFunc<TRet>(func, std::forward<TValues>(values)...,
            std::forward<TArg>(m_value));
}

template<typename TArg, typename... TArgs>
template<typename TRet, typename TDerived, typename TFuncMmbr, 
    typename... TValues>
TRet Value<test::type::Parameter<TArg, TArgs...>>::
    FillerFuncMmbr(TFuncMmbr func_mmbr, TDerived derived, TValues&&... values)
{
    return Value<test::type::Parameter<TArgs...>>::
        template FillerFuncMmbr<TRet>(func_mmbr, derived, 
            std::forward<TValues>(values)..., std::forward<TArg>(m_value));
}

template<typename TArg, typename... TArgs>
template<typename TRet, typename... TValues>
TRet&& Value<test::type::Parameter<TArg, TArgs...>>::
    FillerConstruct(TValues&&... values)
{
    return std::move(Value<test::type::Parameter<TArgs...>>::
        template FillerConstruct<TRet>(std::forward<TValues>(values)..., 
            std::forward<TArg>(m_value)));
}

template<typename TArg, typename... TArgs>
template<typename TRet, typename TFunc>
TRet Value<test::type::Parameter<TArg, TArgs...>>::Fill(TFunc func)
{
    return FillerFunc<TRet>(func);
}

template<typename TArg, typename... TArgs>
template<typename TRet, typename TDerived, typename TFuncMmbr>
TRet Value<test::type::Parameter<TArg, TArgs...>>::
    Fill(TFuncMmbr func_mmbr, TDerived derived)
{
    return FillerFuncMmbr<TRet>(func_mmbr, derived);
}

template<typename TArg, typename... TArgs>
template<typename TDerived>
TDerived&& Value<test::type::Parameter<TArg, TArgs...>>::Fill()
{
    return std::move(FillerConstruct<TDerived>());
}

template<typename TArg, typename... TArgs>
template<std::size_t I>
typename std::enable_if<I == 0, typename test::type::param::Element<I, 
    test::type::Parameter<TArg, TArgs...>>::Type>::type& 
        Value<test::type::Parameter<TArg, TArgs...>>::Get()
{
    return m_value;
}

template<typename TArg, typename... TArgs>
template<std::size_t I>
typename std::enable_if<I != 0, typename test::type::param::Element<I, 
    test::type::Parameter<TArg, TArgs...>>::Type>::type& 
        Value<test::type::Parameter<TArg, TArgs...>>::Get()
{
    return Value<test::type::Parameter<TArgs...>>::
        template Get<I - 1>();
}

template<typename TArg, typename... TArgs>
template<std::size_t I>
const typename std::enable_if<I == 0, typename test::type::param::
    Element<I,test::type::Parameter<TArg, TArgs...>>::Type>::type& 
        Value<test::type::Parameter<TArg, TArgs...>>::Get() const
{
    return m_value;
}

template<typename TArg, typename... TArgs>
template<std::size_t I>
const typename std::enable_if<I != 0, typename test::type::param::
    Element<I,test::type::Parameter<TArg, TArgs...>>::Type>::type& 
        Value<test::type::Parameter<TArg, TArgs...>>::Get() const
{
    return Value<test::type::Parameter<TArgs...>>::
        template Get<I - 1>();;
}

} //!param

} //!var

} //!test

}//!basic


#endif //!BASIC_TEST_VAR_PARAM_VALUE_H_
