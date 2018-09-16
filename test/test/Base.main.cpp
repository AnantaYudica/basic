#define EXPERIMENTAL
#include "test/Base.h"

#include <iostream>

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

int main()
{
    Variable1<int, int> var1_1;
    Variable1<char, char> var1_2;
    Variable1<short, char> var1_3;
    TestA<Variable1<int, int>, Variable1<char, char>,
        Variable1<short, char>> a1(var1_1, var1_2, var1_3);
    a1.Run();
}
