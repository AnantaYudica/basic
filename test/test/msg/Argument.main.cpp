#define USING_BASIC_TEST_MEMORY
#define EXPERIMENTAL
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/msg/Argument.h"
#include "test/msg/arg/type/Name.h"
#include "test/msg/arg/type/Value.h"
#include "test/msg/arg/type/Function.h"
#include "test/msg/arg/type/val/Sequence.h"
#include "test/msg/arg/type/val/seq/At.h"
#include "test/msg/arg/type/param/Name.h"
#include "test/msg/arg/Value.h"
#include "test/msg/arg/val/Function.h"
#include "test/msg/arg/val/Sequence.h"
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
    template<typename... TArgs>
    void Foo5(int, TArgs&&... args)
    {
        printf("foo5(int, %d %d %d %d)\n", std::forward<TArgs>(args)...);
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

template<typename... TArgs>
int Print(const char* format, TArgs&&... args)
{
    return printf(format, std::forward<TArgs>(args)...);
}

int Foo1()
{
    return printf("Print Foo1()\n");
}

int Foo2(int&& i)
{
    return printf("Print Foo2(i = %d)\n", i);
}

int main()
{
    ATest a1;
    basic::test::Variable<> var1;
    basic::test::msg::Argument<TestA1> arg1;
    arg1.Call<void>(&ATest::Foo1, a1, var1, 2);
    arg1.Call<int>(&Print, var1, std::move("print\n"));

    basic::test::Variable<int, char> var2;
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::Name<0>> arg2;
    arg2.Call<void>(&ATest::Foo2, a1, var2, 2);
    arg2.Call<int>(&Print, var2, std::move("Print Name : %s\n"));

    basic::test::Variable<int, char> var3;
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::Name<1>> arg3;
    arg3.Call<void>(&ATest::Foo2, a1, var3, 2);
    arg3.Call<int>(&Print, var3, std::move("Print Name : %s\n"));

    basic::test::Variable<A, char> var4;
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::Name<0>> arg4;
    arg4.Call<void>(&ATest::Foo2, a1, var4, 2);
    arg4.Call<int>(&Print, var4, std::move("Print Name : %s\n"));
    
    basic::test::Variable<basic::test::type::Parameter<int, char>> var5;
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::param::Name<0>> arg5;
    arg5.Call<void>(&ATest::Foo3, a1, var5, 2);
    arg5.Call<int>(&Print, var5, std::move("Print param Name : %s\n"));
    
    basic::test::Variable<basic::test::type::Value<int, 14>, char> var6;
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::Value<0>> arg6;
    arg6.Call<void>(&ATest::Foo4, a1, var6, 2);
    arg6.Call<int>(&Print, var6, std::move("Print type value : %d\n"));
    
    basic::test::Variable<basic::test::type::val::Sequence<int, 
        14, 4, 6, 11>, char> var7;
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::
        val::Sequence<0>> arg7;
    arg7.Call<void>(&ATest::Foo5, a1, var7, 2);
    arg7.Call<int>(&Print, var7, 
        std::move("Print type val sequence : %d %d %d %d\n"));
    
    basic::test::msg::Argument<TestA1, 
        basic::test::msg::arg::type::val::seq::At<0, 0>> arg7_0_0;
    basic::test::msg::Argument<TestA1, 
        basic::test::msg::arg::type::val::seq::At<0, 1>> arg7_0_1;
    basic::test::msg::Argument<TestA1, 
        basic::test::msg::arg::type::val::seq::At<0, 2>> arg7_0_2;
    basic::test::msg::Argument<TestA1, 
        basic::test::msg::arg::type::val::seq::At<0, 3>> arg7_0_3;
    arg7_0_0.Call<void>(&ATest::Foo4, a1, var7, 2);
    arg7_0_0.Call<int>(&Print, var7, std::move("Print type value at 0 : %d\n"));
    arg7_0_1.Call<void>(&ATest::Foo4, a1, var7, 2);
    arg7_0_1.Call<int>(&Print, var7, std::move("Print type value at 1 : %d\n"));
    arg7_0_2.Call<void>(&ATest::Foo4, a1, var7, 2);
    arg7_0_2.Call<int>(&Print, var7, std::move("Print type value at 2 : %d\n"));
    arg7_0_3.Call<void>(&ATest::Foo4, a1, var7, 2);
    arg7_0_3.Call<int>(&Print, var7, std::move("Print type value at 3 : %d\n"));

    basic::test::Variable<basic::test::Value<int>, char> var8(4);
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::Value<0>> arg8;
    arg8.Call<void>(&ATest::Foo4, a1, var8, 2);
    arg8.Call<int>(&Print, var8, std::move("Print var value : %d\n"));
    
    basic::test::Variable<basic::test::val::Sequence<int, 4>, char> var9(4, 2, 10, 1);
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::val::Sequence<0>> arg9;
    arg9.Call<void>(&ATest::Foo4, a1, var9, 2);
    arg9.Call<int>(&Print, var9, 
        std::move("Print var value : %d %d %d %d\n"));

    basic::test::Variable<basic::test::type::Function<int(), &Foo1>> var10;
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::
        Function<0>> arg10;
    arg10.Call<void>(&ATest::Foo4, a1, var10, 2);
    arg10.Call<int>(&Print, var10, std::move("Print var value : %d\n"));
    
    basic::test::Variable<basic::test::Value<int>,
        basic::test::type::Function<int(int&&), &Foo2>> var11(4);
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::
        Function<1, basic::test::msg::arg::Value<0>>> arg11;
    arg11.Call<void>(&ATest::Foo4, a1, var11, 2);
    arg11.Call<int>(&Print, var11, std::move("Print var value : %d\n"));
    
    basic::test::Variable<basic::test::val::Function<int()>> var12(&Foo1);
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::
        Function<0>> arg12;
    arg12.Call<void>(&ATest::Foo4, a1, var12, 2);
    arg12.Call<int>(&Print, var12, std::move("Print var value : %d\n"));
    
    basic::test::Variable<basic::test::Value<int>,
        basic::test::val::Function<int(int&&)>> var13(14, &Foo2);
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::
        Function<1, basic::test::msg::arg::Value<0>>> arg13;
    arg13.Call<void>(&ATest::Foo4, a1, var13, 2);
    arg13.Call<int>(&Print, var13, std::move("Print var value : %d\n"));
}
