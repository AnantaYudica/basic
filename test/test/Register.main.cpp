#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/Register.h"
#include "test/Base.h"

#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>

struct StatusError
{
    int& m_err;
    StatusError(int& err) :
        m_err(err)
    {}
    int Get()
    {
        return m_err;
    }
};

struct Test
{
    static Test ms_instance;
    std::vector<basic::test::reg::Base*> m_lists;
    int m_err;
    StatusError m_status;
    Test() :
        m_lists(),
        m_err(),
        m_status(m_err)
    {}
    static Test& GetInstance()
    {
        return ms_instance;
    }
    std::vector<basic::test::reg::Base*>& List()
    {
        return m_lists;
    }
    static void Error(const char* msg)
    {
        ms_instance.m_err += 1;
    }
    static StatusError& Status()
    {
        return ms_instance.m_status;
    }

};

Test Test::ms_instance;

template<typename T1, typename T2>
struct Variable1
{};

bool isCase1Run = false;

struct Case1
{
public:
    template<typename T1, typename T2>
    void Run(Variable1<T1, T2>&)
    {
        isCase1Run = true;
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
    Variable1<int, int> var1_1;
    int t1_line = __LINE__ + 2;
    basic::test::Register<Test, TestA<Case1, Variable1<int, int>>>
        t1(new TestA<Case1, Variable1<int, int>>(var1_1), __FILE__, t1_line);
    t1.Run();
    assert(isCase1Run == true);
    printf("t1_line : %d, t1.Line() : %zd\n", t1_line, t1.Line());
    assert(t1.Line() == t1_line);
    printf("__FILE__ : %s,  t1.File() : %s\n", __FILE__, t1.File());
    assert(strcmp(__FILE__, t1.File()) == 0);
}
