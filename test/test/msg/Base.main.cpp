#define USING_BASIC_TEST_MEMORY
#define EXPERIMENTAL
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/msg/Base.h"

#include <cstdio>

struct TestA1 {};
struct TestA2 {};
struct TestA3 {};

class TestA :
    public basic::test::msg::Base<TestA1>,
    public basic::test::msg::Base<TestA2>,
    public basic::test::msg::Base<TestA3>
{
    basic::test::msg::Format formatI1, formatD1, formatE1;
    basic::test::msg::Format formatI2, formatD2, formatE2;
    basic::test::msg::Format formatI3, formatD3, formatE3;
public:
    TestA() :
        formatI1("Test TestA1 : %s"),
        formatI2("Test TestA2 : %s"),
        formatI3("Test TestA3 : %s"),
        formatD1(formatI1, formatI1.Size() + 10, "type %d"),
        formatD2(formatI2, formatI1.Size() + 10, "type %d"),
        formatD3(formatI3, formatI1.Size() + 10, "type %d"),
        formatE1("Error TestA1 msg %s"),
        formatE2("Error TestA2 msg %s"),
        formatE3("Error TestA3 msg %s")
    {}
public:
    const basic::test::msg::Format& Info(TestA1&&) const
    {
        return formatI1;
    }
    const basic::test::msg::Format& Info(TestA2&&) const
    {
        return formatI2;
    }
    const basic::test::msg::Format& Info(TestA3&&) const
    {
        return formatI3;
    }
    const basic::test::msg::Format& Debug(TestA1&&) const
    {
        return formatD1;
    }
    const basic::test::msg::Format& Debug(TestA2&&) const
    {
        return formatD2;
    }
    const basic::test::msg::Format& Debug(TestA3&&) const
    {
        return formatD3;
    }
    const basic::test::msg::Format& Error(TestA1&&) const
    {
        return formatE1;
    }
    const basic::test::msg::Format& Error(TestA2&&) const
    {
        return formatE2;
    }
    const basic::test::msg::Format& Error(TestA3&&) const
    {
        return formatE3;
    }
};


int main()
{
    TestA a;
    printf(a.Info(TestA1()).Value(), "a");
    printf("\n");
    printf(a.Info(TestA2()).Value(), "b");
    printf("\n");
    printf(a.Info(TestA3()).Value(), "c");
    printf("\n");
    printf(a.Debug(TestA1()).Value(), 1);
    printf("\n");
    printf(a.Debug(TestA2()).Value(), 2);
    printf("\n");
    printf(a.Debug(TestA3()).Value(), 3);
    printf("\n");
    printf(a.Error(TestA1()).Value(), "error 1");
    printf("\n");
    printf(a.Error(TestA2()).Value(), "error 2");
    printf("\n");
    printf(a.Error(TestA3()).Value(), "error 3");
    printf("\n");
}
