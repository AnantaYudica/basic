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
#include "test/msg/arg/type/param/name/At.h"
#include "test/msg/arg/Value.h"
#include "test/msg/arg/val/Function.h"
#include "test/msg/arg/val/Parameter.h"
#include "test/msg/arg/val/Sequence.h"
#include "test/msg/arg/val/param/At.h"
#include "test/msg/arg/val/seq/At.h"

#include "test/msg/arg/type/Index.h"
#include "test/type/Index.h"

#include "test/CString.h"
#include "test/cstr/out/Argument.h"

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
    void Foo4f(int, TArgs&&... args)
    {
        printf("foo4(int, %f)\n", std::forward<TArgs>(args)...);
    }
    template<typename... TArgs>
    void Foo5(int, TArgs&&... args)
    {
        printf("foo5(int, %d %d %d %d)\n", std::forward<TArgs>(args)...);
    }
    template<typename... TArgs>
    void Foo6(int, TArgs&&... args)
    {
        printf("foo5(int, %d %f %d %f)\n", std::forward<TArgs>(args)...);
    }
    template<typename TChar>
    void Foo7(int, basic::test::CString<TChar>&& cstr)
    {
        printf("foo7(int, %s)\n", *cstr);
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
    return printf(format, 
        basic::test::out::Argument<TArgs>::Value(args)...);
}

int Foo1()
{
    return printf("Print Foo1()\n");
}

int Foo2(int&& i)
{
    return printf("Print Foo2(i = %d)\n", i);
}

int Foo3(int&& i1, float&& f, long&& l, int&& i2)
{
    return printf("Print Foo3(i1 = %d, f = %f, l = %d, "
        "i2 = %d)\n", i1, f, l, i2);
}

int Foo3(int&& i1, int&& i2, int&& i3, int&& i4)
{
    return printf("Print Foo3(i1 = %d, i2 = %d, i3 = %d, "
        "i4 = %d)\n", i1, i2, i3, i4);
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
    printf("get arg2 value from var2 : %s\n", *arg2.Get(var2));
    arg2.Call<void>(&ATest::Foo7, a1, var2, 2);
    arg2.Call<int>(&Print, var2, std::move("Print Name : %s\n"));

    basic::test::Variable<int, char> var3;
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::Name<1>> arg3;
    printf("get arg3 value from var3 : %s\n", *arg3.Get(var3));
    arg3.Call<void>(&ATest::Foo7, a1, var3, 2);
    arg3.Call<int>(&Print, var3, std::move("Print Name : %s\n"));

    basic::test::Variable<A, char> var4;
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::Name<0>> arg4;
    printf("get arg4 value from var4 : %s\n", *arg4.Get(var4));
    arg4.Call<void>(&ATest::Foo7, a1, var4, 2);
    arg4.Call<int>(&Print, var4, std::move("Print Name : %s\n"));
    
    basic::test::Variable<basic::test::type::Parameter<int, char>> var5;
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::param::Name<0>> arg5;
    printf("get arg5 value from var5 : %s\n", *arg5.Get(var5));
    arg5.Call<void>(&ATest::Foo7, a1, var5, 2);
    arg5.Call<int>(&Print, var5, std::move("Print param Name : %s\n"));

    basic::test::msg::Argument<TestA1, 
        basic::test::msg::arg::type::param::name::At<0, 0>> arg5_0_0;
    basic::test::msg::Argument<TestA1, 
        basic::test::msg::arg::type::param::name::At<0, 1>> arg5_0_1;
    printf("get arg5_0_0 value from var5 : %s\n", *arg5_0_0.Get(var5));
    arg5_0_0.Call<int>(&Print, var5, 
        std::move("Print get arg5_0_0 from var5 at 0 : %s\n"));

    arg5_0_0.Call<void>(&ATest::Foo7, a1, var5, 2);
    printf("get arg5_0_1 value from var5 : %s\n", *arg5_0_1.Get(var5));
    arg5_0_1.Call<void>(&ATest::Foo7, a1, var5, 2);
    arg5_0_1.Call<int>(&Print, var5, 
        std::move("Print get arg5_0_1 from var5 at 1 : %s\n"));
    
    basic::test::Variable<basic::test::type::Value<int, 14>, char> var6;
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::Value<0>> arg6;
    printf("get arg6 value from var6 : %d\n", arg6.Get(var6));
    arg6.Call<void>(&ATest::Foo4, a1, var6, 2);
    arg6.Call<int>(&Print, var6, std::move("Print type value : %d\n"));
    
    basic::test::Variable<basic::test::type::val::Sequence<int, 
        14, 4, 6, 11>, char> var7;
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::
        val::Sequence<0>> arg7;
    printf("get arg7 at 0 value from var7 : %d\n", arg7.Get<0>(var7));
    printf("get arg7 at 1 value from var7 : %d\n", arg7.Get<1>(var7));
    printf("get arg7 at 2 value from var7 : %d\n", arg7.Get<2>(var7));
    printf("get arg7 at 3 value from var7 : %d\n", arg7.Get<3>(var7));
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
    printf("get arg7_0_0 value from var7 : %d\n", arg7_0_0.Get(var7));
    arg7_0_0.Call<void>(&ATest::Foo4, a1, var7, 2);
    arg7_0_0.Call<int>(&Print, var7, std::move("Print type value at 0 : %d\n"));
    printf("get arg7_0_1 value from var7 : %d\n", arg7_0_1.Get(var7));
    arg7_0_1.Call<void>(&ATest::Foo4, a1, var7, 2);
    arg7_0_1.Call<int>(&Print, var7, std::move("Print type value at 1 : %d\n"));
    printf("get arg7_0_2 value from var7 : %d\n", arg7_0_2.Get(var7));
    arg7_0_2.Call<void>(&ATest::Foo4, a1, var7, 2);
    arg7_0_2.Call<int>(&Print, var7, std::move("Print type value at 2 : %d\n"));
    printf("get arg7_0_3 value from var7 : %d\n", arg7_0_3.Get(var7));
    arg7_0_3.Call<void>(&ATest::Foo4, a1, var7, 2);
    arg7_0_3.Call<int>(&Print, var7, std::move("Print type value at 3 : %d\n"));

    basic::test::Variable<basic::test::Value<int>, char> var8(4);
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::Value<0>> arg8;
    printf("get arg8 value from var8  : %d\n", arg8.Get(var8));
    arg8.Call<void>(&ATest::Foo4, a1, var8, 2);
    arg8.Call<int>(&Print, var8, std::move("Print var value : %d\n"));
    
    basic::test::Variable<basic::test::val::Sequence<int, 4>, char> var9(4, 2, 10, 1);
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::val::Sequence<0>> arg9;
    printf("get arg9 at 0 value from var9 : %d\n", arg9.Get<0>(var9));
    printf("get arg9 at 1 value from var9 : %d\n", arg9.Get<1>(var9));
    printf("get arg9 at 2 value from var9 : %d\n", arg9.Get<2>(var9));
    printf("get arg9 at 3 value from var9 : %d\n", arg9.Get<3>(var9));
    arg9.Call<void>(&ATest::Foo4, a1, var9, 2);
    arg9.Call<int>(&Print, var9, 
        std::move("Print var value : %d %d %d %d\n"));
    
    basic::test::msg::Argument<TestA1, 
        basic::test::msg::arg::val::seq::At<0, 0>> arg9_0_0;
    basic::test::msg::Argument<TestA1, 
        basic::test::msg::arg::val::seq::At<0, 1>> arg9_0_1;
    basic::test::msg::Argument<TestA1, 
        basic::test::msg::arg::val::seq::At<0, 2>> arg9_0_2;
    basic::test::msg::Argument<TestA1, 
        basic::test::msg::arg::val::seq::At<0, 3>> arg9_0_3;
        
    printf("get arg9_0_0 value from var9 : %d\n", arg9_0_0.Get(var9));
    arg9_0_0.Call<void>(&ATest::Foo4, a1, var9, 2);
    arg9_0_0.Call<int>(&Print, var9, std::move("Print type value at 0 : %d\n"));
    
    printf("get arg9_0_1 value from var9 : %d\n", arg9_0_1.Get(var9));
    arg9_0_1.Call<void>(&ATest::Foo4, a1, var9, 2);
    arg9_0_1.Call<int>(&Print, var9, std::move("Print type value at 1 : %d\n"));
    
    printf("get arg9_0_2 value from var9 : %d\n", arg9_0_2.Get(var9));
    arg9_0_2.Call<void>(&ATest::Foo4, a1, var9, 2);
    arg9_0_2.Call<int>(&Print, var9, std::move("Print type value at 2 : %d\n"));
    
    printf("get arg9_0_3 value from var9 : %d\n", arg9_0_3.Get(var9));
    arg9_0_3.Call<void>(&ATest::Foo4, a1, var9, 2);
    arg9_0_3.Call<int>(&Print, var9, std::move("Print type value at 3 : %d\n"));

    basic::test::Variable<basic::test::type::Function<int(), &Foo1>> var10;
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::
        Function<0>> arg10;
    printf("get arg10 value from var10  : %d\n", arg10.Get(var10));
    arg10.Call<void>(&ATest::Foo4, a1, var10, 2);
    arg10.Call<int>(&Print, var10, std::move("Print var value : %d\n"));
    
    basic::test::Variable<basic::test::Value<int>,
        basic::test::type::Function<int(int&&), &Foo2>> var11(4);
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::
        Function<1, basic::test::msg::arg::Value<0>>> arg11;
    printf("get arg11 value from var11  : %d\n", arg11.Get(var11));
    arg11.Call<void>(&ATest::Foo4, a1, var11, 2);
    arg11.Call<int>(&Print, var11, std::move("Print var value : %d\n"));
    
    basic::test::Variable<basic::test::val::Function<int()>> var12(&Foo1);
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::
        Function<0>> arg12;
    
    printf("get arg12 value from var12  : %d\n", arg12.Get(var12));
    arg12.Call<void>(&ATest::Foo4, a1, var12, 2);
    arg12.Call<int>(&Print, var12, std::move("Print var value : %d\n"));
    
    basic::test::Variable<basic::test::Value<int>,
        basic::test::val::Function<int(int&&)>> var13(14, &Foo2);
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::
        Function<1, basic::test::msg::arg::Value<0>>> arg13;
        
    printf("get arg13 value from var13  : %d\n", arg13.Get(var13));
    arg13.Call<void>(&ATest::Foo4, a1, var13, 2);
    arg13.Call<int>(&Print, var13, std::move("Print var value : %d\n"));


    basic::test::Variable<basic::test::val::Parameter<int, float, long, 
        double>, char> var14(1, 3.14, 14, double(22/7.0));
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::
        val::Parameter<0>> arg14;
        
    printf("get arg14 value at 0 from var14  : %d\n", arg14.Get<0>(var14));
    printf("get arg14 value at 1 from var14  : %f\n", arg14.Get<1>(var14));
    printf("get arg14 value at 2 from var14  : %d\n", arg14.Get<2>(var14));
    printf("get arg14 value at 3 from var14  : %f\n", arg14.Get<3>(var14));
    arg14.Call<void>(&ATest::Foo6, a1, var14, 2);
    arg14.Call<int>(&Print, var14, 
        std::move("Print type val parameter : %d %f %d %f\n"));
    
    basic::test::msg::Argument<TestA1, 
        basic::test::msg::arg::val::param::At<0, 0>> arg14_0_0;
    basic::test::msg::Argument<TestA1, 
        basic::test::msg::arg::val::param::At<0, 1>> arg14_0_1;
    basic::test::msg::Argument<TestA1, 
        basic::test::msg::arg::val::param::At<0, 2>> arg14_0_2;
    basic::test::msg::Argument<TestA1, 
        basic::test::msg::arg::val::param::At<0, 3>> arg14_0_3;
        
    printf("get arg14_0_0 value from var14  : %d\n", arg14_0_0.Get(var14));
    arg14_0_0.Call<void>(&ATest::Foo4, a1, var14, 2);
    arg14_0_0.Call<int>(&Print, var14, std::move("Print type value at 0 : %d\n"));
    
    printf("get arg14_0_1 value from var14  : %f\n", arg14_0_1.Get(var14));
    arg14_0_1.Call<void>(&ATest::Foo4f, a1, var14, 2);
    arg14_0_1.Call<int>(&Print, var14, std::move("Print type value at 1 : %f\n"));
    
    printf("get arg14_0_2 value from var14  : %d\n", arg14_0_2.Get(var14));
    arg14_0_2.Call<void>(&ATest::Foo4, a1, var14, 2);
    arg14_0_2.Call<int>(&Print, var14, std::move("Print type value at 2 : %d\n"));
    
    printf("get arg14_0_3 value from var14  : %f\n", arg14_0_3.Get(var14));
    arg14_0_3.Call<void>(&ATest::Foo4f, a1, var14, 2);
    arg14_0_3.Call<int>(&Print, var14, std::move("Print type value at 3 : %f\n"));

    basic::test::Variable<basic::test::type::Function<int(int&&, float&&, 
        long&&, int&&), &Foo3>, basic::test::val::Parameter<int, float, long>,
        basic::test::type::Value<int, 22>> var15(1, 3.14, 11);
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::
        Function<0, basic::test::msg::arg::val::Parameter<1>,
            basic::test::msg::arg::type::Value<2>>> arg15;
    printf("get arg15 value from arg15  : %d\n", arg15.Get(var15));
    arg15.Call<void>(&ATest::Foo4, a1, var15, 2);
    arg15.Call<int>(&Print, var15, std::move("Print var value : %d\n"));
    
    basic::test::Variable<basic::test::type::Function<int(int&&, int&&, 
        int&&, int&&), &Foo3>, basic::test::val::Sequence<int, 3>,
        basic::test::Value<int>> var16(1, 2, 3, 4);
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::
        Function<0, basic::test::msg::arg::val::Sequence<1>,
            basic::test::msg::arg::Value<2>>> arg16;
    printf("get arg16 value from var16  : %d\n", arg16.Get(var16));
    arg16.Call<void>(&ATest::Foo4, a1, var16, 2);
    arg16.Call<int>(&Print, var16, std::move("Print var value : %d\n"));
    
    typedef basic::test::type::Index<TestA1, 0> TestAt_at0;
    basic::test::msg::Argument<TestA1, basic::test::msg::arg::type::Index<0,
        basic::test::msg::arg::val::seq::At>> arg17;
    printf("get arg17 at 0 value from var16  : %d\n", arg17.Get<0>(var9));
    arg17.Call<void>(TestAt_at0{}, &ATest::Foo4, a1, var9, 2);
    arg17.Call<int>(TestAt_at0{}, 
        &Print, var9, std::move("Print var value : %d\n"));
    
    
    typedef basic::test::type::Index<TestA1, 1> TestAt_at1;
    basic::test::Variable<
        basic::test::Value<int>,
        basic::test::val::Sequence<int, 4>,
        basic::test::type::Value<int, 1>,
        basic::test::type::val::Sequence<int, 144, 4, 44, 441>> var18(4, 11, 14, 6, 22);
    basic::test::msg::Argument<TestA1, 
        basic::test::msg::arg::Value<0>,
        basic::test::msg::arg::type::Index<1,
            basic::test::msg::arg::val::seq::At>,
        basic::test::msg::arg::type::Value<2>,
        basic::test::msg::arg::type::Index<3,
            basic::test::msg::arg::type::val::seq::At>> arg18;
    arg18.Call<void>(TestAt_at1{}, &ATest::Foo4, a1, var18, 2);
    arg18.Call<int>(TestAt_at1{}, &Print, var18, 
        std::move("Print var value : %d %d %d %d\n"));
}
