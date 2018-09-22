#ifndef BASIC_TEST_VAL_PARAMETER_H_
#define BASIC_TEST_VAL_PARAMETER_H_

#include "../type/Parameter.h"
#include "../type/param/Element.h"

#include <utility>
#include <type_traits>

namespace basic
{
namespace test
{
namespace val
{

template<typename TTypeParam>
class Parameter
{
public:
    Parameter();
    Parameter(const Parameter<TTypeParam>& cpy);
    Parameter(Parameter<TTypeParam>&& mov);
public:
    Parameter<TTypeParam>& operator=(const Parameter<TTypeParam>& cpy);
    Parameter<TTypeParam>& operator=(Parameter<TTypeParam>&& mov);
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
class Parameter<test::type::Parameter<TArg, TArgs...>> :
    Parameter<test::type::Parameter<TArgs...>>
{
private:
    TArg m_value;
public:
    Parameter(const TArg& val, const TArgs&... vals);
    Parameter(const Parameter<test::type::Parameter<TArg, TArgs...>>& cpy);
    Parameter(Parameter<test::type::Parameter<TArg, TArgs...>>&& mov);
public:
    Parameter<test::type::Parameter<TArg, TArgs...>>& 
        operator=(const Parameter<test::type::Parameter<TArg, TArgs...>>& cpy);
    Parameter<test::type::Parameter<TArg, TArgs...>>& 
        operator=(Parameter<test::type::Parameter<TArg, TArgs...>>&& mov);
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

template<typename TTypeParam>
Parameter<TTypeParam>::Parameter()
{}

template<typename TTypeParam>
Parameter<TTypeParam>::Parameter(const Parameter<TTypeParam>& cpy)
{}

template<typename TTypeParam>
Parameter<TTypeParam>::Parameter(Parameter<TTypeParam>&& mov)
{}

template<typename TTypeParam>
Parameter<TTypeParam>& Parameter<TTypeParam>::
    operator=(const Parameter<TTypeParam>& cpy)
{
    return *this;
}

template<typename TTypeParam>
Parameter<TTypeParam>& Parameter<TTypeParam>::
    operator=(Parameter<TTypeParam>&& mov)
{
    return *this;
}

template<typename TTypeParam>
template<typename TRet, typename TFunc, typename... TValues>
TRet Parameter<TTypeParam>::FillerFunc(TFunc func, TValues&&... values)
{
    return func(std::forward<TValues>(values)...);
}

template<typename TTypeParam>
template<typename TRet, typename TDerived, typename TFuncMmbr, 
    typename... TValues>
typename std::enable_if<std::is_pointer<TDerived>::value, TRet>::type 
    Parameter<TTypeParam>::FillerFuncMmbr(TFuncMmbr func_mmbr, TDerived derived, 
        TValues&&... values)
{
    return (derived->*func_mmbr)(std::forward<TValues>(values)...);
}

template<typename TTypeParam>
template<typename TRet, typename TDerived, typename TFuncMmbr, 
    typename... TValues>
typename std::enable_if<!std::is_pointer<TDerived>::value, TRet>::type 
    Parameter<TTypeParam>::FillerFuncMmbr(TFuncMmbr func_mmbr, TDerived derived, 
        TValues&&... values)
{
    return (derived.*func_mmbr)(std::forward<TValues>(values)...);
}

template<typename TTypeParam>
template<typename TRet, typename... TValues>
TRet&& Parameter<TTypeParam>::FillerConstruct(TValues&&... values)
{
    return std::move(TRet{std::forward<TValues>(values)...});
}

template<typename TTypeParam>
template<typename TRet, typename TFunc>
TRet Parameter<TTypeParam>::Fill(TFunc func)
{
    return FillerFunc<TRet>(func);
}

template<typename TTypeParam>
template<typename TRet, typename TDerived, typename TFuncMmbr>
TRet Parameter<TTypeParam>::Fill(TFuncMmbr func_mmbr, TDerived derived)
{
    return FillerFuncMmbr<TRet>(func_mmbr, derived);
}

template<typename TTypeParam>
template<typename TDerived>
TDerived&& Parameter<TTypeParam>::Fill()
{
    return std::move(FillerConstruct<TDerived>());
}

template<typename TArg, typename... TArgs>
Parameter<test::type::Parameter<TArg, TArgs...>>::
    Parameter(const TArg& val, const TArgs&... vals) :
        Parameter<test::type::Parameter<TArgs...>>(vals...),
        m_value(val)
{}

template<typename TArg, typename... TArgs>
Parameter<test::type::Parameter<TArg, TArgs...>>::
    Parameter(const Parameter<test::type::Parameter<TArg, TArgs...>>& cpy) :
        Parameter<test::type::Parameter<TArgs...>>(cpy),
        m_value(cpy.m_value)
{}

template<typename TArg, typename... TArgs>
Parameter<test::type::Parameter<TArg, TArgs...>>::
    Parameter(Parameter<test::type::Parameter<TArg, TArgs...>>&& mov) :
        Parameter<test::type::Parameter<TArgs...>>(std::move(mov)),
        m_value(std::move(mov.m_value))
{}

template<typename TArg, typename... TArgs>
Parameter<test::type::Parameter<TArg, TArgs...>>& 
    Parameter<test::type::Parameter<TArg, TArgs...>>::
        operator=(const Parameter<test::type::Parameter<TArg, TArgs...>>& cpy)
{
    Parameter<test::type::Parameter<TArgs...>>::operator=(cpy);
    m_value = cpy.m_value;
    return *this;
}

template<typename TArg, typename... TArgs>
Parameter<test::type::Parameter<TArg, TArgs...>>& 
    Parameter<test::type::Parameter<TArg, TArgs...>>::
        operator=(Parameter<test::type::Parameter<TArg, TArgs...>>&& mov)
{
    Parameter<test::type::Parameter<TArgs...>>::operator=(std::move(mov));
    m_value = std::move(mov.m_value);
    return *this;
}

template<typename TArg, typename... TArgs>
template<typename TRet, typename TFunc, typename... TValues>
TRet Parameter<test::type::Parameter<TArg, TArgs...>>::
    FillerFunc(TFunc func, TValues&&... values)
{
    return Parameter<test::type::Parameter<TArgs...>>::
        template FillerFunc<TRet>(func, std::forward<TValues>(values)...,
            std::forward<TArg>(m_value));
}

template<typename TArg, typename... TArgs>
template<typename TRet, typename TDerived, typename TFuncMmbr, 
    typename... TValues>
TRet Parameter<test::type::Parameter<TArg, TArgs...>>::
    FillerFuncMmbr(TFuncMmbr func_mmbr, TDerived derived, TValues&&... values)
{
    return Parameter<test::type::Parameter<TArgs...>>::
        template FillerFuncMmbr<TRet>(func_mmbr, derived, 
            std::forward<TValues>(values)..., std::forward<TArg>(m_value));
}

template<typename TArg, typename... TArgs>
template<typename TRet, typename... TValues>
TRet&& Parameter<test::type::Parameter<TArg, TArgs...>>::
    FillerConstruct(TValues&&... values)
{
    return std::move(Parameter<test::type::Parameter<TArgs...>>::
        template FillerConstruct<TRet>(std::forward<TValues>(values)..., 
            std::forward<TArg>(m_value)));
}

template<typename TArg, typename... TArgs>
template<typename TRet, typename TFunc>
TRet Parameter<test::type::Parameter<TArg, TArgs...>>::Fill(TFunc func)
{
    return FillerFunc<TRet>(func);
}

template<typename TArg, typename... TArgs>
template<typename TRet, typename TDerived, typename TFuncMmbr>
TRet Parameter<test::type::Parameter<TArg, TArgs...>>::
    Fill(TFuncMmbr func_mmbr, TDerived derived)
{
    return FillerFuncMmbr<TRet>(func_mmbr, derived);
}

template<typename TArg, typename... TArgs>
template<typename TDerived>
TDerived&& Parameter<test::type::Parameter<TArg, TArgs...>>::Fill()
{
    return std::move(FillerConstruct<TDerived>());
}

template<typename TArg, typename... TArgs>
template<std::size_t I>
typename std::enable_if<I == 0, typename test::type::param::Element<I, 
    test::type::Parameter<TArg, TArgs...>>::Type>::type& 
        Parameter<test::type::Parameter<TArg, TArgs...>>::Get()
{
    return m_value;
}

template<typename TArg, typename... TArgs>
template<std::size_t I>
typename std::enable_if<I != 0, typename test::type::param::Element<I, 
    test::type::Parameter<TArg, TArgs...>>::Type>::type& 
        Parameter<test::type::Parameter<TArg, TArgs...>>::Get()
{
    return Parameter<test::type::Parameter<TArgs...>>::
        template Get<I - 1>();
}

template<typename TArg, typename... TArgs>
template<std::size_t I>
const typename std::enable_if<I == 0, typename test::type::param::
    Element<I,test::type::Parameter<TArg, TArgs...>>::Type>::type& 
        Parameter<test::type::Parameter<TArg, TArgs...>>::Get() const
{
    return m_value;
}

template<typename TArg, typename... TArgs>
template<std::size_t I>
const typename std::enable_if<I != 0, typename test::type::param::
    Element<I,test::type::Parameter<TArg, TArgs...>>::Type>::type& 
        Parameter<test::type::Parameter<TArg, TArgs...>>::Get() const
{
    return Parameter<test::type::Parameter<TArgs...>>::
        template Get<I - 1>();;
}

} //!var

} //!test

}//!basic


#endif //!BASIC_TEST_VAL_PARAMETER_H_
