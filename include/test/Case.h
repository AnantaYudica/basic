#ifndef BASIC_TEST_CASE_H_
#define BASIC_TEST_CASE_H_

#include "type/Parameter.h"
#include "Variable.h"

#include <utility>

namespace basic
{
namespace test
{
namespace case_
{

template<typename TDerived, typename... TVariableArgs>
void Run(TDerived& d, Variable<TVariableArgs...>& var)
{}

template<typename TDerived, typename... TVariableArgs, 
    typename TCaseId, typename... TCaseIds>
void Run(TDerived& d, test::Variable<TVariableArgs...>& var, const TCaseId& case_id, 
    const TCaseIds&... case_ids)
{
    if (d.Result(case_id, var))
    {
        d.Debug(case_id, var);
    }
    else
    {
        d.Error(case_id, var);
    }
    Run(d, var, case_ids...);
}

} //!case_

template<typename TDerived, typename TCaseId>
class Case
{
private:
    TDerived& m_derived;
public:
    Case(TDerived& d);
    Case(const Case<TDerived, TCaseId>& cpy);
    Case(Case<TDerived, TCaseId>&&) = delete;
public:
    Case<TDerived, TCaseId>& operator=(const Case<TDerived, TCaseId>& cpy);
    Case<TDerived, TCaseId>& operator=(Case<TDerived, TCaseId>&&) = delete;
public:
    template<typename... TVariableArgs>
    void Run(test::Variable<TVariableArgs...>& var);
};

template<typename TDerived, typename... TCaseIds>
class Case<TDerived, type::Parameter<TCaseIds...>>
{
private:
    TDerived& m_derived;
public:
    Case(TDerived& d);
    Case(const Case<TDerived, type::Parameter<TCaseIds...>>& cpy);
    Case(Case<TDerived, type::Parameter<TCaseIds...>>&&) = delete;
public:
    Case<TDerived, type::Parameter<TCaseIds...>>& 
        operator=(const Case<TDerived, type::Parameter<TCaseIds...>>& cpy);
    Case<TDerived, type::Parameter<TCaseIds...>>& 
        operator=(Case<TDerived, type::Parameter<TCaseIds...>>&&) = delete;
public:
    template<typename... TVariableArgs>
    void Run(test::Variable<TVariableArgs...>& var);
};

template<typename TDerived, typename TCaseId>
Case<TDerived, TCaseId>::Case(TDerived& d) :
    m_derived(d)
{}

template<typename TDerived, typename TCaseId>
Case<TDerived, TCaseId>::Case(const Case<TDerived, TCaseId>& cpy) :
    m_derived(cpy.m_derived)
{}

template<typename TDerived, typename TCaseId>
Case<TDerived, TCaseId>& Case<TDerived, TCaseId>::
    operator=(const Case<TDerived, TCaseId>& cpy)
{
    m_derived = cpy.m_derived;
    return *this;
}

template<typename TDerived, typename TCaseId>
template<typename... TVariableArgs>
void Case<TDerived, TCaseId>::Run(Variable<TVariableArgs...>& var)
{
    case_::Run(m_derived, var, TCaseId());
}

template<typename TDerived, typename... TCaseIds>
Case<TDerived, type::Parameter<TCaseIds...>>::Case(TDerived& d) :
    m_derived(d)
{}

template<typename TDerived, typename... TCaseIds>
Case<TDerived, type::Parameter<TCaseIds...>>::
    Case(const Case<TDerived, type::Parameter<TCaseIds...>>& cpy) :
        m_derived(cpy.m_derived)
{}

template<typename TDerived, typename... TCaseIds>
Case<TDerived, type::Parameter<TCaseIds...>>& 
    Case<TDerived, type::Parameter<TCaseIds...>>::
        operator=(const Case<TDerived, type::Parameter<TCaseIds...>>& cpy)
{
    m_derived = cpy.m_derived;
    return *this;
}

template<typename TDerived, typename... TCaseIds>
template<typename... TVariableArgs>
void Case<TDerived, type::Parameter<TCaseIds...>>::
    Run(test::Variable<TVariableArgs...>& var)
{
    case_::Run(m_derived, var, TCaseIds()...);
}

} //!test

} //!basic

#endif //!BASIC_TEST_CASE_H_
