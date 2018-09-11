#define USING_BASIC_TEST_MEMORY
#define EXPERIMENTAL
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/msg/Argument.h"
#include "test/type/Parameter.h"
#include "test/type/param/Name.h"
#include "test/type/Value.h"

#include <cstdio>

struct TestA1 {};

class ATest
{
public:
    template<typename... TArgs>
    void Foo1(int, TArgs&&... args)
    {
        printf("foo1(int, ...)\n");
    }
    template<typename... TArgs>
    void Foo2(int, TArgs&&... args)
    {
        printf("foo2(int, %s)\n", std::forward<TArgs>(args)...);
    }
    template<typename... TArgs>
    void Foo3(int, TArgs&&... args)
    {
        printf("foo3(int, %s)\n", std::forward<TArgs>(args)...);
    }
    template<typename... TArgs>
    void Foo4(int, TArgs&&... args)
    {
        printf("foo4(int, %d)\n", std::forward<TArgs>(args)...);
    }
};

struct A
{};

template<typename... TArgs>
struct ParamA
{};

BASIC_TEST_TYPE_NAME("int", int);
BASIC_TEST_TYPE_NAME("char", char);

template<>
struct basic::test::type::Name<A>
{
    static basic::test::CString<char> CStr()
    {
        static char _A[] = "A";
        return {_A};
    }
};

template<typename... TArgs>
struct basic::test::type::Name<ParamA<TArgs...>>
{
    static basic::test::CString<const char> CStr()
    {
        static char _ParamA[] = "ParamA";
        return {_ParamA};
    }
};

int main()
{
    ATest a1;
    basic::test::Variable<> var1;
    basic::test::msg::Argument<TestA1> arg1;
    arg1.Call<void>(&ATest::Foo1, a1, var1, 2);

    basic::test::Variable<int, char> var2;
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::TypeName<0>> arg2;
    arg2.Call<void>(&ATest::Foo2, a1, var2, 2);

    basic::test::Variable<int, char> var3;
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::TypeName<1>> arg3;
    arg3.Call<void>(&ATest::Foo2, a1, var3, 2);

    
    basic::test::Variable<A, char> var4;
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::TypeName<0>> arg4;
    arg4.Call<void>(&ATest::Foo2, a1, var4, 2);
    
    basic::test::Variable<basic::test::type::Parameter<int, char>> var5;
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::TypeParamName<0>> arg5;
    arg5.Call<void>(&ATest::Foo3, a1, var5, 2);
    
    basic::test::Variable<basic::test::type::Value<int, 14>, char> var6;
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::TypeValue<0>> arg6;
    arg6.Call<void>(&ATest::Foo4, a1, var6, 2);

    basic::test::Variable<basic::test::var::Value<int>, char> var7(4);
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::VarValue<0>> arg7;
    arg7.Call<void>(&ATest::Foo4, a1, var7, 2);
}
