#include "test/Case.h"

#include "test/val/Sequence.h"
#include "test/type/Parameter.h"
#include "test/var/At.h"

#include "test/var/val/Sequence.h"

#include <cstdio>
#include <cassert>

struct Case1 {};
struct Case2 {};
struct Case3 {};

enum message
{
    m_undefined,
    m_info,
    m_debug,
    m_error
};

template<typename TCase>
struct CaseIndex
{};

template<>
struct CaseIndex<Case1>
{
    static constexpr std::size_t Value = 0;
};
template<>
struct CaseIndex<Case2>
{
    static constexpr std::size_t Value = 1;
}; 
template<>
struct CaseIndex<Case3>
{
    static constexpr std::size_t Value = 2;
};

using Variable = basic::test::Variable<basic::test::val::Sequence<bool, 3>,
    basic::test::val::Sequence<message, 3>>;

template<typename... TCases>
struct TestA :
    basic::test::Case<TestA<TCases...>, 
    basic::test::type::Parameter<TCases...>>
{
    TestA() :
        basic::test::Case<TestA, 
            basic::test::type::Parameter<TCases...>>(*this)
    {}
    template<typename TVar>
    bool Result(const Case1&, TVar& var)
    {
        var.Get().template At<0>() = true;
        return true;
    }

    template<typename TVar>
    bool Result(const Case2&, TVar& var)
    {
        var.Get().template At<1>() = true;
        return false;
    }

    template<typename TVar>
    bool Result(const Case3&, TVar& var)
    {
        var.Get().template At<2>() = true;
        return true;
    }

    template<typename TCaseId, typename TVar>
    void Info(const TCaseId&, TVar& var)
    {
        basic::test::var::At<1>(var).Get().
            template At<CaseIndex<TCaseId>::Value>() = message::m_info;
    }

    template<typename TCaseId, typename TVar>
    void Debug(const TCaseId&, TVar& var)
    {
        basic::test::var::At<1>(var).Get().
            template At<CaseIndex<TCaseId>::Value>() = message::m_debug;
    }

    template<typename TCaseId, typename TVar>
    void Error(const TCaseId&, TVar& var)
    {
        basic::test::var::At<1>(var).Get().
            template At<CaseIndex<TCaseId>::Value>() = message::m_error;
    } 
};

int main()
{
    TestA<> testa0;

    Variable var1{ false, false, false, 
        m_undefined, m_undefined, m_undefined };
    TestA<Case1> testa1;
    testa1.Run(var1);
    assert(var1.Get().template At<0>() == true);
    assert(basic::test::var::At<1>(var1).Get().
        template At<CaseIndex<Case1>::Value>() == message::m_debug);
    assert(var1.Get().template At<1>() == false);
    assert(basic::test::var::At<1>(var1).Get().
        template At<CaseIndex<Case2>::Value>() == message::m_undefined);
    assert(var1.Get().template At<2>() == false);
    assert(basic::test::var::At<1>(var1).Get().
        template At<CaseIndex<Case3>::Value>() == message::m_undefined);

    Variable var2{ false, false, false, 
        m_undefined, m_undefined, m_undefined };
    TestA<Case1, Case2> testa2;
    testa2.Run(var2);
    assert(var2.Get().template At<0>() == true);
    assert(basic::test::var::At<1>(var2).Get().
        template At<CaseIndex<Case1>::Value>() == message::m_debug);
    assert(var2.Get().template At<1>() == true);
    assert(basic::test::var::At<1>(var2).Get().
        template At<CaseIndex<Case2>::Value>() == message::m_error);
    assert(var2.Get().template At<2>() == false);
    assert(basic::test::var::At<1>(var2).Get().
        template At<CaseIndex<Case3>::Value>() == message::m_undefined);

    Variable var3{ false, false, false, 
        m_undefined, m_undefined, m_undefined };
    TestA<Case1, Case2, Case3> testa3;
    testa3.Run(var3);
    assert(var3.Get().template At<0>() == true);
    assert(basic::test::var::At<1>(var3).Get().
        template At<CaseIndex<Case1>::Value>() == message::m_debug);
    assert(var3.Get().template At<1>() == true);
    assert(basic::test::var::At<1>(var3).Get().
        template At<CaseIndex<Case2>::Value>() == message::m_error);
    assert(var3.Get().template At<2>() == true);
    assert(basic::test::var::At<1>(var3).Get().template 
        At<CaseIndex<Case3>::Value>() == message::m_debug);

}
