#ifndef BASIC_TEST_REGISTER_H_
#define BASIC_TEST_REGISTER_H_

#include "reg/Base.h"

#include <algorithm>

namespace basic
{
namespace test
{

template<typename TTest, typename TDerived>
class Register :
    public basic::test::reg::Base
{
private:
    TDerived* m_derived;
    const char* m_file;
    const std::size_t m_line;
public:
    template<std::size_t S>
    Register(TDerived* ptr, const char (&file)[S], const std::size_t& line);
    Register(const Register<TTest, TDerived>&) = delete;
    Register(Register<TTest, TDerived>&&);
    ~Register();
public:
    Register<TTest, TDerived>& 
        operator=(const Register<TTest, TDerived>&) = delete;
    Register<TTest, TDerived>& operator=(Register<TTest, TDerived>&&) = delete;
public:
    int Run();
    const char* File() const;
    const std::size_t& Line() const;
};

template<typename TTest, typename TDerived>
    template<std::size_t S>
Register<TTest, TDerived>::Register(TDerived* derived, const char (&file)[S], 
    const std::size_t& line) :
        m_derived(derived),
        m_file(file),
        m_line(line)
{
    TTest::GetInstance().List().push_back(this);
}

template<typename TTest, typename TDerived>
Register<TTest, TDerived>::Register(Register<TTest, TDerived>&& mov) :
    m_derived(mov.m_derived),
    m_file(mov.m_file),
    m_line(mov.m_line)
{
    mov.m_derived = nullptr;
    auto fn = std::find(TTest::GetInstance().List().begin(),
        TTest::GetInstance().List().end(), &mov);
    if (fn != TTest::GetInstance().List().end())
        *fn = this;
    else
        TTest::GetInstance().List().push_back(this);
}

template<typename TTest, typename TDerived>
Register<TTest, TDerived>::~Register()
{
    if (m_derived != nullptr)
    {
        delete m_derived;
        m_derived = nullptr;
    } 
}

template<typename TTest, typename TDerived>
int Register<TTest, TDerived>::Run()
{
    if (m_derived != nullptr)
        m_derived->Run();
    else
    {
        TTest::Error("derived is nullptr");
    }
    return TTest::GetInstance().Status().Get();
}

template<typename TTest, typename TDerived>
const char* Register<TTest, TDerived>::File() const
{
    return m_file;
}

template<typename TTest, typename TDerived>
const std::size_t& Register<TTest, TDerived>::Line() const
{
    return m_line;
}

namespace reg
{

template<typename TTest, typename TDerived, std::size_t S>
Register<TTest, TDerived> Make(TDerived* derived, 
    const char (&file)[S], const std::size_t& line)
{
    return Register<TTest, TDerived>(derived, file, line);
}

} //!reg

} //!test

} //!basic

#endif //!BASIC_TEST_REGISTER_H_