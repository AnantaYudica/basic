#ifndef BASIC_TEST_PARAMETER_H_
#define BASIC_TEST_PARAMETER_H_

#include "type/Parameter.h"
#include "type/param/Element.h"

#include <utility>
#include <type_traits>

namespace basic
{
namespace test
{

template<typename... TArgs>
class Parameter
{
public:
    Parameter();
    Parameter(const Parameter<TArgs...>& cpy);
    Parameter(Parameter<TArgs...>&& mov);
public:
    Parameter<TArgs...>& operator=(const Parameter<TArgs...>& cpy);
    Parameter<TArgs...>& operator=(Parameter<TArgs...>&& mov);
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
class Parameter<TArg, TArgs...> :
    Parameter<TArgs...>
{
private:
    TArg m_value;
public:
    Parameter(const TArg& val, const TArgs&... vals);
    Parameter(const Parameter<TArg, TArgs...>& cpy);
    Parameter(Parameter<TArg, TArgs...>&& mov);
public:
    Parameter<TArg, TArgs...>& 
        operator=(const Parameter<TArg, TArgs...>& cpy);
    Parameter<TArg, TArgs...>& 
        operator=(Parameter<TArg, TArgs...>&& mov);
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
        test::type::Parameter<TArg, TArgs...>>::Type>::type& At();
    template<std::size_t I>
    typename std::enable_if<I != 0, typename test::type::param::Element<I, 
        test::type::Parameter<TArg, TArgs...>>::Type>::type& At();
    template<std::size_t I>
    const typename std::enable_if<I == 0, typename test::type::param::
        Element<I,test::type::Parameter<TArg, TArgs...>>::Type>::type& 
            At() const;
    template<std::size_t I>
    const typename std::enable_if<I != 0, typename test::type::param::
        Element<I,test::type::Parameter<TArg, TArgs...>>::Type>::type& 
            At() const;
};

template<typename... TArgs>
Parameter<TArgs...>::Parameter()
{}

template<typename... TArgs>
Parameter<TArgs...>::Parameter(const Parameter<TArgs...>& cpy)
{}

template<typename... TArgs>
Parameter<TArgs...>::Parameter(Parameter<TArgs...>&& mov)
{}

template<typename... TArgs>
Parameter<TArgs...>& Parameter<TArgs...>::
    operator=(const Parameter<TArgs...>& cpy)
{
    return *this;
}

template<typename... TArgs>
Parameter<TArgs...>& Parameter<TArgs...>::
    operator=(Parameter<TArgs...>&& mov)
{
    return *this;
}

template<typename... TArgs>
template<typename TRet, typename TFunc, typename... TValues>
TRet Parameter<TArgs...>::FillerFunc(TFunc func, TValues&&... values)
{
    return func(std::forward<TValues>(values)...);
}

template<typename... TArgs>
template<typename TRet, typename TDerived, typename TFuncMmbr, 
    typename... TValues>
typename std::enable_if<std::is_pointer<TDerived>::value, TRet>::type 
    Parameter<TArgs...>::FillerFuncMmbr(TFuncMmbr func_mmbr, TDerived derived, 
        TValues&&... values)
{
    return (derived->*func_mmbr)(std::forward<TValues>(values)...);
}

template<typename... TArgs>
template<typename TRet, typename TDerived, typename TFuncMmbr, 
    typename... TValues>
typename std::enable_if<!std::is_pointer<TDerived>::value, TRet>::type 
    Parameter<TArgs...>::FillerFuncMmbr(TFuncMmbr func_mmbr, TDerived derived, 
        TValues&&... values)
{
    return (derived.*func_mmbr)(std::forward<TValues>(values)...);
}

template<typename... TArgs>
template<typename TRet, typename... TValues>
TRet&& Parameter<TArgs...>::FillerConstruct(TValues&&... values)
{
    return std::move(TRet{std::forward<TValues>(values)...});
}

template<typename... TArgs>
template<typename TRet, typename TFunc>
TRet Parameter<TArgs...>::Fill(TFunc func)
{
    return FillerFunc<TRet>(func);
}

template<typename... TArgs>
template<typename TRet, typename TDerived, typename TFuncMmbr>
TRet Parameter<TArgs...>::Fill(TFuncMmbr func_mmbr, TDerived derived)
{
    return FillerFuncMmbr<TRet>(func_mmbr, derived);
}

template<typename... TArgs>
template<typename TDerived>
TDerived&& Parameter<TArgs...>::Fill()
{
    return std::move(FillerConstruct<TDerived>());
}

template<typename TArg, typename... TArgs>
Parameter<TArg, TArgs...>::
    Parameter(const TArg& val, const TArgs&... vals) :
        Parameter<TArgs...>(vals...),
        m_value(val)
{}

template<typename TArg, typename... TArgs>
Parameter<TArg, TArgs...>::
    Parameter(const Parameter<TArg, TArgs...>& cpy) :
        Parameter<TArgs...>(cpy),
        m_value(cpy.m_value)
{}

template<typename TArg, typename... TArgs>
Parameter<TArg, TArgs...>::
    Parameter(Parameter<TArg, TArgs...>&& mov) :
        Parameter<TArgs...>(std::move(mov)),
        m_value(std::move(mov.m_value))
{}

template<typename TArg, typename... TArgs>
Parameter<TArg, TArgs...>& 
    Parameter<TArg, TArgs...>::
        operator=(const Parameter<TArg, TArgs...>& cpy)
{
    Parameter<TArgs...>::operator=(cpy);
    m_value = cpy.m_value;
    return *this;
}

template<typename TArg, typename... TArgs>
Parameter<TArg, TArgs...>& 
    Parameter<TArg, TArgs...>::
        operator=(Parameter<TArg, TArgs...>&& mov)
{
    Parameter<TArgs...>::operator=(std::move(mov));
    m_value = std::move(mov.m_value);
    return *this;
}

template<typename TArg, typename... TArgs>
template<typename TRet, typename TFunc, typename... TValues>
TRet Parameter<TArg, TArgs...>::
    FillerFunc(TFunc func, TValues&&... values)
{
    return Parameter<TArgs...>::
        template FillerFunc<TRet>(func, std::forward<TValues>(values)...,
            std::forward<TArg>(m_value));
}

template<typename TArg, typename... TArgs>
template<typename TRet, typename TDerived, typename TFuncMmbr, 
    typename... TValues>
TRet Parameter<TArg, TArgs...>::
    FillerFuncMmbr(TFuncMmbr func_mmbr, TDerived derived, TValues&&... values)
{
    return Parameter<TArgs...>::
        template FillerFuncMmbr<TRet>(func_mmbr, derived, 
            std::forward<TValues>(values)..., std::forward<TArg>(m_value));
}

template<typename TArg, typename... TArgs>
template<typename TRet, typename... TValues>
TRet&& Parameter<TArg, TArgs...>::
    FillerConstruct(TValues&&... values)
{
    return std::move(Parameter<TArgs...>::
        template FillerConstruct<TRet>(std::forward<TValues>(values)..., 
            std::forward<TArg>(m_value)));
}

template<typename TArg, typename... TArgs>
template<typename TRet, typename TFunc>
TRet Parameter<TArg, TArgs...>::Fill(TFunc func)
{
    return FillerFunc<TRet>(func);
}

template<typename TArg, typename... TArgs>
template<typename TRet, typename TDerived, typename TFuncMmbr>
TRet Parameter<TArg, TArgs...>::
    Fill(TFuncMmbr func_mmbr, TDerived derived)
{
    return FillerFuncMmbr<TRet>(func_mmbr, derived);
}

template<typename TArg, typename... TArgs>
template<typename TDerived>
TDerived&& Parameter<TArg, TArgs...>::Fill()
{
    return std::move(FillerConstruct<TDerived>());
}

template<typename TArg, typename... TArgs>
template<std::size_t I>
typename std::enable_if<I == 0, typename test::type::param::Element<I, 
    test::type::Parameter<TArg, TArgs...>>::Type>::type& 
        Parameter<TArg, TArgs...>::At()
{
    return m_value;
}

template<typename TArg, typename... TArgs>
template<std::size_t I>
typename std::enable_if<I != 0, typename test::type::param::Element<I, 
    test::type::Parameter<TArg, TArgs...>>::Type>::type& 
        Parameter<TArg, TArgs...>::At()
{
    return Parameter<TArgs...>::
        template At<I - 1>();
}

template<typename TArg, typename... TArgs>
template<std::size_t I>
const typename std::enable_if<I == 0, typename test::type::param::
    Element<I,test::type::Parameter<TArg, TArgs...>>::Type>::type& 
        Parameter<TArg, TArgs...>::At() const
{
    return m_value;
}

template<typename TArg, typename... TArgs>
template<std::size_t I>
const typename std::enable_if<I != 0, typename test::type::param::
    Element<I,test::type::Parameter<TArg, TArgs...>>::Type>::type& 
        Parameter<TArg, TArgs...>::At() const
{
    return Parameter<TArgs...>::
        template At<I - 1>();;
}

} //!test

}//!basic


#endif //!BASIC_TEST_PARAMETER_H_
