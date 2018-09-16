#ifndef BASIC_TEST_BASE_H_
#define BASIC_TEST_BASE_H_

#include <utility>

namespace basic
{
namespace test
{

#ifdef EXPERIMENTAL

template<typename TCases, typename... TVariables>
class Base
{
protected:
    TCases& m_cases;
public:
    Base(TCases&);
    Base(const Base<TCases, TVariables...>& cpy);
    virtual ~Base();
    Base(Base<TCases, TVariables...>&&) = delete;
public:
    Base<TCases, TVariables...>& 
        operator=(const Base<TCases, TVariables...>& cpy);
    Base<TCases, TVariables...>& 
        operator=(const Base<TCases, TVariables...>&&) = delete;
public:
    void Run();
};

template<typename TCases, typename TVariable, 
    typename... TVariables>
class Base<TCases, TVariable, TVariables...> : 
    public Base<TCases, TVariables...>
{
private:
    TVariable& m_var;
public:
    Base(TCases& cases, TVariable& var, TVariables&... vars);
    Base(const Base<TCases, TVariable, TVariables...>& cpy);
    virtual ~Base();
    Base(Base<TCases, TVariable, TVariables...>&&) = delete;
public:
    Base<TCases, TVariable, TVariables...>& 
        operator=(const Base<TCases, TVariables...>& cpy);
    Base<TCases, TVariables...>& 
        operator=(const Base<TCases, TVariable, TVariables...>&&) = delete;
public:
    void Run();
};

template<typename TCases, typename... TVariables>
Base<TCases, TVariables...>::Base(TCases& c) :
    m_cases(c)
{}

template<typename TCases, typename... TVariables>
Base<TCases, TVariables...>::Base(const Base<TCases, TVariables...>& cpy) :
    m_cases(cpy.m_cases)
{}

template<typename TCases, typename... TVariables>
Base<TCases, TVariables...>::~Base()
{}

template<typename TCases, typename... TVariables>
Base<TCases, TVariables...>& Base<TCases, TVariables...>::
    operator=(const Base<TCases, TVariables...>& cpy)
{
    m_cases = cpy.m_cases;
    return *this;
}

template<typename TCases, typename... TVariables>
void Base<TCases, TVariables...>::Run()
{}

template<typename TCases, typename TVariable, 
    typename... TVariables>
Base<TCases, TVariable, TVariables...>::
    Base(TCases& cases, TVariable& var, TVariables&... vars) :
        Base<TCases, TVariables...>(cases, vars...),
        m_var(var)
{}

template<typename TCases, typename TVariable, 
    typename... TVariables>
Base<TCases, TVariable, TVariables...>::
    Base(const Base<TCases, TVariable, TVariables...>& cpy) :
        Base<TCases, TVariables...>(cpy),
        m_var(cpy.m_var)
{}

template<typename TCases, typename TVariable, 
    typename... TVariables>
Base<TCases, TVariable, TVariables...>::~Base()
{}

template<typename TCases, typename TVariable, 
    typename... TVariables>
Base<TCases, TVariable, TVariables...>& 
    Base<TCases, TVariable, TVariables...>::
        operator=(const Base<TCases, TVariables...>& cpy)
{
    Base<TCases, TVariables...>::operator=(cpy);
    m_var = cpy.m_var;
    return *this;
}

template<typename TCases, typename TVariable, 
    typename... TVariables>
void Base<TCases, TVariable, TVariables...>::Run()
{
    Base<TCases>::m_cases.Run(m_var);
    Base<TCases, TVariables...>::Run();
}

#else
struct Base
{
    virtual ~Base() {};
    virtual void Test() = 0;
};
#endif

} //!test

} //!basic

#endif //!BASIC_TEST_BASE_H_
