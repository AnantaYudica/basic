#include "test/Base.h"

#include <cstdio>
#include <cassert>

struct Variable1 
{
    bool m_isRunCase1;
    Variable1() :
        m_isRunCase1(false)
    {}
};

struct Case1 
{
    void Run(Variable1& var)
    {
        var.m_isRunCase1 = true;
    }
};


template<typename TCase, typename... TVariable>
class TestA :
    public basic::test::Base<TCase, TVariable...>
{
private:
    TCase m_case;
public:
    TestA(TVariable&... vars) :
        basic::test::Base<TCase, TVariable...>(m_case, vars...)
    {}
    ~TestA() {}
};

int main()
{
    TestA<Case1> testa0;
    testa0.Run();

    Variable1 var1_1;
    TestA<Case1, Variable1> testa1(var1_1);
    testa1.Run();
    assert(var1_1.m_isRunCase1);

    Variable1 var2_1;
    Variable1 var2_2;
    TestA<Case1, Variable1, Variable1> testa2(var2_1,
        var2_2);
    testa2.Run();
    assert(var2_1.m_isRunCase1);
    assert(var2_2.m_isRunCase1);

    Variable1 var3_1;
    Variable1 var3_2;
    Variable1 var3_3;
    TestA<Case1, Variable1, Variable1, Variable1> testa3(var3_1,
        var3_2, var3_3);
    testa3.Run();
    assert(var3_1.m_isRunCase1);
    assert(var3_2.m_isRunCase1);
    assert(var3_3.m_isRunCase1);
}
