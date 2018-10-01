#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/Register.h"

#include "test/Base.h"


template<typename T1, typename T2>
class Variable1
{
public:
};

class Case1
{
public:
    template<typename T1, typename T2>
    void Run(Variable1<T1, T2>&)
    {
        std::cout << "Case1 Run" << std::endl;
    }
};

template<typename... TVariable>
class TestA :
    public basic::test::Base<Case1, TVariable...>
{
private:
    Case1 m_case;
public:
    TestA(TVariable&... vars) :
        basic::test::Base<Case1, TVariable...>(m_case, vars...)
    {}
    ~TestA() {}
};

Variable1<int, int> var1_1;

basic::test::Register<BASIC_TEST, TestA<Variable1<int, int>>> 
    t1(new TestA<Variable1<int, int>>(var1_1), __FILE__, __LINE__);


REGISTER_TEST(t2, new TestA<Variable1<int, int>, 
    Variable1<int, int>>(var1_1, var1_1));


int main()
{
    return RUN_TEST();
}
